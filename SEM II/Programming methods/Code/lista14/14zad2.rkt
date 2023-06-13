#lang plait

(module+ test
  (print-only-errors #t))

;; abstract syntax -------------------------------

(define-type Op
  (add) (sub) (mul))

(define-type Exp
  (numE [n : Number])
  (opE [op : Op] [e1 : Exp] [e2 : Exp])
  (varE [x : Symbol])
  (lamE [x : Symbol] [e : Exp])
  (appE [e0 : Exp] [e1 : Exp]))

;; semantics: the error/exception monad and values

(define-type (M 'a)
  (valM [val : 'a])
  (errM (l : Symbol) (m : String)))


(define (returnM [v : 'a]) : (M 'a)
  (valM v))

(define (bindM [c : (M 'a)] [f : ('a -> (M 'b))]) : (M 'b)
  (type-case (M 'a) c
    [(errM l m) (errM l m)]
    [(valM val) (f val)]))

(define (errorM [l : Symbol] [m : String]) : (M 'a)
  (errM l m))

#|
returnM :  ('a -> (M 'a))
bindM : ((M 'a) ('a -> (M 'b)) -> (M 'b))
1) (bindM (returnM a) f) ≡ (bindM (valM a) f) ≡ (f a).

2) (bindM c returnM) ≡ ...
  2.1) (c to (errM l m)): ...  ≡ c.
  2.2) (c to (valM x)): ...  ≡ (returnM (valM x)) [gdzie (valM x)  ≡ c]  ≡  (returnM x)  ≡ (valM x) ≡ c.

3) (bindM (bindM c f) g) ≡ ... ≡ (bindM c (λ (a) (bindM (f a) g))).
  3.1) (c to (errM l m)): ... ≡ (bindM (errM l m) g) ≡ (errM l m) ≡ c ≡ (bindM c (λ (a) (bindM (f a) g))).
  3.2) (c to (valM x)): ... ≡ (bindM (f x) g) ≡ (g (f x)) ≡ (bindM (f x) g) ≡ (bindM c (λ (a) (bindM (f a) g)))
|#

(define (showM [c : (M Value)]) : String
  (type-case (M Value) c
    [(errM l m) (string-append "error in " (string-append (symbol->string l) (string-append ": " m)))]
    [(valM val) (value->string val)]))

(define-type Value
  (numV [n : Number])
  (funV [f : (Value -> (M Value))]))

(define (value->string [v : Value]) : String
  (type-case Value v
    [(numV n) (string-append "value: " (to-string n))]       
    [(funV _) "value: #<procedure>"]))

;; environments

(define-type Binding
  (bind [name : Symbol]
        [val : Value]))

(define-type-alias Env (Listof Binding))

(define mt-env empty)

(define (extend-env [env : Env] [x : Symbol] [v : Value]) : Env
  (cons (bind x v) env))

(define (lookup-env [x : Symbol] [env : Env]) : (M Value)
  (type-case (Listof Binding) env
    [empty
     (errorM 'lookup-env "unbound variable")]
    [(cons b rst-env)
     (cond
       [(eq? x (bind-name b))
        (returnM (bind-val b))]
       [else
        (lookup-env x rst-env)])]))

;; primitive operations

(define (op-num-num->proc [f : (Number Number -> Number)]) : (Value Value -> (M Value))
  (λ (v1 v2)
    (type-case Value v1
      [(numV n1)
       (type-case Value v2
         [(numV n2)
          (returnM (numV (f n1 n2)))]
         [else
          (errorM 'prim-op "not a number")])]
      [else
       (errorM 'prim-op "not a number")])))

(define (op->proc [op : Op]) : (Value Value -> (M Value))
  (type-case Op op
    [(add) (op-num-num->proc +)]
    [(sub) (op-num-num->proc -)]
    [(mul) (op-num-num->proc *)]))

;; evaluation function (eval/apply)

(define (eval [e : Exp] [env : Env]) : (M Value)
  (type-case Exp e
    [(numE n)
     (returnM (numV n))]
    [(opE o e1 e2)
     (bindM (eval e1 env)
            (λ (v1) (bindM (eval e2 env)
                           (λ (v2) ((op->proc o) v1 v2)))))]
    [(varE x)
     (lookup-env x env)]
    [(lamE x b)
     (returnM (funV (λ (v) (eval b (extend-env env x v)))))]
    [(appE e0 e1)
     (bindM (eval e0 env)
            (λ (v0) (bindM (eval e1 env)
                           (λ (v1) (apply v0 v1)))))]))

(define (apply [v0 : Value] [v1 : Value]) : (M Value)
  (type-case Value v0
    [(funV f) (f v1)]
    [else (errorM 'apply "not a function")]))

(define (run [e : S-Exp]) : String
  (showM (eval (parse e) mt-env)))

(module+ test
  (test (run `{+ {* 2 3} {+ 5 8}})
        "value: 19")
  (test (run `{{lambda {x} {+ x 1}} 5})
        "value: 6")
  (test (run `{lambda {x} {+ x 1}})
        "value: #<procedure>")
  (test (run `{1 2})
        "error in apply: not a function")
  (test (run `x)
        "error in lookup-env: unbound variable")
  (test (run `{+ 1 {lambda {x} x}})
        "error in prim-op: not a number"))


;; parse ----------------------------------------

(define (parse [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    [(s-exp-match? `{lambda {SYMBOL} ANY} s)
     (lamE (s-exp->symbol
            (first (s-exp->list 
                    (second (s-exp->list s)))))
           (parse (third (s-exp->list s))))]
    [(s-exp-match? `{SYMBOL ANY ANY} s)
     (opE (parse-op (s-exp->symbol (first (s-exp->list s))))
          (parse (second (s-exp->list s)))
          (parse (third (s-exp->list s))))]
    [(s-exp-match? `SYMBOL s)
     (varE (s-exp->symbol s))]
    [(s-exp-match? `{ANY ANY} s)
     (appE (parse (first (s-exp->list s)))
           (parse (second (s-exp->list s))))]
    [else (error 'parse "invalid input")]))

(define (parse-op [op : Symbol]) : Op
  (cond
    [(eq? op '+) (add)]
    [(eq? op '-) (sub)]
    [(eq? op '*) (mul)]
    [else (error 'parse "unknown operator")]))



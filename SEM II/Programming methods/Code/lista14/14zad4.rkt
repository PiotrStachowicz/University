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
  (count)
  (appE [e0 : Exp] [e1 : Exp]))

;; semantics: the identity monad and values
(define-type-alias State Number)

(define-type (E 'a)
  (valE [val : 'a])
  (errE (l : Symbol) (m : String)))


(define (returnE [v : 'a]) : (E 'a)
  (valE v))

(define (bindE [c : (E 'a)] [f : ('a -> (E 'b))]) : (E 'b)
  (type-case (E 'a) c
    [(errE l m) (errE l m)]
    [(valE val) (f val)]))

(define (errorE [l : Symbol] [m : String]) : (E 'a)
  (errE l m))

(define (showE [c : (E Value)]) : String
  (type-case (E Value) c
    [(errE l m) (string-append "error in " (string-append (symbol->string l) (string-append ": " m)))]
    [(valE val) (value->string val)]))

(define-type-alias (M 'a) (State -> ((E 'a) * State)))

(define (returnM [v : 'a]) : (M 'a)
  (λ ([s : State]) (pair (returnE v) s)))

(define (bindM [c : (M 'a)] [f : ('a -> (M 'b))]) : (M 'b)
  (λ ([s : State]) (let* ([Ma (c s)]
                          [Ea (fst Ma)]
                          [new_s (snd Ma)])
                     (type-case (E 'a) Ea
                       [(errE l m) ((errorM l m) new_s)]
                       [(valE val) ((f val) new_s)]))))

(define (errorM [l : Symbol] [m : String]) : (M 'a)
  (λ ([s : State]) (pair (errorE l m) s)))

(define (tickM) : (M Void)
  (λ ([s : State]) (pair (returnE (void)) (+ 1 s))))

(define (showM [c : (M Value)]) : String
  (let ([x (c 0)])
    (type-case (E 'a) (fst x)
      [(errE l m) (string-append (showE (fst x)) (string-append ", state: " (to-string (snd x))))]
      [(valE val) (string-append "value: " (string-append (showE (fst x)) (string-append ", state: " (to-string (snd x)))))])))

#|
returnM :  ('a -> (M 'a))
bindM : ((M 'a) ('a -> (M 'b)) -> (M 'b))
1) (bindM (returnM a) f) ≡ (bindM (λ (State1) (pair (valE a) State1)) f) ≡ (λ (State2) (pair (f a) State2)) ≡ (f a).

2) (bindM c returnM) [gdzie c to (λ (State1) (pair Ea State1))]  ≡ (λ (State2) ...
2.1) (Ea to (errE l m)): ... (pair (errE l m) State2) ≡ c.
2.2) (Ea to (valE a)): ... (pair (valE a) State2)  ≡ c.


3) (bindM (bindM c f) g) [gdzie c to (λ (State1) (pair Ea State1))] ≡ ...
   3.1) (Ea to (errE l m)): ... ≡ (bindM (λ (State2) (pair (errE l m) State2) g) ≡ (λ (State3) (pair (errE l m) State3)) ≡ ...
   ≡ (bindM c (λ (a) (bindM (f a) g))). 
   3.2) (Ea to (valE a)): ... ≡ (bindM (λ (State2) (pair (f a) State2)) g) ≡ (λ (State3) (pair (g (f a)) State3)) ≡ ...
   (λ (State1) ((λ (State2) (pair (g (f a)) State2)) State1)
   ≡ (λ (State1) (((λ (a) (bindM (f a) g)) a) State1) ≡ (bindM c (λ (a) (bindM (f a) g))) ≡
|#


(define-type Value
  (numV [n : Number])
  (funV [f : (Value -> (M Value))]))

(define (value->string [v : Value]) : String
  (type-case Value v
    [(numV n) (to-string n)]
    [(funV _) "#<procedure>"]))

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
          (bindM (tickM)
                 (λ (void) (returnM (numV (f n1 n2)))))]
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
    [(count)
     (λ ([s : State])
       (pair (returnE (numV s)) s))]
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
    [(funV f) (bindM (tickM) (λ ([_ : Void]) (f v1)))]
    [else (errorM 'apply "not a function")]))

(define (run [e : S-Exp]) : String
  (showM (eval (parse e) mt-env)))

(module+ test
   (test (run `{+ {* 2 3} {+ 5 8}})
          "value: 19, state: 3")
   (test (run `{+ {+ 1 2} {lambda {x} x}})
          "error in prim-op: not a number, state: 1"))


;; parse ----------------------------------------

(define (parse [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    [(s-exp-match? `count s)
     (count)]
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
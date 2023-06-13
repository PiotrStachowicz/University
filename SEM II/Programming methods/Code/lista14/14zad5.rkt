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
  (writE [e : Exp])
  (lamE [x : Symbol] [e : Exp])
  (beginE [e1 : Exp] [e2 : Exp])
  (appE [e0 : Exp] [e1 : Exp]))

;; semantics: the identity monad and values

(define-type-alias Output (Listof Number))
(define-type-alias (M 'a) ('a * Output))

(define (returnM [v : 'a]) : (M 'a)
  (pair v empty))

(define (bindM [c : (M 'a)] [f : ('a -> (M 'b))]) : (M 'b)
  (let* ([v1 (fst c)]
         [output1 (snd c)]
         [Mv2 (f v1)]
         [v2 (fst Mv2)]
         [output2 (snd Mv2)])
    (pair v2 (append output1 output2))))

(define (errorM [l : Symbol] [m : String]) : (M 'a)
  (pair (error l m) empty))

(define (showM [c : (M Value)]) : String
  (string-append "value: " (string-append (value->string (fst c)) (string-append ", output: " (list->string (snd c))))))

#|
returnM :  ('a -> (M 'a))
bindM : ((M 'a) ('a -> (M 'b)) -> (M 'b))
1) (bindM (returnM a) f) ≡ (bindM (pair v empty) f) ≡ (f a).

2) (bindM c returnM) [gdzie c to (pair v o)] ≡ (pair v (append o empty)) ≡ c.


3) (bindM (bindM c f) g)[gdzie c to (pair v o)] ≡ (bindM (pair (f v) (append o (snd (f v)))) g)
 ≡ (pair (g (f v)) (append o (append (snd (f v)))) (snd (g (f v)))))
 
 (bindM c (λ (a) (bindM (f a) g))) [gdzie c to (pair v o)] ≡ (pair (fst (bindM (f v) g)) (append o (snd (bindM (f v) g))))
 ≡ (pair (fst (pair (g (f v)) (append (snd (f v)) (snd (g (f v)))))) (append o (snd (bindM (f v) g))))
 ≡ (pair (g (f v))(append o (append (snd (f v)) (snd (g (f v))))))).
|#

(define (list->string xs) : String
  (cond
    [(empty? xs) ""]
    [else (string-append (to-string (first xs)) (list->string (rest xs)))]))

(define-type Value
  (voidV)
  (numV [n : Number])
  (funV [f : (Value -> (M Value))]))

(define (value->string [v : Value]) : String
  (type-case Value v
    [(voidV) "#<void>"]
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
    [(beginE e1 e2)
     (bindM (eval e1 env)
            (λ (v1) (bindM (eval e2 env)
                           (λ (v2) (pair v2 empty)))))]
    [(writE e)
     (bindM (eval e env)
            (λ (v1) (pair (voidV) (list (numV-n v1)))))]
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
          "value: 19, output: ")
   (test/exn (run `{1 2})
              "not a function")
   (test (run `{write {{lambda {x} {begin {write x} {+ x 1}}} 5}})
          "value: #<void>, output: 56"))

;; parse ----------------------------------------

(define (parse [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    [(s-exp-match? `{begin ANY ANY} s)
     (beginE (parse (second (s-exp->list s)))
             (parse (third (s-exp->list s))))]
    [(s-exp-match? `{write ANY} s)
     (writE (parse (second (s-exp->list s))))]
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


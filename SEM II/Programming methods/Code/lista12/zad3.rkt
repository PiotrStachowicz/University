#lang plait

(module+ test
  (print-only-errors #t))

;; abstract syntax ---------------------------------------------------

(define-type Exp
  (numE [n : Number])
  (ifz [b : Exp] [l : Exp] [r : Exp])
  (varE [x : Symbol])
  (letE [x : Symbol] [e1 : Exp] [e2 : Exp])
  (defE [xs : (Listof Exp)] [b : Exp])
  (funE [x : Symbol] [xs : (Listof Symbol)] [b : Exp])
  (wywE [x : Symbol] [xs : (Listof Exp)])
  (appE [e1 : Exp] [e2 : Exp]))

;; parse --------------------------------------------------------------

(define (parse [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    [(s-exp-match? `{define {ANY ...} for ANY} s)
     (defE (map parse (s-exp->list (second (s-exp->list s))))
           (parse (fourth (s-exp->list s))))]
    [(s-exp-match? `{ifz ANY then ANY else ANY} s)
     (ifz (parse (second (s-exp->list s)))
          (parse (fourth (s-exp->list s)))
          (parse (fourth (rest (rest (s-exp->list s))))))]
    [(s-exp-match? `SYMBOL s)
     (varE (s-exp->symbol s))]
    [(s-exp-match? `{let SYMBOL be ANY in ANY} s)
     (letE (s-exp->symbol (second (s-exp->list s)))
           (parse (fourth (s-exp->list s)))
           (parse (fourth (rest (s-exp->list s)))))]
    [(s-exp-match? `{SYMBOL {ANY ...}} s)
     (wywE (s-exp->symbol (first (s-exp->list s))) (map parse (s-exp->list (first (rest (s-exp->list s))))))]
    [(s-exp-match? `{fun SYMBOL {ANY ...} = ANY} s)
     (funE (s-exp->symbol (second (s-exp->list s))) (map s-exp->symbol (s-exp->list (third (s-exp->list s)))) (parse (fourth (rest (s-exp->list s)))))]
    [(s-exp-match? `{ANY SYMBOL ANY} s)
     (appE (appE (varE (parse-op (s-exp->symbol (second (s-exp->list s)))))
                 (parse (first (s-exp->list s))))
           (parse (third (s-exp->list s))))]
    [(s-exp-match? `{ANY ANY} s)
     (appE (parse (first (s-exp->list s)))
           (parse (second (s-exp->list s))))]
    [else (error 'parse "invalid input")]))

(define prim-ops '(+ - * <=))

(define (parse-op [op : Symbol]) : Symbol
  (if (member op prim-ops)
      op 
      (error 'parse-op "unknown binary operator")))

;; eval --------------------------------------

;; values

(define-type Value
  (numV [n : Number])
  (funV [x : Symbol] [e : Exp] [env : Env])
  (primopV [f : (Value -> Value)]))

(define-type Binding
  (bind [name : Symbol]
        [val : Value]))

;; environments

(define-type-alias Env (Listof Binding))

(define mt-env empty)
(define (extend-env [env : Env] [x : Symbol] [v : Value]) : Env
  (cons (bind x v) env))
(define (lookup-env [n : Symbol] [env : Env]) : Value
  (type-case (Listof Binding) env
    [empty (error 'lookup "unbound variable")]
    [(cons b rst-env) (cond
                        [(eq? n (bind-name b))
                         (bind-val b)]
                        [else (lookup-env n rst-env)])]))

;; primitive operations and the initial environment

(define (op-num-num->value [f : (Number Number -> Number)]) : Value 
  (primopV
   (λ (v1)
     (type-case Value v1
       [(numV n1)
        (primopV
         (λ (v2)
           (type-case Value v2
             [(numV n2)
              (numV (f n1 n2))]
             [else
              (error 'eval "type error")])))]
       [else
        (error 'eval "type error")]))))

(define (op-num-bool->value [f : (Number Number -> Number)]) : Value 
  (primopV
   (λ (v1)
     (type-case Value v1
       [(numV n1)
        (primopV
         (λ (v2)
           (type-case Value v2
             [(numV n2)
              (boolV (f n1 n2))]
             [else
              (error 'eval "type error")])))]
       [else
        (error 'eval "type error")]))))

(define init-env 
  (foldr (λ (b env) (extend-env env (fst b) (snd b)))
         mt-env 
         (list (pair '+ (op-num-num->value +))
               (pair '- (op-num-num->value -))
               (pair '* (op-num-num->value *))
               (pair '<= (op-num-bool->value <=)))))

;; evaluation function (eval/apply)

#;(define-type Exp
  (numE [n : Number])
  (ifz [b : Exp] [l : Exp] [r : Exp])
  (varE [x : Symbol])
  (letE [x : Symbol] [e1 : Exp] [e2 : Exp])
  (defE [xs : (Listof Exp)] [b : Exp])
  (funE [x : Symbol] [xs : (Listof Symbol)] [b : Exp])
  (wywE [x : Symbol] [xs : (Listof Exp)])
  (appE [e1 : Exp] [e2 : Exp]))

(define (eval [e : Exp] [env : Env]) : Value
  (type-case Exp e
    [(numE n) (numV n)]
    [(ifz b l r)
     (type-case Value (eval b env)
       [(numV v)
        (if (= 0 (numV-v v)) (eval l env) (eval r env))]
       [else
        (error 'eval "type error")])]
    [(varE x)
     (lookup-env x env)]
    [(defE xs b) (numV 2)]
    [(letE x e1 e2)
     (let ([v1 (eval e1 env)])
       (eval e2 (extend-env env x v1)))]
    [(wywE x xs) (numV 2)]
    [(funE x xs b) (numV 2)]
    [(appE e1 e2)
     (apply (eval e1 env) (eval e2 env) env)]))

(define (apply [v1 : Value] [v2 : Value] [e : Env]) : Value
  (type-case Value v1
    [(funV x b env)
     (eval b (extend-env e x v2))]
    [(primopV f)
     (f v2)]
    [else (error 'apply "not a function")]))

(define (run [e : S-Exp]) : Value
  (eval (parse e) init-env))
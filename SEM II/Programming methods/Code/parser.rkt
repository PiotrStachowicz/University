#lang plait

(define-type Exp
  (exp-number [n : Number])
  (exp-op [op : Op] [e1 : Exp] [e2 : Exp])
  (exp-op1 [op : Op1] [e1 : Exp]))


(define-type Op
  (op-add) (op-mul) (op-sub) (op-div) (op-pot))

(define-type Op1
  (op-sil) (op-umin))

(define (parse-Op s)
  (let ([sym (s-exp->symbol s)])
  (cond
    [(equal? sym '+) (op-add)]
    [(equal? sym '-) (op-sub)]
    [(equal? sym '*) (op-mul)]
    [(equal? sym '/) (op-div)]
    [(equal? sym '^) (op-pot)])))

(define (parse-Op1 s)
  (let ([sym (s-exp->symbol s)])
  (cond
    [(equal? sym '!) (op-sil)]
    [(equal? sym '~) (op-umin)])))

(define (parse-Exp s)
  (cond
    [(s-exp-number? s) (exp-number (s-exp->number s))]
    [(s-exp-list? s)
     (let ([xs (s-exp->list s)])
       (if (empty? (rest (rest xs)))
           (exp-op1 (parse-Op1 (first xs))
                    (parse-Exp (second xs)))
           (exp-op (parse-Op (first xs))
                   (parse-Exp (second xs))
                   (parse-Exp (third xs)))))]))

; Zadanie 4 1/1
(define (better-parse-Exp s)
  (cond
    [(s-exp-number? s) (s-exp->number s)]
    [(s-exp-list? s)
     (let ([xs (s-exp->list s)])
       ((eval-op (parse-Op (first  xs)))
               (better-parse-Exp (second xs))
               (better-parse-Exp (third  xs))))]))

; ==============================================

(define (eval-op op)
  (type-case Op op
    [(op-add) +]
    [(op-sub) -]
    [(op-mul) *]
    [(op-div) /]
    [(op-pot) pot]))

(define (eval-op1 op)
  (type-case Op1 op
    [(op-sil) sil]
    [(op-umin) umin]))

(define (pot x y)
  (if (> y 0)
      (* x (pot x (- y 1)))
      1))

(define (sil x)
  (if (> x 0) (* x (sil (- x 1))) 1))

(define (umin x)
  (* x -1))

(define (eval e)
  (type-case Exp e
    [(exp-number n)    n]
    [(exp-op op e1 e2)
     ((eval-op op) (eval e1) (eval e2))]
    [(exp-op1 op e1) ((eval-op1 op) (eval e1))]))
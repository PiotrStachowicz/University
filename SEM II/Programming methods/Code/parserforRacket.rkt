#lang plait

; Zadanie 6 2/2 i 7 ?/2
; Types


(define-type Racket-Exp
  [var (name : Symbol)]
  [val (num : Number)]
  [lam (arg : (Listof Symbol))
       (body : Racket-Exp)]
  [app (op : Racket-Exp)
       (arg : (Listof Racket-Exp))]
  [letE (ch : (Listof (Symbol * Racket-Exp)))
        (body : Racket-Exp)]
  [ifE (check : Racket-Exp)
       (T : Racket-Exp)
       (F : Racket-Exp)]
  [condE (body : (Listof (Racket-Exp * Racket-Exp)))
         (else-case : (Optionof Racket-Exp))])

; Parser


(define (last xs)
  (cond
    [(empty? (rest xs)) (first xs)]
    [else (last (rest xs))]))

(define (take xs)
  (cond [(empty? xs) xs]
        [(empty? (rest xs)) (rest xs)]
        [else (cons (first xs) (take (rest xs)))]))


(define (parser s)
  (cond
    [(s-exp-number? s) (val (s-exp->number s))]
    [(s-exp-symbol? s) (var (s-exp->symbol s))]
    [(s-exp-list? s)
     (let* ([xs (s-exp->list s)]
            [fst (first xs)])
       (cond
         [(equal? fst `lambda) (lam (map s-exp->symbol (s-exp->list (second xs))) (parser (third xs)))]
         [(equal? fst `if) (ifE (parser (second xs)) (parser (third xs)) (parser (fourth xs)))]
         [(equal? fst `let) (letE (map (lambda (x) (let ([y (s-exp->list x)])
                                                     (pair (s-exp->symbol (first y)) (parser (second y))))) (s-exp->list (second xs)))
                                  (parser (third xs)))]
         [(equal? fst `cond) (let ([x (s-exp->list (last xs))])
                               (if (equal? (first x) `else)
                                   (condE (map (lambda (z) (let ([y (s-exp->list z)])
                                                                    (pair (parser (first y)) (parser (second y))))) (take (rest xs)))
                                                 (some (parser (second x))))
                                   (condE (map (lambda (z)
                                                (pair (parser (first (s-exp->list z))) (parser (second (s-exp->list z))))) (rest xs))
                                          (none))))]  
         [else (app (parser (first xs)) (map parser (rest xs)))]))]))




(define (sil x)
  (if (> x 0) (* x (sil (- x 1))) 1))
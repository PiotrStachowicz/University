#lang racket
(require "3types.rkt")
(require (only-in plait s-exp-content))
(provide (contract-out [run-parser
                        
(-> (listof
     (list/c
      (or/c symbol? (listof symbol?))
      procedure?))
    any/c any/c)]))

; Sprawdza czy s pasuje do patternu pat (#f lub (list s))
(define (match-sexp pat s)
  (match pat
    ['ANY    (list s)]
    ['SYMBOL (and (symbol? s) (list s))]
    ['NUMBER (and (number? s) (list s))]
    ['()     (and (null? s)   null)]
    [(cons p1 p2)
     (and (pair? s)
          (let ([r1 (match-sexp p1 (car s))])
            (and r1
                 (let ([r2 (match-sexp p2 (cdr s))])
                   (and r2 (append r1 r2))))))]
    [_
     (cond
       [(symbol? pat) (and (symbol? s) (eq? pat s) null)])]))

; Parse op/expr
(define (run-parser p s)
  (match p
    ['() (error "Syntax error")]
    [(cons (list pat action) rest-p)
     (let ([r (match-sexp pat s)])
       (if r
           (apply action r)
           (run-parser rest-p s)))]))

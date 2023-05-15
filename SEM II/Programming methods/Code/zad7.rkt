#lang plait
(define-syntax my-and
  (syntax-rules ()
    [(my-and) #t]
    [(my-and a1 a2 ...) (if a1 (my-and a2 ...)
                            #f)]))

(define-syntax my-or
  (syntax-rules ()
    [(my-or) #f]
    [(my-or a1 a2 ...) (if a1 #t
                            (my-or a2 ...))]))


(define-syntax my-let
  (syntax-rules ()
    [(my-let () body) body]
    [(my-let ([x1 e1] [x2 e2] ...) body)
     ((λ (x1 x2 ...) body) e1 e2 ...)]))

(define-syntax my-let*
  (syntax-rules ()
    [(my-let* () body) body]
    [(my-let* ([x1 e1] [x2 e2] ...) body)
     ((λ (x1) (my-let* ([x2 e2] ...) body)) e1)]))
#lang racket

; Zadanie 3 1/1

; cpu time: 296 real time: 316 gc time: 125
(define/contract (suffixes xs)
  (parametric->/c [a] (-> (listof a) (listof (listof a))))
  (match xs
    ['() (list '())]
    [(cons x ys) (cons xs (suffixes ys))]))

; cpu time: 0 real time: 0 gc time: 0
(define (suffixes2 xs)
  (match xs
    ['() (list '())]
    [(cons x ys) (cons xs (suffixes2 ys))]))

; Zadanie 4 1/1

;( parametric- >/ c [ a b ] (- > a b a ) )

(define/contract (f1 a b)
  (parametric->/c [a b] (-> a b a))
  a)

;( parametric- >/ c [ a b c ] (- > (- > a b c ) (- > a b ) a c ) )

(define/contract (f2 f g a)
  (parametric->/c [a b c] (-> (-> a b c) (-> a b) a c))
  (f a (g a)))

;( parametric- >/ c [ a b c ] (- > (- > b c ) (- > a b ) (- > a c ) ) )

(define/contract (f3 f g)
  (parametric->/c [a b c] (-> (-> b c) (-> a b) (-> a c)))
  (lambda (x) (f (g x))))

; ( parametric- >/ c [ a ] (- > (- > (- > a a ) a ) a ) )

(define (id x)
   x)

(define/contract (f4 f)
  (parametric->/c [a] (-> (-> (-> a a) a) a))
  (f identity))

; Zadanie 5 2/2

(define/contract (foldl-map f a xs)
  (parametric->/c [a b c] (-> (-> a b (cons/c c b)) b (listof a)
                              (cons/c (listof c) b)))
  (define (it a xs ys)
    (if (null? xs)
        (cons (reverse ys) a)
        (let [(p (f (car xs) a))]
          (it (cdr p)
              (cdr xs)
              (cons (car p) ys)))))
  (it a xs null))



(define/contract (fh a b)
  (parametric->/c [c] (-> c c c))
  b)

(fh 8 #t)

; Zadanie 6 2/2

;(parametric->/c [a b] (-> (-> a b b) b (listof a) b))
;(parametric->/c [a] (-> (-> a a a) a (listof a) a))

(define/contract (my-foldr f x xs)
  (parametric->/c [a b] (-> (-> a b b) b (listof a) b))
  (match xs
    ['() x]
    [(cons y ys) (f y (my-foldr f x ys))]))

(define/contract (my-foldr-blad f x xs)
  ;(parametric->/c [a] (-> (-> a a a) a (listof a) a))
  (parametric->/c [a b] (-> (-> a b b) b (listof a) b))
  (match xs
    ['() x]
    [(cons y ys) (f (my-foldr-blad f x ys) y)]))




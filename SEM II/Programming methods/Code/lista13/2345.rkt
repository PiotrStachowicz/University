#lang racket

;; processing data sequences with lists --------------------

(define (second-prime-in-interval a b)
  (car (cdr (filter prime?
                    (enumerate-interval a b)))))

; (second-prime-in-interval 10000 5000000)

(define (enumerate-interval a b)
  (if (> a b)
      '()
      (cons a (enumerate-interval (+ a 1) b))))

(define (square x)
  (* x x))

(define (smallest-divisor n)
  (find-divisor n 2))

(define (find-divisor n test-divisor)
  (cond ((> (square test-divisor) n) n)
        ((divides? test-divisor n) test-divisor)
        (else (find-divisor n (+ test-divisor 1)))))

(define (divides? a b)
  (= (remainder b a) 0))

(define (prime? n)
  (= n (smallest-divisor n)))

;; streams aka lazy lists ---------------------------------

;; delay and force

(define-syntax-rule
  (stream-cons v s)
  (cons v (delay s)))

(define stream-car car)

(define (stream-cdr s)
  (force (cdr s)))

(define stream-null null)
(define stream-null? null?)

;; operations on streams

(define (stream-ref s n)
  (if (= n 0)
      (stream-car s)
      (stream-ref (stream-cdr s) (- n 1))))

(define (stream-filter p s)
  (if (stream-null? s)
      stream-null
      (if (p (stream-car s))
          (stream-cons (stream-car s)
                       (stream-filter p (stream-cdr s)))
          (stream-filter p (stream-cdr s)))))

(define (stream-enumerate-interval a b)
  (if (> a b)
      stream-null
      (stream-cons a (stream-enumerate-interval (+ a 1) b))))

(define (stream-second-prime-in-interval a b)
  (stream-car
   (stream-cdr
    (stream-filter prime?
                   (stream-enumerate-interval a b)))))

;; infinite streams

(define ones (stream-cons 1 ones))

(define (integers-from n)
  (stream-cons n (integers-from (+ n 1))))

(define nats (integers-from 0))

(define (sieve s)
  (stream-cons
   (stream-car s)
   (sieve
    (stream-filter
     (λ (x) (begin (display (stream-car s))
                   (display "\n")
                   (not (divides? (stream-car s) x))))
     (stream-cdr s)))))

(define primes (sieve (integers-from 2)))

 ;; combining (infinite) streams 

(define (map2 f xs ys)
  (stream-cons
   (f (stream-car xs)
      (stream-car ys))
   (map2 f (stream-cdr xs) (stream-cdr ys))))

(define nats2 (stream-cons 0 (map2 + nats2 ones)))

; ZADANIE 2 2/2
(define (new-prime N-stream)
  (define (iterator stream)
    (let ([sx (stream-car stream)]
          [x (stream-car N-stream)])
      (cond
        [(> (* sx sx) x) N-stream]
        [(divides? sx x) (new-prime (stream-cdr N-stream))]
        [else (iterator (stream-cdr stream))])))
  (iterator lazy-primes))

(define (prime-stream N-stream)
  (stream-cons
   (stream-car N-stream)
   (prime-stream (new-prime (stream-cdr N-stream)))))

(define lazy-primes
  (prime-stream (integers-from 2)))

; ZADANIE 3 1/1
(define sil (stream-cons 1 (map2 * sil (integers-from 1))))
#|
int-f-2      2 3...
sil          1 ......
---------------------
sil        1 2
|#

; ZADANIE 4 1/1
(define (partial-sum s)
  (stream-cons (stream-car s) (map2 + (partial-sum s) (stream-cdr s))))
#|
(cdr-s)        S1 S2 ...
partial-sum    S0 ...
---------------------------
partial-sum S0 S0+S1 ...
|#

; ZADANIE 5 2/2 
(define (scale s n)
  (stream-cons
   (* n (stream-car s))
   (scale (stream-cdr s) n)))

(define (merge s1 s2)
  (define (exclude-stream sx s)
    (stream-cons
     (stream-car sx)
     (merge (stream-filter (λ (x) (not (equal? (stream-car sx) x))) (stream-cdr sx))
            (stream-filter (λ (x) (not (equal? (stream-car sx) x))) s))))
  (cond
    [(<= (stream-car s1) (stream-car s2))
     (exclude-stream s1 s2)]
    [else
     (exclude-stream s2 s1)]))
  
(define Hamming-Stream
  (stream-cons
   1
   (merge (scale Hamming-Stream 2) (merge (scale Hamming-Stream 3) (scale Hamming-Stream 5)))))

; Funkcja testująca streamy
(define (test s n)
  (if (= n 0)
      (void)
      (begin
        (display s)
        (display "\n")
        (test (stream-cdr s) (- n 1)))))

(define x (test Hamming-Stream 50))
#|
nats2    0 1 2 ...
ones     1 1 1 ...
---------------------------------------
nats2  0 1 2 3 ...
|#

(define fibs
  (stream-cons 0 (stream-cons 1 (map2 + fibs (stream-cdr fibs)))))

#|
fib            0 1 1 2 3 ...  
(cdr fib)      1 1 2 3 ...
-----------------------------------------
fib        0 1 1 2 3 5 ...

|#

;; our own implementation of delay and force (needs to be moved at the top of the file)

#|
(define (memo-proc proc)
  (let ([already-run? false]
        [result false])
    (lambda ()
      (if (not already-run?)
          (begin (set! result (proc))
                 (set! already-run? true)
                 result)
          result))))

(define-syntax-rule
  (delay c)
  (memo-proc (λ () c)))

(define (force t)
  (t))
|#
#lang racket
; Zadanie 1 1/1
(define (cycle! mlist)
  (define (helper ml)
    (match ml
      [(mcons x null) (set-mcdr! ml mlist)]
      [(mcons x xs) (helper xs)]))
  (helper mlist))


(define mlist1
  (mcons 1 (mcons 2 (mcons 3 null))))

;Zadanie 2 1/1
(define (mreverse! mlist)
  (define (helper prev curr)
    (match curr
      ['() prev]
      [(mcons x xs)
       (define next xs)
       (set-mcdr! curr prev)
       (helper curr next)]))
  (helper null mlist))

; Zadanie 3 3/3

(provide
 dequeue?
 nonempty-dequeue?
 (contract-out
  [dequeue-empty? (-> dequeue? boolean?)]
  [make-dequeue   (-> dequeue?)]
  [dequeue-push-front   (-> dequeue? any/c void?)]
  [dequeue-push-back  (-> dequeue? any/c void?)]
  [dequeue-pop-front    (-> dequeue? any/c)]
  [dequeue-pop-back    (-> dequeue? any/c)]))

(struct node
  ([prev #:mutable]
  [elem]
  [next #:mutable]))

(struct dequeue
  ([front #:mutable]
  [back #:mutable]))


(define/contract (dequeue-empty? dq)
  (-> dequeue? boolean?)
  (and (null? (dequeue-front dq))
       (null? (dequeue-back  dq))))

(define (nonempty-dequeue? dq)
  (and (dequeue? dq) (node? (dequeue-front dq))))

(define/contract (make-dequeue)
  (-> dequeue?)
  (dequeue null null))


; Przykładowa pusta kolejka
(define deq
  (dequeue null null))

; Push Front
(define/contract (dequeue-push-front dq x)
  (-> dequeue? any/c void?)
  (define p (node null x null))
  (if (dequeue-empty? dq)
      (set-dequeue-back! dq p)
      (begin (set-node-next! p (dequeue-front dq))
             (set-node-prev! (dequeue-front dq) p)))
  (set-dequeue-front! dq p))

; Push Back
(define/contract (dequeue-push-back dq x)
  (-> dequeue? any/c void?)
  (define p (node null x null))
  (if (dequeue-empty? dq)
      (set-dequeue-front! dq p)
      (begin (set-node-prev! p (dequeue-back dq))
             (set-node-next! (dequeue-back dq) p)))
  (set-dequeue-back! dq p))


; Pop front
(define/contract (dequeue-pop-front dq)
  (-> nonempty-dequeue? any/c)
  (define p (dequeue-front dq))
  (set-dequeue-front! dq (node-next p))
  (if (null? (node-next p))
      (set-dequeue-back! dq null)
      (set-node-prev! (dequeue-front dq) null))
  (node-elem p))


; Pop back
(define/contract (dequeue-pop-back dq)
  (-> nonempty-dequeue? any/c)
  (define p (dequeue-back dq))
  (set-dequeue-back! dq (node-prev p))
  (if (null? (node-prev p))
      (set-dequeue-front! dq null)
      (set-node-next! (dequeue-back dq) null))
  (node-elem p))
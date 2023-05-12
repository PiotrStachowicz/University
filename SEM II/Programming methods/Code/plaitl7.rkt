#lang plait

; Zadanie 1 2/2

(define-type  (Drzewo2-3 'a)
  (leaf)
  (node2 [l : (Drzewo2-3 'a)] [elem : 'a] [r : (Drzewo2-3 'a)])
  (node3 [l : (Drzewo2-3 'a)] [elem1 : 'a] [s : (Drzewo2-3 'a)] [elem2 : 'a] [r : (Drzewo2-3 'a)]))

(define (val? d min max h mh)
  (type-case (Drzewo2-3 'a) d
    [(leaf) (= h mh)]
    [(node2 l elem r)
     (and (< elem max) (> elem min)
          (val? l min elem (+ 1 h) mh)
          (val? r elem max (+ 1 h) mh))]
    [(node3 l elem1 s elem2 r)
     (and (> elem1 elem2)
          (< elem1 max) (> elem1 min)
          (val? l min elem2 (+ 1 h) mh)
          (val? s elem2 elem1 (+ 1 h) mh)
          (val? r elem1 max (+ 1 h) mh))]))

(define (height d)
  (type-case (Drzewo2-3 'a) d
    [(leaf) 0]
    [(node2 l elem r) (+ 1 (height r))]
    [(node3 l elem1 s elem2 r) (+ 1 (height r))]))

(define (check-drzewo2-3? d)
  (val? d +inf.0 -inf.0 0 (height d)))

; Zadanie 2 2/2

(define-type  (Drzewo 'a)
  (Drzewo23 [tree : (Drzewo2-3 'a)])
  (node4 [l1 : (Drzewo2-3 'a)] [l2 : (Drzewo2-3 'a)]
         [elem1 : 'a] [elem2 : 'a] [elem3 : 'a]
         [r1 : (Drzewo2-3 'a)] [r2 : (Drzewo2-3 'a)])) 

; (define (helper x d) (...)) type: ('a (Drzewo2-3 'a) -> (Drzewo 'a))
; {potencjalnie zmienione na złe drzewko2-3 (posiada node4)}

(define (insert x d)
  (let ([t (helper x d)])
    (if (node4? d)
        (node2
         (node2 (node4-l1 t) (node4-elem1 t) (node4-l2 t))
         (node4-elem2 t)
         (node2 (node4-r1 t) (node4-elem3 t) (node4-r2 t)))
        (Drzewo23-tree t))))








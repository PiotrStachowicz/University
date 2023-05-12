#lang racket
; =====================================================================================================
; ZADANIE 1 2/2
; GRAMATYKA
; T = {0,1,2,3,4,5,6,7,8,9}
; N = {A, E, B, C, H, D, F}
; S = E
; P = {
; E = E - A | E + A | A
; A = A * B | A / B | B
; B = C ^ B | C
; O = -O | C
; C = H | H!| (E)
; H = 0 | D |
; D = 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | DF
; F = 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
; }
; =====================================================================================================
; ZADANIE 4 2/2

; Hash
(define code-map
  (hash
   #\A "._" #\B "_..." #\C "_._." #\D "_.." #\E "." #\F ".._." #\G "__." #\H "...." #\I ".." #\J ".___" #\K "_._"
   #\L "._.." #\M "__" #\N "_." #\O "___" #\P ".__." #\Q "__._" #\R "._." #\S "..." #\T "_" #\U ".._" #\V "..._"
   #\W ".__" #\X "_.._" #\Y "_.__" #\Z "__.." #\1 ".____" #\2 "..___" #\3 "...__" #\4 "...._" #\5 "....."
   #\6 "_...." #\7 "__..." #\8 "___.." #\9 "____." #\0 "_____" #\space "" #\newline "\n" #\. "._._._" #\- "..__._"))
      
; Encoder
(define (process s)
  (map (lambda (x) (hash-ref code-map x)) s))

(define (morse-code s)
  (string-join (process (spacer (string->list (string-upcase s))))))

; Funkcja redukuje łańcuchy białych znaków
(define (spacer s)
  (if (or (null? s) (null? (rest s)))
      (cons (transfer (car s)) null)
      (if (and (char-whitespace? (car s)) (char-whitespace? (cadr s)))
          (spacer (rest s))
          (cons (transfer (car s)) (spacer (rest s))))))
; Funkcja pomocnicza do zamiany białych znaków na #\space
(define (transfer x)
  (cond
    [(null? x) null]
    [(char-whitespace? x) #\space]
    [else x]))

; ZADANIE 5 2/2
; Decoder
(define (val-key val) 
  (filter (lambda (x) (equal? (hash-ref code-map x) val)) (hash-keys code-map)))

(define (morse-decode s)
 (list->string (flatten (map (lambda (x) (val-key x)) (string-split s " ")))))


















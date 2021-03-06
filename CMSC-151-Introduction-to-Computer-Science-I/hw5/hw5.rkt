;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname hw5) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;; Jaime Arana-Rochel
;; aranarochel
;; CS151 Autumn 2012, Homework 5

(require 2htdp/image)
(require racket/match)

;; === Data Definitions ===

;; a date is a (make-date m d y)
;; for m, d, y numbers
(define-struct date (m d y))


;; Problem 1

;; any? : (α -> bool) (listof α) -> bool
;; return true if the test is true 
;; for any list element
(define (any? t αs)
  (cond
    [(empty? αs) false]
    [(cons? αs)
     (if (boolean=? true (first (map t αs))) 
         true (any? t (rest αs)))]))
(check-expect (any? odd? (list 1 2 3)) true)
(check-expect (any? boolean? (list 1 2 3)) false)
(check-expect (any? cons? (list 1 (list 1) 3)) true)


;; every? : (α -> bool) (listof α) -> bool
;; return true if the test is true
;; for every list element
(define (every? t αs)
  (cond
    [(empty? αs) true]
    [(cons? αs)
     (if (boolean=? true (first (map t αs)))
         (every? t (rest αs)) false)]))
(check-expect (every? odd? (list 1 3 5)) true)
(check-expect (every? boolean? (list true 1 true)) false)
(check-expect (every? cons? (list #f 2 (list 1))) false)


;; Problem 2


;; circles : num (listof color) -> (listof image)
;; given a radius in pixels, return a list 
;; of solid circles,one per color
(define (circles n cs)
  (cond
    [(and (empty? cs) (zero? n)) empty]
    [(and (cons? cs) (zero? n)) (list empty-image)]
    [(and (empty? cs) (positive? n)) empty]
    [(and (cons? cs) (positive? n))
     (map (lambda (c) (circle n "solid" c)) cs)]))
(check-expect (circles 10 (list "red" "blue"))
              (list (circle 10 "solid" "red")
                    (circle 10 "solid" "blue")))
(check-expect (circles 0 (list "red")) (list empty-image))
(check-expect (circles 0 empty) empty)
(check-expect (circles 2 empty) empty)


;; in-interval : num num (listof num) -> (listof num)
;; given an inclusive lower bound and an inclusive upper bound
;; return a list of those numbers that are in the interval
(define (in-interval n1 n2 ns)
  (cond
    [(empty? ns) empty]
    [(> n1 n2) empty]
    [(cons? ns)
     (filter (lambda (n) (<= n1 n n2)) ns)]))
(check-expect (in-interval 1 10 (list 1 5 12 2 30))
              (list 1 5 2))
(check-expect (in-interval 0 2 empty) empty)
(check-expect (in-interval 4 3 (list 1 2)) empty)


;; caps : (listof string) -> (listof string)
;; returns those strings in the list
;; that begin with capital letters
(define (caps ss)
  (cond
    [(empty? ss) empty]
    [(cons? ss)
     (filter (lambda (s) 
               (string-upper-case? (string-ith s 0)))
             ss)]))
(check-expect (caps empty) empty)
(check-expect (caps (list "Ball" "red" "Two"))
              (list "Ball" "Two"))


;; firsts : (listof string) -> (listof char)
;; returns the first character of every string
(define (firsts ss)
  (cond
    [(empty? ss) empty]
    [(cons? ss)
     (map (lambda (s) (string-ref s 0)) ss)]))
(check-expect (firsts empty) empty)
(check-expect (firsts (list "cat" "Ball"))
              (list #\c #\B))


;; count-color : color image -> num
;; count the occurrences of the given color
(define (count-color c1 img)
  (cond
    [(equal? img empty-image) 0]
    [else
     (length (filter (lambda (c) (equal? c1 c)) 
                     (image->color-list img)))]))
(check-expect (count-color (make-color 0 0 0) empty-image) 0)
(check-expect (count-color 
               (make-color 0 0 0) 
               (square 2 "solid" (make-color 0 0 0))) 4)


;; identity-matrix : nat -> (listof (listof num))
;; constructs the identity matrix of a given dimension
(define (identity-matrix n)
  (cond
    [(zero? n) empty]
    [else 
     (build-list n (lambda (x) 
                     (build-list n (lambda (y) (if (= x y) 1 0)))))]))
(check-expect (identity-matrix 0) empty)
(check-expect (identity-matrix 3) 
              (list (list 1 0 0) (list 0 1 0) (list 0 0 1)))


;; Problem 3

;; deriv : (num-> num) num -> (num-> num)
;; constructs the numerical derivative
;; of a given function, with given h value
(define (deriv f h)
  (local {;; f-prime : num -> num
          (define (f-prime x)
            (/ (- (f (+ x h)) 
                  (f x)) h))}
    f-prime))
(check-expect ((deriv (lambda (x) (+ (* x x) (* 2 x))) 0.001) 1)
              4.001)
(check-expect ((deriv (lambda (x) (+ (* x x) (* 2 x))) 0.001) 3)
              8.001)


;; Problem 4

;; divides? : num num -> bool
;; does the first number divide the second?
(define (divides? candidate n)  
  (zero? (remainder n candidate)))
(check-expect (divides? 2 4) true)
(check-expect (divides? 4 2) false)

;; leap? : year -> bool
;; test for leap years
(define (leap? y)  
  (or (divides? 400 y)     
      (and (divides? 4 y) (not (divides? 100 y)))))
(check-expect (leap? 2012) true)
(check-expect (leap? 2013) false)
(check-expect (leap? 2000) true)
(check-expect (leap? 1900) false)

;; adj : num num -> num
;; "month adjustment" (part of the day-of-week formula)
(define (adj m y)  
  (cond  
    [(= m 1) (if (leap? y) 0 1)]    
    [(= m 2) (if (leap? y) 3 4)]   
    [(= m 3) 4]  
    [(= m 4) 0]   
    [(= m 5) 2]   
    [(= m 6) 5]    
    [(= m 7) 0]   
    [(= m 8) 3]   
    [(= m 9) 6]   
    [(= m 10) 1]  
    [(= m 11) 4]   
    [(= m 12) 6]))
(check-expect (adj 1 2000) 0)
(check-expect (adj 2 2000) 3)
(check-expect (adj 2 2001) 4)
(check-expect (adj 3 2000) 4)
(check-expect (adj 4 2000) 0)
(check-expect (adj 5 2000) 2)
(check-expect (adj 6 2000) 5)
(check-expect (adj 7 2000) 0)
(check-expect (adj 8 2000) 3)
(check-expect (adj 9 2000) 6)
(check-expect (adj 10 2000) 1)
(check-expect (adj 11 2000) 4)
(check-expect (adj 12 2000) 6)

;; day-of-week-index : date -> num
;; given date, return 0 for Sunday, 1 Monday, ..., 6 Saturday
(define (day-of-week-index t) 
  (match t    
    [(date m d y)     
     (local {(define n (+ (- y 1900) (adj m y) d (floor (/ y 4))))}      
       (remainder n 7))]))
(check-expect (day-of-week-index (make-date 1 1 1970)) 4)
(check-expect (day-of-week-index (make-date 1 1 1971)) 5)

;; day-of-week : date -> string
;; given date, return "Sunday", "Monday", ..., "Saturday"
(define (day-of-week t)  
  (list-ref    
   (list "Sunday" "Monday" "Tuesday" "Wednesday" "Thursday" "Friday" "Saturday")  
   (day-of-week-index t)))
(check-expect (day-of-week (make-date 1 1 1970)) "Thursday")
(check-expect (day-of-week (make-date 1 1 1971)) "Friday")

;; draw-row : num num -> img
;; draws a row of a given number of squares
;; given the square width
(define (draw-row n1 n)
  (cond
    [(zero? n1) empty-image]
    [else
     (beside (square (/ n 7) "outline" "black") (draw-row (sub1 n1) n))]))
"eyeball test: draw-row"
(draw-row 7 200)

;; cal-board : num num -> img
;; draws the calendar board, (without dates)
;; given the calendar width and rows
(define (cal-board n r)
  (cond
    [(zero? r) empty-image]
    [else
     (above (draw-row 7 n)
            (cal-board n (sub1 r)))]))
"eyeball test: cal-board"
(cal-board 200 7)



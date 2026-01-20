#lang racket

;; често използвани функции
(define (id x) x)
(define (1+ x) (+ x 1))
(define (compose f g) (lambda (x) (f (g x))))

;; натрупване от по-висок ред
(define (accumulate op nv a b term next)
  (if (> a b) nv
      (op (term a) (accumulate op nv (next a) b term next))))

;; функции от по-висок ред за списъци
(define (filter p? l)
  (cond ((null? l) l)
        ((p? (car l)) (cons (car l) (filter p? (cdr l))))
        (else (filter p? (cdr l)))))

(define (foldr op nv l)
  (if (null? l) nv
      (op (car l) (foldr op nv (cdr l)))))

(define (foldl op nv l)
  (if (null? l) nv
      (foldl op (op nv (car l)) (cdr l))))

(define (foldr1 op l)
  (if (null? (cdr l)) (car l)
      (op (car l) (foldr1 op (cdr l)))))

(define (foldl1 op l)
  (foldl op (car l) (cdr l)))

(define (search p l)
  (and (not (null? l)) (or (p (car l)) (search p (cdr l)))))

(define (all? p? l)
  (not (search (lambda (x) (not (p? x))) l)))

;; Задача 1

(define (repeat x n)
  (if (= n 0)
      '()
      (cons x (repeat x (- n 1)))))

(define (encode lst)
  (define (pack x n)
    (if (>= n 2)
        (cons n x)
        x))

  (define (loop rest current count)
    (cond
      ((null? rest)
       (list (pack current count)))

      ((equal? (car rest) current)
       (loop (cdr rest) current (+ count 1)))

      (else
       (cons (pack current count)
             (loop (cdr rest) (car rest) 1)))))

  (if (null? lst)
      '()
      (loop (cdr lst) (car lst) 1)))

(define (decode rle)
  (cond
    ((null? rle) '())
    ((pair? (car rle))
     (append
      (repeat (cdar rle) (caar rle))
      (decode (cdr rle))))
    (else
     (cons (car rle) (decode (cdr rle))))))

(define (split-at lst n)
  (cond
    ((= n 0) (cons '() lst))
    ((null? lst) (cons '() '()))
    (else
     (let ((res (split-at (cdr lst) (- n 1))))
       (cons (cons (car lst) (car res))
             (cdr res))))))

(define (insert l1 l2 i)
  (let* ((xs (decode l1))
         (ys (decode l2))
         (sp (split-at xs i)))
    (encode (append (car sp) ys (cdr sp)))))

; (encode '(1 1 2 3 3 4))
; (decode '((2 . 1) 2 (2 . 3) 4))
; (insert '(1 2 (6 . 8) 9) '((8 . 3)) 4)


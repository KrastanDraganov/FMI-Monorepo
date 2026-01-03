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

;; Решение - зад. 1

(define (divides? d n)
  (= (remainder n d) 0))

(define (smallest-divisor n)
  (define (iter d)
    (if (divides? d n) d
        (iter (+ d 1))))
  (iter 2))

(define (sum-digits n)
  (if (< n 10)
      n
      (+ (remainder n 10) (sum-digits (quotient n 10)))))

(define (sumDig n)
  (sum-digits (smallest-divisor n)))

;; Решение - зад. 2

(define (empty-tree? t) (null? t))

(define (node t)  (car t))

(define (left t)  (cadr t))

(define (right t) (caddr t))

(define (size t)
  (if (empty-tree? t) 0
      (+ 1 (size (left t)) (size (right t)))))

(define (tree=? a b)
  (cond
    [(and (empty-tree? a) (empty-tree? b)) #t]
    [(or  (empty-tree? a) (empty-tree? b)) #f]
    [else (and (equal? (node a) (node b))
               (tree=? (left a)  (left b))
               (tree=? (right a) (right b)))]))

(define (subtree-of? S T)
  (cond
    [(empty-tree? S) #t]
    [(empty-tree? T) #f]
    [(tree=? S T)  #t]
    [else (or (subtree-of? S (left T))
              (subtree-of? S (right T)))]))

(define (count-subtrees-of T L)
  (length (filter (lambda (S) (subtree-of? S T)) L)))

(define (better T1 T2 L)
  (define c1 (count-subtrees-of T1 L))
  (define c2 (count-subtrees-of T2 L))
  (cond
    [(> c1 c2) T1]
    [(< c1 c2) T2]
    [else (if (< (size T1) (size T2)) T1 T2)]))

(define (inSuperTree L)
  (cond
    [(null? (cdr L)) (car L)]
    [else
     (foldl (lambda (acc t) (better acc t L)) (car L) (cdr L))]))

;; Решение - зад. 3

(define (my-foldr op nv l)
  (if (null? l) nv
      (op (car l) (my-foldr op nv (cdr l)))))

(define (my-foldl op nv l)
  (if (null? l) nv
      (my-foldl op (op nv (car l)) (cdr l))))

(define (my-map f l)
  (my-foldr (lambda (x acc) (cons (f x) acc)) '() l))

(define (my-filter p l)
  (my-foldr (lambda (x acc) (if (p x) (cons x acc) acc)) '() l))

(define (my-concat a b)         
  (my-foldr cons b a))

(define (sum l)
  (my-foldl + 0 l))

(define (prefixes l)
  (define acc0 (cons '() '()))
  (define accF
    (my-foldl
     (lambda (acc x)
       (let* ([cp   (car acc)]
              [res  (cdr acc)]
              [new-cp  (append cp (list x))]
              [new-res (cons new-cp res)])
         (cons new-cp new-res)))
     acc0
     l))
  (reverse (cdr accF)))

(define (tails l)
  (my-foldr
   (lambda (x acc)
     (cons (cons x (if (null? acc) '() (car acc))) acc))
   '()
   l))

(define (contiguous-subs l)
  (my-foldl
   (lambda (acc t) (my-concat acc (prefixes t)))
   '()
   (tails l)))

(define (pick-shortest lists)
  (my-foldl
   (lambda (best cur)
     (cond
       [(null? best) cur]
       [(< (length cur) (length best)) cur]
       [else best]))
   '()
   lists))

(define (minSub f l)
  (define valid
    (my-filter (lambda (sub) (= (f (sum sub)) 0))
               (contiguous-subs l)))
  (if (null? valid) '()
      (pick-shortest valid)))

#lang racket

(define (looksLikeComb x)
  (cond
    ((not (pair? x)) #t)

    ((null? x) #t)

    (else
      (let ((f (car x)))
        (and
          (ok-first? f)
          (all looksLikeComb x))))))

(define (ok-first? f)
  (or (procedure? f)
      (lambda-form? f)))

(define (lambda-form? f)
  (and (pair? f)
       (list? f)
       (= (length f) 3)
       (eq? (car f) 'lambda)))

(define (all p xs)
  (cond
    ((null? xs) #t)
    (else (and (p (car xs)) (all p (cdr xs))))))

;; (looksLikeComb (list + 5 (list (list 'lambda '(x) 'x) 10)))
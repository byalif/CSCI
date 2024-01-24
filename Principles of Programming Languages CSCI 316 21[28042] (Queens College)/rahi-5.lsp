;;Alif Rahi
;;Assignment 5

;; n= 1
;;         ^
;; L= (1 2 3 4 5)
;;1
(defun INDEX (n L)
(cond 
    ((null L) 'ERROR)
    ((= n 1) (car L))
    ((= n 0) 'ERROR)
    (T (INDEX (- n 1) (cdr L)))
))

;;               ^
               ;(  34) X
;; (1 2 3 4 5 0 -1 34) L

;; (-1 1 2 3 4 5 0 34)



(defun insert-d (x L)
 (cond 
   ((null L) (list x))
   ((>= x (car L)) (cons x L))
   (T (cons (car L) (insert-d x (cdr L))))
 )
)


(defun count-repetitions (L)
(cond ((endp L (cdr L) (list (cons 1 L))))
      (T (let ((X (count-repetitions (cdr L))))
         (if (equal (car L) (cadr L))
         (cons (+ 1 ))
         X
)))))




(defun remove-adj-dupl (L)
(if (endp (cdr L))
L
  
      (if (equal (car L) (cadr L))
      (remove-adj-dupl (cdr L))
      (cons (car L) (remove-adj-dupl (cdr L)) )

)
)


(defun )

;;2
(defun MIN-FIRST (L)
(cond ((null L) L)
;;       x = null
      (T (let ((X (MIN-FIRST (cdr L))))
        (cond 
        ((null X) L)
        ((> (car L) (car X)) (append (list (car X)) (list (car L)) (cdr X)))
        (T L)
        )
      ))
))

;;3
(defun SSORT (L)
    (if (null L)
    L
        (let ((X (MIN-FIRST L)))
        (cons (car X) (SSORT (cdr X)))
        )
    )
)

;;4 
(defun qsort (L)
 (if (null L)
 L
 (let ((pL (PARTITION (cdr L) (car L))))
 (append (qsort (car pL)) (cons (car L ) (qsort (cadr pL))) )
 )))


;;5
(defun MERGE-LISTS (L1 L2)
(cond ((null L1) L2)
      ((null L2) L1)
      (T 
      (if (<= (car L1) (car L2))
        (cons (car L1) (MERGE-LISTS (cdr L1) L2) )
        (cons (car L2) (MERGE-LISTS L1 (cdr L2)) )
      ))
))


;;
(cons (append (list (second (first E))) (list (first (first E)))) (list (first (second E))  (cdr (third E))))


(defun tr-add (L res) 
(if (endp L) res
   (tr-add (cdr L) (+ res (car L)))
)
)


(defun repeated-elts (L)
   (cond
   ((endp L) NIL)
   ((not (eq1 (car L) (cadr L))) ; e.g, L = (6 5 ...) or (7) [see examples C and A1]
   (repeated-elts (cdr L)))
   ((not (eq1 (car L) (caddr L))) ; e.g, L = (6 6 4 ...) or (7 7) [see examples D & A2]
   (cons (car L) (repeated-elts (cddr L))
   ))
   (t (repeated-elts (cdr L))))) ; e.g, L = (6 6 6 4 ....
   )


(if (or (numberp a ) (numberp b) 'BAD-ARG
(/(+ a b ) 2))
)


(defun remove-if2 (f L)
(cond ((null L) L)
   (T (let ((X (remove-if2 f (cdr L))))
   (if (funcall f (car L)) 
   X
   (cons (car L) X)
   )
   ))
))


)) 'NIL)

(/(+ a b ) 2))

;;6
(defun MSORT (N)
   (if (endp (cdr N))
       N
       (let* ((Z (split-list N)))
          (let ((x (MSORT (car Z)))
		(y (MSORT (cadr Z))))
		(MERGE-LISTS x y)))))

;;7
(defun REMOVE-ADJ-DUPL (L)
   (if (endp L)
        nil
	(let ((x (REMOVE-ADJ-DUPL (cdr L))))
	      (if (equalp (car L) (car x))
	           x
		  (cons (car L) x)))))

;;8
(defun UNREPEATED-ELTS (L)
   (cond ((endp L) nil)
         ((or (endp (rest L)) (not (equal (first L)(second L)))) (cons (first L)(UNREPEATED-ELTS (rest L))))
         ((or (endp (cddr L)) (not (equal (first L)(third L)))) (UNREPEATED-ELTS (cddr L)))
         (t (UNREPEATED-ELTS (rest L)))))


;;9
(defun REPEATED-ELTS (L)
   (cond ((endp L) nil)
         ((or (endp (cdr L)) (not (equal (car L) (cadr L)))) (REPEATED-ELTS (cdr L)))
	 ((or (endp (cddr L)) (not (equal (car L) (caddr L)))) (cons (car L) (REPEATED-ELTS (cddr L))))
	 (t (REPEATED-ELTS (cdr L)))))

;;10
(defun COUNT-REPETITIONS (L)
   (if (endp L)
	nil
	(let ((x (COUNT-REPETITIONS (cdr L))))
	   (if (equal (car L) (cadr L))
	       (append (list (list (+ 1 (caar x)) (cadar x))) (cdr x))
	       (append (list (list 1 (car L))) x)))))

;;11
(defun SUBSET (f L)
   (if (endp L)
	nil
	(let ((x (SUBSET f (cdr L))))
	   (if (funcall f (car L))
	       (cons (car L) x)
		x))))

;;12.1
(defun OUR-SOME (f L)
   (if (endp L)
	nil
	(let ((x (OUR-SOME f (cdr L))))
	   (if (funcall f (car L))
		L
		x))))

;;12.2
(defun OUR-EVERY (f L)
   (if (endp L)
	t
	(let ((x (OUR-EVERY f (cdr L))))
	   (if x (funcall f (car L))))))

;;13
(defun PARTITION1 (f L p)
   (if (endp L)
       (list nil nil)
       (let ((x (PARTITION1 f (cdr L) p)))
		(cond ((funcall f (car L) p)
		      (append (list (cons (car L) (car x))) (list (cadr x))))
		      (t (append (list (car x)) (list (cons (car L) (cadr x)))))))))

(defun QSORT1 (f L)
   (cond ((endp L) nil)
	 (t (let ((Z (PARTITION1 f L (car L))))  
	          (cond ((endp (car Z)) (cons (car L) (QSORT1 f (cdr L))))
		        (t (let ((x (QSORT1 f (car Z)))
		                (y (QSORT1 f (cadr Z)))) 
			        (append  x  y))))))))

;;14
(defun FOO (f L)
   (if (endp L) 
       () 
       (let* ((x (FOO f (cdr L))) (ls (cdr L))
	     (Z (list (cons (funcall f (car L)) ls)))
	     (Y (mapcar (lambda (a) (cons (car L) a)) x)))
	     (append Z Y))))
;;15a
(defun TR-ADD (L acc)
   (if (endp L)
	acc
	(TR-ADD (cdr L) (+ (car L) acc))))
(defun TR-MUL (L acc)
   (if (endp L)
	acc
	(TR-MUL (cdr L) (* (car L) acc))))
(defun TR-FAC (x acc)
   (if (zerop x)
	acc
	(TR-FAC (- x 1) (* x acc))))

;;15b
(defun SLOW-PRIMEP (N)
  (if (equal (mod (TR-FAC (- N 1) 1) N) (- N 1))
      t
      nil))

;;16a
(defun TRANSPOSE1 (m)
   (cond ((endp (cdr m)) (mapcar #'list (car m)))
	 (t (mapcar #'cons (car m) (TRANSPOSE1 (cdr m))))))
;;16b
(defun TRANSPOSE2 (m)
   (cond ((endp (cdar m)) (list (mapcar #'car m)))
	 (t (cons (mapcar #'car m) (TRANSPOSE2 (mapcar #'rest m))))))
;;16c
(defun TRANSPOSE3 (m)
   (apply #'mapcar #'list m))
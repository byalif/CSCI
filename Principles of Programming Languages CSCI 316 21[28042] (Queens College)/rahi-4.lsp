;;Alif Rahi


;;SECTION 1 (Nonrecursive Preliminary Problems)

;;A
(defun my-sum (L)
 (let ((X (sum (cdr L))))
        (+ (car L) X)
 ))

 ;;B
 (defun my-neg-nums (L)
 (let ((X (neg-nums (cdr L))))
        (if (>= (car L) 0)
        X
        (cons (car L) X)
        )
))

;;C
(defun my-inc-list-2 (L n)
 (let ((X (inc-list-2 (cdr L) n)))
    (if (null (car L)) 
    X
    (cons (+ n (car L)) X)) 
 ))

 ;;D
 (defun my-insert (n L)
    (if (<= n (car L))
    (cons n L)
    (let ((X (insert n (cdr L))))
        (cons (car L) X)
    ))
 )

 ;;E
 (defun my-isort (L)
 (let ((X (isort (cdr L))))
    (if (<= (car L) (car X))
    (cons (car L) X)
    (INSERT (car L) X))
 ))

 ;;F
 (defun my-split-list (L)
 (let ((X (split-list (cdr L))))
 (list (cons (car L) (second X)) (first X))
))

;;G
(defun my-partition (L p)
 (let ((X (partition (cdr L) p)))
    (if (< (car L) p)
    (list (cons (car L) (car X)) (second X))
    (list (car X) (cons (car L) (second X)))
 )))


;;SECTION 2 (Main Problems)

 ;;1
 (defun SUM (L)
    (if (null L)
    0
    (+ (car L) (SUM (cdr L)))
    )
)

 ;;2
 (defun NEG-NUMS (L)
    (if (null L)
    L
    (let ((X (NEG-NUMS (cdr L))))
        (if (< (car L) 0)
        (cons (car L) X)
        X
        )
)))

 ;;3
 (defun INC-LIST-2 (L n)
    (if (null L)
    L
    (let ((X (INC-LIST-2 (cdr L) n)))
        (cons (+ (car L) n) X)
)))

;;4
(defun INSERT (N L)
    (if (null L)
    L
        (if (<= N (car L)) 
        (cons N L)
        (cons (car L) (INSERT N (cdr L)))
        )
    )
)

;;5
(defun ISORT (L)
    (if (null L)
    L
    (let ((X (ISORT (cdr L))))
        (INSERT (car L) X)
    )
    )
)

;;6
(defun SPLIT-LIST (L)
  (cond ((endp L) (list () ()))
        (T (let ((X (SPLIT-LIST (cdr L))))
             (list (cons (car L) (cadr X)) (car X))))))



;;6
(defun SPLIT-LIST (L)
    (if (null L)
    L
    (let ((X )))
    )
)

;;7
(defun PARTITION (L P)
  (cond ((endp L) (list () ()))
        ((or (not (numberp (car L))) (not (numberp P))) NIL)
        (T (let ((X (PARTITION (cdr L) P)))
             (cond ((< (car L) P) (list (cons (car L) (car X)) (cadr X)))
                   (T (list (car X) (cons (car L)(cadr X)))))))))


;;7
(defun PARTITION (L N)
 (if (null L)
 (list () ())
    (let ((X (PARTITION (cdr L) N)))
    (if (< (car L) N)
    (list (cons (car L) (first X)) (second X) )
    (list  (first X) (cons (car L) (second X)) )
))))

;;8
(defun POS (E L)
  (cond ((endp L) 0)
        ((equal E (car L)) 1)
        (T (let ((X (POS E (cdr L))))
             (if (= X 0)
               0
               (+ X 1))))))

(defun POS (E L)
    (if (null L)
    0
    (if (= (car L) E)
        1
        (let ((X (POS E (cdr L))))
        (if (= X 0)
        0
        (+ 1 X)
        )    
        )
        )
    )
)



;;9

(defun SPLIT-NUMS (N)
    (if (= N 0)
    (list (cons N nil) ())
    (let ((X (SPLIT-NUMS (- N 1))))
        (if (evenp N)
        (list (cons N (first X)) (second X))
        (list (first X) (cons N (second X)))
        )
    )
    )
)


;;9
(defun SPLIT-NUMS (N)
  (cond ((minusp N) NIL)
        ((zerop N) (list (list N) NIL))
        (T (let ((X (SPLIT-NUMS (- N 1))))
             (if (evenp N)
               (list (cons N (car X)) (cadr X))
               (list (car X) (cons N (cadr X))))))))

(defun SET-UNION (S1 S2)
    (cond ((null S1) S1)
          ((null S2) S2)
            (T (let ((X (SET-UNION (cdr S1) (cdr S2))))
            (if (member (car S1) X))
            X
            (cons (car S1) X)
            ))
    )
)

;;10
(defun SET-UNION (S1 S2)
  (cond ((endp S1) S2)
        (T (let ((X (SET-UNION (cdr S1) S2)))
             (if (member (car S1) X)
               X
               (cons (car S1) X)))))) 

;;11
(defun SET-REMOVE (Y S)
  (cond ((or (endp S) (not (atom Y))) NIL)
        (T (let ((X (SET-REMOVE Y (cdr S))))
             (if (or (member (car S) X) (eq (car S) Y))
               X
               (cons (car S) X))))))

(defun SET-REMOVE (Y S)
    (if (null S)
    S
        (if (not (member Y S))
        S
            (let ((X (SET-REMOVE Y (cdr S))))
                (if (= (car S) Y)
                X
                (cons (car S) X)
                )
            )
        )
    )

)

(defun SET-EXCL-UNION (S1 S2)
(if (null S1)
    S2
    (let ((X (SET-EXCL-UNION (cdr S1) S2)))
        (if (member (car S1) X)
        (SET-REMOVE (car S1) X)
        (cons (car S1) X)
        )
    )
)
)

;;12
(defun SET-EXCL-UNION (S1 S2)
  (cond ((endp S1) S2)
        (T (let ((X (SET-EXCL-UNION (cdr S1) S2)))
             (if (member (car S1) X)
               (SET-REMOVE (car S1) X)
               (cons (car S1) X))))))
;;13

;; (1 2 3 4 4 5 5 1)
;; (2 3)
(defun SINGLETONS (E)
    (if (null E)
    E
    (let ((X (SINGLETONS (rest E))))
             (if (member (first E) (rest E))
               (SET-REMOVE (first E) X)
               (cons (first E) X))) 
    )
)




;;
(defun my-index (n L)
(cond ((= 1 n) (car L))
    ((= 0 n) 'ERROR)
    (T (let ((X (index (- n 1) (cdr L))))
    X
    ))
))

;;
(defun my-min-first (L)
 (let ((X (min-first (cdr L))))
 (if (> (car L) (car X))
 (append (list (car X)) (list (car L)) (cdr X))
 L
 )
 )
)

;;
(defun my-ssort (L)
 (let* ((L1 (min-first L))
 (X (ssort (cdr L1))))
 (cons (car L1) X)
 ))

;;Assignment 5

;;1
(defun INDEX (n L)
(cond 
    ((null L) 'ERROR)
    ((= 1 n) (car L))
    ((= 0 n) 'ERROR)
    (T (INDEX (- n 1) (cdr L)))
))

;;2
(defun MIN-FIRST (L)
(cond ((endp L) L)
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
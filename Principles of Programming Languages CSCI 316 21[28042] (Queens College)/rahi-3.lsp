;;Alif Rahi

;;1
(defun MIN-2 (A B) 
(cond 
((not (numberp A)) 'ERROR ) 
((not (numberp B)) 'ERROR )
((> A B) B) 
((< A B) A)
)
)


;;2
(defun SAFE-AVG (x y)
(cond
( (not (numberp x)) NIL)
( (not (numberp y)) NIL)
( (/ (+ x y) 2))
) )


;;3
(defun ODD-GT-MILLION (x)
(cond
( (not (integerp x)) NIL) 
( (= 0 (mod x 2)) NIL) 
( (> x 1000000) T)
( NIL ) ))

;;4
(defun MULTIPLE-MEMBER(a b)
(if (not (and (or (symbolp a) (numberp a)) (listp b))) 'NIL
(member a (cdr (member a b)))))

;;5
(defun MONTH->INTEGER (x)
(cond
((not (symbolp x)) 'ERROR)
((eq x 'JANUARY) 1)
((eq x 'FEBRUARY) 2)
((eq x 'MARCH) 3)
((eq x 'APRIL) 4)
((eq x 'MAY) 5)
((eq x 'JUNE) 6)
((eq x 'JULY) 7)
((eq x 'AUGUST) 8)
((eq x 'SEPTEMBER) 9)
((eq x 'OCTOBER) 10)
((eq x 'NOVEMBER) 11)
((eq x 'DECEMBER) 12)
('ERROR)
)
)

;;6
(defun SCORE->GRADE (x)
(cond
((not (numberp x)) NIL)
((>= x 90) 'A)
((>= x 87) 'A-)
((>= x 83) 'B+)
((>= x 80) 'B)
((>= x 77) 'B-)
((>= x 73) 'C+)
((>= x 70) 'C)
((>= x 60) 'D)
((< x 60) 'F)
)
)

;;7
(defun GT (x y)
(and (numberp x) (numberp y) (> x y)))

;;8
(defun SAME-PARITY (x y) 
(and 
(and (integerp x) (integerp y))
(or (and (evenp x) (evenp y))
(and (oddp x) (oddp y)))
))

;;9
(defun SAFE-DIV (a b)
(and
(and 
(and (numberp a) (numberp b))
(not(zerop b)))
(and (/ a b))))



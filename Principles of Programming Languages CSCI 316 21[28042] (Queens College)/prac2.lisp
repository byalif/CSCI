(defun MIN-2 (A B) 
(cond 
((not (numberp A)) 'ERROR ) 
((not (numberp B)) 'ERROR )
((> A B) B) 
((< A B) A)
)
)

(print(MIN-2 'g0 2))
;------- Data Area
@ /0000
MAIN JP INICIO
ZERO K /0000
hello K /0000
0temp K /0000 ; Anonymous Expression
1temp K =5

;------- Code Area
INICIO LD ZERO
LD 1temp
MM 0temp
LD 0temp ; Result of Anonymous Expression
MM hello ; Assignment

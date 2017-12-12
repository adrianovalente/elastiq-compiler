;------- Data Area
@ /0000
MAIN JP INICIO
ZERO K /0000
UM K /0001
hello K /0000
world K /0000
0temp K /0000 ; Anonymous Expression
1temp K =5
2temp K /0000 ; Anonymous Expression
3temp K =2
4temp K /0000
5temp K =3
6temp K /0000

;------- Code Area
INICIO LD ZERO
LD 1temp
MM 0temp
LD 0temp ; Result of Anonymous Expression
MM hello ; Assignment
LD hello
* 3temp
MM 4temp
LD 4temp
+ 5temp
MM 6temp
LD 6temp
MM 2temp
LD 2temp ; Result of Anonymous Expression
MM world ; Assignment
FIM HM FIM
# MAIN

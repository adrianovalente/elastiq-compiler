;------- Data Area
@ /0000
MAIN JP INICIO
ZERO K /0000
a K /0000
b K /0000
0temp K /0000 ; Anonymous Expression
1temp K =4
2temp K /0000 ; Anonymous Expression
3temp K =2
4temp K /0000 ; Anonymous Expression
5temp K =4
7temp K /0000 ; Anonymous Expression
8temp K =3

;------- Code Area
INICIO LD ZERO
LD 1temp
MM 0temp
LD 0temp ; Result of Anonymous Expression
MM a ; Assignment
LD 3temp
MM 2temp
LD 2temp ; Result of Anonymous Expression
MM b ; Assignment
LD a ; First logical operator
- 5temp ; Second logical operator
- UM
JN 6tempsalva0
LD UM
MM 6temp
JP 6tempfinal
MM 6temp
6tempfinal LD ZERO
LD 6temp
MM 4temp
LD 4temp ; Condition is here!
JZ 4tempendif ; Evaluating Conditional
LD 8temp
MM 7temp
LD 7temp ; Result of Anonymous Expression
MM b ; Assignment
4tempendif LD ZERO

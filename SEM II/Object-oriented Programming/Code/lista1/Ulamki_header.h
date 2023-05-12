/*
* Piotr Stachowicz
* wykład PO: Ulamki (Zadanie 2 lista6 1)
* gcc Ulamki.c
*/

#include "stdio.h"
#include "stdlib.h"


typedef struct Ulamek{
    int num;
    int denom;
}Ulamek;
int NWW(int a, int b);
int NWD(int a, int b);
Ulamek* nowy_ulamek(int num, int denom);
Ulamek* add_v1(Ulamek* ulamek1, Ulamek* ulamek2);
Ulamek* sub_v1(Ulamek* ulamek1, Ulamek* ulamek2);
Ulamek* mul_v1(Ulamek* ulamek1, Ulamek* ulamek2);
Ulamek* div_v1(Ulamek* ulamek1, Ulamek* ulamek2);
void add_v2(Ulamek* ulamek1, Ulamek* ulamek2);
void sub_v2(Ulamek* ulamek1, Ulamek* ulamek2);
void mul_v2(Ulamek* ulamek1, Ulamek* ulamek2);
void div_v2(Ulamek* ulamek1, Ulamek* ulamek2);
void show(Ulamek *u);
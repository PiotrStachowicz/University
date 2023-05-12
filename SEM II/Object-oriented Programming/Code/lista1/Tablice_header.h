/* Piotr Stachowicz
* wykład PO: Tablice (Zadanie 3 lista6 1)
* gcc Tablice.c
*/
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
typedef struct Tablica{
    int min_index;
    int max_index;
    float *t;
}Tablica;
Tablica* nowa_tablica();
void dodaj(Tablica* tablica, int idx, float value);
void show(Tablica* tablica);
float indeks(Tablica* tablica, int idx);

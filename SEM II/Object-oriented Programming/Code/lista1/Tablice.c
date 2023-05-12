#include "Tablice_header.h"
int main(void){
    Tablica* tab = nowa_tablica();
    dodaj(tab,1,1.0);
    dodaj(tab,3,3.0);
    dodaj(tab,2,2.0);
    dodaj(tab,-1,-1.0);
    dodaj(tab,-3,-3.0);
    dodaj(tab,-2,-2.0);
    printf("%f\n", indeks(tab,-3));
    show(tab);
    return 0;
}
Tablica* nowa_tablica(){
    Tablica* nowa_tablica = malloc(sizeof(Tablica));
    nowa_tablica->max_index = -1;
    nowa_tablica->min_index = 0;
    nowa_tablica->t = NULL;
    return nowa_tablica;
}
void dodaj(Tablica* tablica, int idx, float value){
    if(idx == tablica->max_index)
    if (idx > tablica->max_index) {
        int new_size = idx - tablica->min_index + 1;
        float* new_t = malloc(sizeof(float)*new_size);
        memcpy(new_t,tablica->t,sizeof(float)*(tablica->max_index - tablica->min_index + 1));
        free(tablica->t);
        tablica->t = new_t;
        tablica->max_index = idx;
    }
    if (idx < tablica->min_index) {
        int new_size = tablica->max_index - idx + 1;
        float* new_t = malloc(sizeof(float) * new_size);
        int offset = -(idx - tablica->min_index);
        memcpy(&new_t[offset], tablica->t, sizeof(float) * (tablica->max_index - tablica->min_index + 1));
        free(tablica->t);
        tablica->t = new_t;
        tablica->min_index = idx;
    }
    tablica->t[idx - tablica->min_index] = value;
}
void show(Tablica* tablica){
    for(int i = 0; i<tablica->max_index-tablica->min_index+1;i++){
        printf("%f | ",tablica->t[i]);
    }
    putchar('\n');
}
float indeks(Tablica* tablica, int idx){
    return tablica->t[idx-tablica->min_index];
}
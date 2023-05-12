#include <stdio.h>
#include <ctype.h>
#include <math.h>
int main(void){
    static char tab[1001];
    int c;
    int n = 0;
    while ((c = getchar()) != '\n') {
        if(isgraph(c)==0){
            printf("Podano niedrukowanly znak!");
            return 1;
        }
        tab[n] = c;
        n++;
    }
    printf("----------\n");
    double ilosc_wszystkich = n;
    int wypis = 0;
    double nadpis = 0.0;
    for(int i = 0;i<n;i++){
        int character = tab[i];
        double ilosc_charactera = 0;
        int ilosc_do_wypisania;
        if(character != '0'){
            for(int j = 0;j<n;j++){
                if(tab[j]==character){
                    ilosc_charactera++;
                    tab[j] = '0';
                }
            }
            ilosc_do_wypisania = (ilosc_charactera*100.0)/ilosc_wszystkich;
            double ulamek = ilosc_charactera*100.0/ilosc_wszystkich - ilosc_do_wypisania;
            nadpis = nadpis + ulamek;
            if(ilosc_do_wypisania<1){
                printf("%c", character);
                nadpis = nadpis - 1.0;
                wypis++;
            }
            for(int k = 0;k<ilosc_do_wypisania;k++){
                if(round(nadpis)>=1.0){
                    printf("%c", character);
                    wypis++;
                    nadpis = nadpis - 1.0;
                    if(wypis%10==0) {
                        putchar('\n');
                    }
                }
                printf("%c", character);
                wypis++;
                if(wypis%10==0) {
                    putchar('\n');
                }
                }
            }
        }
    printf("----------\n");
    return 0;
    }
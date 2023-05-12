#include<stdio.h>
int main(void) {
    int c;
    int tab[4] = {0,0,0,0};
    static char zam[20*1000*1000];
    int licznik_otwarc = -1;
    while((c=getchar())!='\n'){
        if(c=='('){
            tab[0] += 1;
            licznik_otwarc += 1;
            zam[licznik_otwarc] = ')';
        }else if(c=='['){
            tab[1] += 1;
            licznik_otwarc += 1;
            zam[licznik_otwarc] = ']';
        }else if(c=='{'){
            tab[2] += 1;
            licznik_otwarc += 1;
            zam[licznik_otwarc] = '}';
        }else if(c=='<'){
            tab[3] += 1;
            licznik_otwarc += 1;
            zam[licznik_otwarc] = '>';
        }else if(c==')'){
            tab[0] -= 1;
            if(c != zam[licznik_otwarc]){
                printf("N");
                return 1;
            }
            licznik_otwarc -= 1;
        }else if(c==']'){
            tab[1] -= 1;
            if(c != zam[licznik_otwarc]){
                printf("N");
                return 1;
            }
            licznik_otwarc -= 1;
        }else if(c=='}'){
            tab[2] -= 1;
            if(c != zam[licznik_otwarc]){
                printf("N");
                return 1;
            }
            licznik_otwarc -= 1;
        }else if(c=='>'){
            tab[3] -= 1;
            if(c != zam[licznik_otwarc]){
                printf("N");
                return 1;
            }
           licznik_otwarc -= 1;
        }
    }
    if(tab[0] > 0 || tab[1] > 0 || tab[2] > 0 || tab[3] > 0){
        printf("N");
        return 1;
    }
    printf("P");
    return 0;
}
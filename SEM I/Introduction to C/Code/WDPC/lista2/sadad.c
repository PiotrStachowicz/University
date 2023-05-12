#include <stdio.h>
#include <ctype.h>

int main(void)
{
    int tab[26]={};
    while(1){
        int c = getchar();
        int wskaznik_tablicy = tolower(c) - 97;
        if(c >= 'a' || c <= 'z'){
            if(tab[wskaznik_tablicy] == 0) {
                putchar(c);
                if(c <= 90){
                    tab[wskaznik_tablicy] = 2;
                }else{
                    tab[wskaznik_tablicy] = 1;
                }
            } else{
                if(tab[wskaznik_tablicy] != 0 && tab[wskaznik_tablicy] % 2 == 0){
                    int c2 = tolower(c);
                    putchar(c2);
                    tab[wskaznik_tablicy] += 1;
                } else{
                    int c2 = toupper(c);
                    putchar(c2);
                    tab[wskaznik_tablicy] += 1;
                }
            }
    } else{
            putchar(c);
        }
    }
    return 0;
}
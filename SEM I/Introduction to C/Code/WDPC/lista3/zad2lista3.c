#include <stdio.h>

int main(void) {
    static char tab[10001];
    int c;
    int n = 0;
    while ((c = getchar()) != EOF) {
        tab[n] = c;
        n++;
    }//wczytuje tablice znaków
    int dlugosc = n-1;
    while(dlugosc>0){
        int i = 0;
        int dlugosc_i = dlugosc + i;
        while(dlugosc_i<=n-1){
            int kopia_dlugosc_i = dlugosc_i;
            int s = 0;
            for(int k = i;k<kopia_dlugosc_i;k++){
                if(tab[k]==tab[kopia_dlugosc_i]){
                    s = s + 2;
                } else{
                    break;
                }
                kopia_dlugosc_i--;
            }
            if(s==dlugosc || s-1==dlugosc){
                for(int p = i;p<=dlugosc_i;p++){
                    printf("%c",tab[p]);
                }
                return 0;
            }
            i++;
            dlugosc_i++;
        }
        dlugosc--;
    }
    return 0;
}
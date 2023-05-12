#include <stdio.h>
int main(void){
    int n;
    if(scanf("%d", &n)!=1 || n > 1000000){
        return 1;
    }
    int tab[n+1];
    int zero_jeden[n+1];
    for(int j = 0; j<=n;j++){
        zero_jeden[j] = 0;
    }
    int i = 1;
    do{
        scanf("%d", &tab[i]);
        i++;
    } while(i<=n);
    int max = 1;
    int pocz;
    for(int j = 1;j<=n;j++){
        int dl = 1;
        pocz = j;
        int pointer = tab[j];
        zero_jeden[pointer] += 1;
        if(zero_jeden[pocz] == 0){
            while(pointer!=pocz){
                pointer = tab[pointer];
                zero_jeden[pointer] += 1;
                dl++;
                if(dl==n){
                    max = dl;
                    printf("%d", max);
                    return 0;
                }
            }
            if(dl>max){
                max = dl;
            }
        }
    }
    printf("%d", max);
    return 0;
}
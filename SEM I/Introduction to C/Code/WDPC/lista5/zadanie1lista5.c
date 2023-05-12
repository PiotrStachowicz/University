#include <stdio.h>
int w = 0,n;
long int tab[0];
int sequences(int p, int M,int s){
    if(M>10){
        return 0;
    }
    if (p==n) {
        if(s == 0){
            w += 1;
        }
        return 0;
    }
    int s1 = s + tab[p];
    sequences(p + 1, M + 1, s1);
    sequences(p + 1, M, s);
    return 0;
}
int main(void){
    scanf("%d", &n);
    for (int i=0;i<n;i++){
        scanf(" %ld", &tab[i]);
    }
    int p = 0, M = 0, s = 0;
    sequences(p, M, s);
    printf("Suma[%d]", w);
    return 0;
}
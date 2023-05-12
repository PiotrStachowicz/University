#include <stdio.h>
#include <stdlib.h>
#define MAX_N 100
#define MAX_D 65536
typedef long long int l;
l n;
__int128_t horner(l *wspolczynniki, long long int x, int d){
    __int128_t result2 = 0;
    for (int i = 0; i <=d; i++) {
        result2 = (result2 * (x%100000))%100000+wspolczynniki[i];
    }
    if(result2<0) result2*=(-1);
    return result2%100000;
}
int main(void){
    if(scanf("%lld", &n)!=1 || n>MAX_N || n<1) return 1;
    for(int i =0;i<n;i++){
        l x;
        l d;
        if(scanf("%lld %lld", &d, &x)!=2 || d>MAX_D) return 1;
        l *wspolczynniki = malloc((d + 1) * sizeof(l));
        for (int j = 0; j <= d; j++) {
            if(scanf("%lld", &wspolczynniki[j])!=1) return 1;
            wspolczynniki[j] = wspolczynniki[j] % 100000;
        }
        printf("%05lld\n", (long long) horner(wspolczynniki,x,d));
        free(wspolczynniki);
    }
    return 0;
}

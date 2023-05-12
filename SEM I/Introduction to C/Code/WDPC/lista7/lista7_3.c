#include <stdio.h>
#define N 1001
#define K 1001
int main(void){
    int n, k, max = 0, max_id = 0;;
    char identyfikatory[N][K];
    int uniquec[N];
    if(scanf("%d %d", &n, &k)!=2) return 0;
    for (int i = 0; i < n; i++){
        if(scanf("%s", identyfikatory[i])!=1) return 0;
    }
    for(int i = 0;i<n;i++){//identyfikator
        int unique = 0;
        for(int j = 0;j<k;j++){//j-te literki identyfikatora
            for(int l = 0;l<n;l++){//przejście przez j-te literki wszystkich identyfikatorów
                if(identyfikatory[i][j]==identyfikatory[l][j] && i!=l){
                    unique--;
                    break;
                }
            }
            unique++;
        }
        uniquec[i] = unique;
    }
    for(int i = 0;i<n;i++){
        if(uniquec[i]>max){
            max = uniquec[i];
            max_id = i;
        }
    }
    printf("%s\n%d",identyfikatory[max_id], max);
    return 0;
}
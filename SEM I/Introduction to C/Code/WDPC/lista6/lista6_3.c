#include <stdio.h>
int w[401];
//Functions
int counter (int n, int k, int tab[n][n][k], int d);
void f90 (int n, int k, int tab[n][n][k], int s);
void recursion (int n, int k, int tab[n][n][k], int s, int d);
//Main
int main(void){
    int n,k;
    if (scanf("%d %d", &n, &k)!=2) return 0;
    int tab[n][n][k];
    int d = n*n;
    for (int i=0;i<k;i++){
        for (int j=0; j<n;j++){
            for (int l=0;l<n;l++){
                int c = getchar();
                if (c != ' ' && c != '\n'){
                    if (c == '#'){tab[j][l][i] = 1;}else{tab[j][l][i] = 0;}}else{l--;}
            }
        }
    }//data
    recursion(n, k, tab, 0, d);
    for (int i=0;i<d+1;i++){
        if (w[i]) printf("%d ",i);
    }
    return 0;
}
//Definitions
int counter (int n, int k, int tab[n][n][k],int d){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int l = k-1;l>=0;l--){
                if(tab[i][j][l]) {d--; break;}
            }
        }
    }
    return d;
}
void f90 (int n, int k, int tab[n][n][k], int s){
    int p[n][n];
    for (int i=0;i<n;i++){
        for (int j=0; j<n;j++){
            p[i][j] = tab[n-j-1][i][s];
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            tab[i][j][s] = p[i][j];
        }
}
void recursion (int n, int k, int tab[n][n][k], int s, int d){
    if (s >= k)
        w[counter(n, k,tab, d)] = 1;
    else {
        recursion(n, k, tab, s + 1, d);//0
        f90(n, k, tab, s);
        recursion(n, k, tab, s + 1, d);//90
    }
}
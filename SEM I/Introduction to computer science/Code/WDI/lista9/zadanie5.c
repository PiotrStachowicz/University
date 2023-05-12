#include <stdio.h>
#include <stdbool.h>
#define MAX_N 100
int n;
int tab[MAX_N][MAX_N];
int poprzedni = 0;
int suma = 0;
int uzyte[MAX_N*MAX_N];
#define N n*n
void show();
bool poprawne();
int backtracking(int i);
int main(void){
    scanf("%d",&n);
    for(int i = 0;i<N;i++){
        if(backtracking(i) == 1){
            show();
            break;
        }
    }
    return 0;
}
void show(){
    for(int i = 0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d",tab[i][j]);
        }
        putchar('\n');
    }
}
bool poprawne(){
    for(int x = 0;x<n;x++){
        if(poprzedni!=suma) return false;
        if(suma>N) return false;
        suma = 0;
        for(int y = 0;y<n;y++){
            suma += tab[x][y];
        }
        poprzedni = suma;
    }//kolumny
    poprzedni = 0;
    suma = 0;
    for(int y = 0;y<n;y++){
        if(poprzedni!=suma) return false;
        if(suma>N) return false;
        suma = 0;
        for(int x = 0;x<n;x++){
            suma += tab[x][y];
        }
        poprzedni = suma;
    }//wiersze
    poprzedni = 0;
    suma = 0;
    for(int y = 0 ;y < n;y++){
        int x = 0;
        int ky = y;
        if(suma!=poprzedni) return false;
        if(suma>N) return false;
        suma = 0;
        while (ky!=0){
            suma += tab[x][ky];
            x++;
            ky--;
        }
        poprzedni = suma;
    }
    poprzedni = 0;
    suma = 0;
    for(int x = 0 ;x < n;x++){
        int y = n-1;
        int kx = x;
        if(suma!=poprzedni) return false;
        if(suma>N) return false;
        suma = 0;
        while (kx!=n-1){
            suma += tab[kx][y];
            kx++;
            y--;
        }
        poprzedni = suma;
    }//lewy dolny do prawy górny
    poprzedni = 0;
    suma = 0;
    for(int x = 0 ;x < n;x++){
        int y = n-1;
        int kx = x;
        if(suma!=poprzedni) return false;
        if(suma>N) return false;
        suma = 0;
        while (kx!=0){
            suma += tab[kx][y];
            kx--;
            y--;
        }
        poprzedni = suma;
    }
    poprzedni = 0;
    suma = 0;
    for(int x = 0 ;x < n;x++){
        int y = 0;
        int kx = x;
        if(suma!=poprzedni) return false;
        if(suma>N) return false;
        suma = 0;
        while (kx!=n-1){
            suma += tab[kx][y];
            kx++;
            y++;
        }
        poprzedni = suma;
    }//prawy dolny do lewy górny
    return true;
}
int backtracking(int i){
    for(int x = 0; x<n;x++){
        for(int y = 0; y<n;y++){
            if(tab[x][y]==0&&i<=N){
                tab[x][y]= i;
                bool result = poprawne();
                tab[x][y] = 0;

            }
        }
    }
}
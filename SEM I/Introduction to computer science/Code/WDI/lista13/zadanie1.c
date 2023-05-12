#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
void to_list(int i, int j, int macierz[j][i]){
    for (int y = 0;y<j;y++){
        for (int x = 0;x<i;x++){
            if(macierz[y][x]==1) printf("(%d, %d)", y, x);
        }
    }
}
void to_macierz(int i, int j, int lista[j][i]){
    int macierz[j][i];
    for (int y = 0;y<j;y++){
        for (int x = 0;x<i;x++){
            int w2 = lista[y][x];
            macierz[j][w2] = 1;
        }
    }
    printf("%d", macierz[0][0]);
}
int main(void){
    int macierz[2][2];
    for(int i = 0;i<2;i++){
        for(int j = 0;j<2;j++){
            macierz[i][j] = 0;
        }
    }
    macierz[0][0] = 2;
    to_macierz(2,2,macierz);
    return 0;
}

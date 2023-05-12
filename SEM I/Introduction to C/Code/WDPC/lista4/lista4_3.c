#include <stdio.h>
int walker(int x, int y, int N, int tab[N][N]);
int main(void) {
    int N, max_row = 0, max_snake = 0, max_diagonal = 0, r = 0, s = 0, d = 0, czy_prawo = 1, a = 0, b = 0, a1, b1, count_p = 0;
    if (scanf("%d", &N) != 1 || N > 1024) {
        return 1;
    }// wczytuje N
    int tab[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf(" %d", &tab[i][j]);
        }
    }// wczytuje tablice
    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < N; j ++) {
            if (tab[i][j] == 1) {
                r ++;
                if (max_row < r) {
                    max_row = r;
                }
            }
            else {
                r = 0;
            }
        }
    }// row
    for (int i = 0; i < N; i ++) {
        if (czy_prawo == 1) {
            for (int j = 0; j < N; j++) {
                if (tab[i][j] == 1) {
                    s++;
                    if (max_snake < s) {
                        max_snake = s;
                    }
                } else {
                    s = 0;
                }
            }
            czy_prawo = 0;
        }
        else {
            for (int j = N - 1; j >= 0; j--) {
                if (tab[i][j] == 1) {
                    s++;
                    if (max_snake < s) {
                        max_snake = s;
                    }
                } else {
                    s = 0;
                }
            }
            czy_prawo = 1;
        }
    }// snake
    for (int i = 1; i < 2 * N; i++) {
        if (i == 1 || i == 2 * N - 1) {
            if (tab[a][b] == 1) {
                d ++;
                if (max_diagonal < d) {
                    max_diagonal = d;
                }
            }
            else {
                d = 0;
            }
        }
        else {
            a1 = a;
            b1 = b;
            if (a > b) {
                while(a1 != b){
                    if (tab[a][b] == 1) {
                        d ++;
                        if (max_diagonal < d) {
                            max_diagonal = d;
                        }
                    }
                    else {
                        d = 0;
                    }
                    a--;
                    b++;
                }
                if (tab[a][b] == 1) {
                    d ++;
                    if (max_diagonal < d) {
                        max_diagonal = d;
                    }
                }
                else {
                    d = 0;
                }
            }
            else {
                while(b1 > a){
                    if (tab[a][b] == 1) {
                        d ++;
                        if (max_diagonal < d) {
                            max_diagonal = d;
                        }
                    }
                    else {
                        d = 0;
                    }
                    a++;
                    b--;
                }
                if (tab[a][b] == 1) {
                    d ++;
                    if (max_diagonal < d) {
                        max_diagonal = d;
                    }
                }
                else {
                    d = 0;
                }
            }
        }
        if ((a == 0 || a == N - 1) && b < N - 1) {
            b ++;
        }
        else if ((b == 0 || b == N - 1) && a < N - 1) {
            a ++;
        }
    }//diagonal
    if(N % 3 == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if(tab[i][j]){
                    walker(i, j, N, tab);
                    count_p++;
                }
            }
        }
    }
    if(N % 3 == 0){
        printf("%d %d %d\n%d", max_row, max_snake, max_diagonal, count_p);
    } else {
        printf("%d %d %d", max_row, max_snake, max_diagonal);
    }
    return 0;
}
int walker(int x, int y, int N, int tab[N][N]){
    if(tab[x][y]==1){
        tab[x][y] = 0;
        if(x-1>=0){
            walker(x-1,y,N,tab);
        }// gora
        if(x+1<N){
            walker(x+1,y,N,tab);
        }// dol
        if(y-1>=0){
            walker(x,y-1,N,tab);
        }// lewo
        if(y+1<N){
            walker(x,y+1,N,tab);
        }// prawo
    }
    return 0;
}

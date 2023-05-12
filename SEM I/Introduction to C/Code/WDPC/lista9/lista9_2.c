#include <stdio.h>
#define MAX_HEIGHT 200
#define MAX_WIDTH 200
#define MAX_N 1000000
char tab[MAX_HEIGHT][MAX_WIDTH];
char wynik[MAX_HEIGHT][MAX_WIDTH];
char queue[MAX_N];
int w,h,n;
void show();
int main(void) {
    if (scanf(" %d %d", &w, &h) != 2 || w > MAX_WIDTH || h > MAX_HEIGHT || n > MAX_N || w<3 || h<3) return 1;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            char c;
            if (scanf(" %c", &c) != 1) return 1;
            switch (c) {
                case '.':
                    tab[x][y] = c;
                    wynik[x][y] = c;
                    break;
                case '#':
                    tab[x][y] = c;
                    wynik[x][y] = c;
                    break;
                case 'T':
                    tab[x][y] = c;
                    wynik[x][y] = c;
                    break;
                case '^':
                    tab[x][y] = c;
                    wynik[x][y] = c;
                    break;
                case '~':
                    tab[x][y] = c;
                    wynik[x][y] = c;
                    break;
            }
        }
    } // wczytanie mapy
    if(scanf(" %d", &n)!=1) return 1;
    for(int i = 0;i<n;i++) {
        int c = getchar();
        if (c == '\n') i--;
        queue[i] = c;
    } // wczytanie kolejki
    for(int y=0;y<h;y++){ //wybieram y
        for(int x=0;x<w;x++){ // wybieram x
            if(tab[x][y]=='.') { // jeżeli wolne
                for (int kierunek = 1; kierunek < 5; kierunek++) { // wybieram kierunek
                    int k = kierunek;
                    int kx = x;
                    int ky = y;
                    for (int q = 0; q < n; q++) { // wybieram wskazówkę
                        char c = queue[q];
                        int cp = 1;
                        if (c == 'L') {
                            k -= 1;
                            if(k<=0) k=4;
                        }
                        if (c == 'R') {
                            k += 1;
                            if(k>4) k = 1;
                        }
                        if (c == 'F') {
                            if (k == 1) {
                                while (tab[kx][ky - 1] == '.' && ky>0) {
                                    ky--;
                                }
                            }
                            if (k == 2) {
                                while (tab[kx + 1][ky] == '.' && kx<w-1) {
                                    kx++;
                                }
                            }
                            if (k == 3) {
                                while (tab[kx][ky + 1] == '.'&& ky<h-1) {
                                    ky++;
                                }
                            }
                            if (k == 4) {
                                while (tab[kx - 1][ky] == '.' && kx>0) {
                                    kx--;
                                }
                            }
                        }
                        if (c == 'S') {
                            if (k == 1) {
                                if (tab[kx][ky - 1] == '.' && ky>0) {
                                    ky--;
                                } else {
                                    cp = 0;
                                }
                            }
                            if (k == 2) {
                                if (tab[kx + 1][ky] == '.' && kx<w-1) {
                                    kx++;
                                } else {
                                    cp = 0;
                                }
                            }
                            if (k == 3) {
                                if (tab[kx][ky + 1] == '.' && ky<h-1) {
                                    ky++;
                                } else {
                                    cp = 0;
                                }
                            }
                            if (k == 4) {
                                if (tab[kx - 1][ky] == '.' && kx>0) {
                                    kx--;
                                } else {
                                    cp = 0;
                                }
                            }
                        }
                        if(cp==0){
                            break;
                        }
                        if(tab[kx][ky] == '.' && q==n-1){
                            wynik[kx][ky] = 'X';
                        }
                    }
                }
            }
        }
    }
    show();
    return 0;
}
void show(){
    for(int y = 0;y<h;y++){
        for(int x = 0;x<w;x++){
            printf("%c",wynik[x][y]);
        }
        putchar('\n');
    }
}

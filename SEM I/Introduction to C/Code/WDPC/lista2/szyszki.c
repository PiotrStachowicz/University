#include <stdio.h>
int main(void){
    int w, h, wzr = 1;
    long long s = 0, szychy;
    long long int d;
    if(scanf("%d %d %lld",&w,&h,&d)!=3 || w < 1 || h > 100 || d < 1 || d > (1e14)){
        return 1;
    } //wczytuje width height days
    char plansza[h][w];
    int nowy_cien = 0;
    for(int i = 0;i < h;i++){
        for(int j = 0;j < w;j++){
            char c;
            if(scanf(" %c", &c) != 1) return 1;
            if(c >= '1' && c <= '9'){
                plansza[i][j] = c;
            } else{
                plansza[i][j] = '.';
            }
        }
    } //wczytuje plansze
    for(long long int dni = 1;dni<=d;dni++){
        if(wzr > 0){
            wzr = 0;
            szychy = 0;
            for(int i = 0;i<h;i++){
                int cien = '0';
                for(int j = w-1;j>=0;j--){
                    char komorka = plansza[i][j];
                    if (komorka >= cien && komorka != '.' && komorka >= '1' && komorka <= '9') {
                        nowy_cien = komorka;
                    } else {
                        nowy_cien = cien - 1;
                    }
                    if(cien<='0'){
                        if(komorka >= '1' && komorka <= '9'){
                            if(komorka == '9'){
                                s++;
                                szychy++;
                            } else{
                                plansza[i][j] += 1;
                                wzr++;
                            }
                        }
                    }
                    cien = nowy_cien;
                }
            } //symulacja od wschodu
            for(int i = 0;i<w;i++){
                int cien = '0';
                for(int j = h-1;j>=0;j--){
                    char komorka = plansza[j][i];
                    if (komorka >= cien && komorka != '.' && komorka >= '1' && komorka <= '9') {
                        nowy_cien = komorka;
                    } else {
                        nowy_cien = cien - 1;
                    }
                    if(cien<='0'){
                        if(komorka >= '1' && komorka <= '9'){
                            if(komorka == '9'){
                                s++;
                                szychy++;
                            } else{
                                plansza[j][i] += 1;
                                wzr++;
                            }
                        }
                    }
                    cien = nowy_cien;
                }
            } //symulacja od poludnia
            for(int i = 0;i<h;i++){
                int cien = '0';

                for(int j = 0;j < w;j++){
                    char komorka = plansza[i][j];
                    if (komorka >= cien && komorka != '.' && komorka >= '1' && komorka <= '9') {
                        nowy_cien = komorka;
                    } else {
                        nowy_cien = cien - 1;
                    }
                    if(cien<='0'){
                        if(komorka >= '1' && komorka <= '9'){
                            if(komorka == '9'){
                                s++;
                                szychy++;
                            } else{
                                plansza[i][j] += 1;
                                wzr++;
                            }
                        }
                    }
                    cien = nowy_cien;
                }
            } //symulacja od zachodu
        } else{
            s = s + (szychy*(d-dni+1));
            break;
        }
    }
    printf("%lld", s);
    return 0;
}
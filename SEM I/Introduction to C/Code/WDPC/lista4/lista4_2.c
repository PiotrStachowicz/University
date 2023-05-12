#include <stdio.h>
int main(void){
    while(1){
        int c, zj, p, bit, bitp, cykl = 0, max = 0, pop = 0;
        while((c=getchar())!='\n'){
            bit = 6;
            bitp = 7;
            while(bit>=0){
                if(pop>0) {
                    p = c >> bitp;
                    if (cykl % 2 == 0) {
                        if (pop % 2 == 1 && p % 2 == 1) {
                            cykl += 1;
                            if (cykl > max) {
                                max = cykl;
                            }
                        } else {
                            cykl = 0;
                        }
                    }else if(cykl%2==1){
                        if(pop%2==0 && p%2==0){
                            cykl += 1;
                            if(cykl > max){
                                max = cykl;
                            }
                        }else{
                            cykl = 0;
                        }
                    }
                    if(cykl>=1){
                        bitp -= 1;
                        bit -=1;
                    }
                    pop = 0;
                }
                p = c >> bitp;
                zj = c >> bit;
                if(cykl%2==0){
                    if(zj%2==1 && p%2==1){
                        cykl += 1;
                        if(cykl > max){
                            max = cykl;
                        }
                    }else{
                        cykl = 0;
                    }
                }else if(cykl%2==1){
                    if(zj%2==0 && p%2==0){
                        cykl += 1;
                        if(cykl > max){
                            max = cykl;
                        }
                    }else{
                        cykl = 0;
                    }
                }
                if(cykl>=1){
                    bitp -= 2;
                    bit -=2;
                }else{
                    bitp -= 1;
                    bit -= 1;
                }
            }
            if(bitp!=bit){
                pop = c >> 0;
            }
        }
        printf("%d\n", 2*max);
    }
}
#include <stdio.h>
#include <math.h>
unsigned long int MIN(unsigned long int a, unsigned long int b, unsigned long int c){
    unsigned long int sm = 100001;
    if(a<sm){
        sm = a;
    }
    if(b<sm){
        sm = b;
    }
    if(c<sm){
        sm = c;
    }
    return sm;
}
int main(void){
    static unsigned long int d, da = 0, db, dc, daa, dab, dac;
    unsigned long int max;
    if(scanf("%ld", &d)!=1) return 0;
    unsigned long int D = d*d;
    unsigned long int minp = 0;
    for(unsigned long int a = 1;a<d;a++){
        unsigned long int A = a*a;
        max = 0;
        for(unsigned long int b = a/2;b<a;b++){
            unsigned long int B = b*b;
            if(A+B>D){
                break;
            }//opt1
            unsigned long int C = D-A-B;
            unsigned long int c = sqrt(C);
            if(c*c==C){
                unsigned long int min = MIN(a,b,c);
                if(max< min){
                    da = a;
                    db = b;
                    dc = c;
                    max = min;
                }else{
                    goto check;
                }
            }
        }
        check:if(max>minp && max>0) {
        minp = max;
        daa = da;
        dab = db;
        dac = dc;
    }
    }
    if(da == 0){
    printf("BRAK");
} else{
        unsigned int POM;
    if(daa>dac){
        POM = daa;
        daa = dac;
        dac = POM;
    }
    if(daa>dab){
        POM = daa;
        daa = dab;
        dab = POM;
    }
    if(dab>dac){
        POM = dab;
        dab = dac;
        dac = POM;
    }
    printf("%lu %lu %lu", dac,dab,daa);
}
    return 0;
}
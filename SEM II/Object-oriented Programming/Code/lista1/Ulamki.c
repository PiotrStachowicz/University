#include "Ulamki_header.h"


int main(void){
    Ulamek* ulamek1 = nowy_ulamek(-1,8);
    Ulamek* ulamek2 = nowy_ulamek(1,4);
    Ulamek* ulamek3 = add_v1(ulamek1,ulamek2);
    show(ulamek3);
    return 0;
}


int NWD(int a, int b){
    if (a == 0)
        return b;
    return NWD(b % a, a);
}
int NWW(int a, int b){
    return ((a*b)/ NWD(a,b));
}
Ulamek* nowy_ulamek(int num, int denom){
    if(denom==0){
        printf("Denom can't be '0'", stderr);
        return NULL;
    }
    Ulamek* ulamek1 = malloc(sizeof(Ulamek));
    if(num<0 && denom<0){num = num*(-1); denom=denom*(-1);}
    int gcd = NWD(num,denom);
    num = num / gcd;
    denom = denom / gcd;
    ulamek1->num = num;
    ulamek1->denom = denom;
    return ulamek1;
}
Ulamek* add_v1(Ulamek* ulamek1, Ulamek* ulamek2){
    if(ulamek1==NULL || ulamek2==NULL){
        return NULL;
    }
    int new_denom = NWW(ulamek1->denom, ulamek2->denom);
    int new_num = (new_denom/ulamek1->denom)*ulamek1->num + (new_denom/ulamek2->denom)*ulamek2->num;
    return nowy_ulamek(new_num, new_denom);
}
Ulamek* sub_v1(Ulamek* ulamek1, Ulamek* ulamek2){
    if(ulamek1==NULL || ulamek2==NULL){
        return NULL;
    }
    int new_denom = NWW(ulamek1->denom, ulamek2->denom);
    int new_num = (new_denom/ulamek1->denom)*ulamek1->num - (new_denom/ulamek2->denom)*ulamek2->num;
    return nowy_ulamek(new_num, new_denom);
}
Ulamek* mul_v1(Ulamek* ulamek1, Ulamek* ulamek2){
    int new_num = ulamek1->num*ulamek2->num;
    int new_denom = ulamek1->denom*ulamek2->denom;
    return nowy_ulamek(new_num,new_denom);
}
Ulamek* div_v1(Ulamek* ulamek1, Ulamek* ulamek2){
    int new_num = ulamek1->num*ulamek2->denom;
    int new_denom = ulamek1->denom*ulamek2->num;
    return nowy_ulamek(new_num,new_denom);
}
void add_v2(Ulamek* ulamek1, Ulamek* ulamek2){
    if(ulamek2==NULL || ulamek1==NULL) return;
    int new_denom = NWW(ulamek1->denom, ulamek2->denom);
    int new_num = (new_denom/ulamek1->denom)*ulamek1->num + (new_denom/ulamek2->denom)*ulamek2->num;
    ulamek2->num = new_num;
    ulamek2->denom = new_denom;
}
void sub_v2(Ulamek* ulamek1, Ulamek* ulamek2){
    if(ulamek2==NULL || ulamek1==NULL) return;
    int new_denom = NWW(ulamek1->denom, ulamek2->denom);
    int new_num = (new_denom/ulamek1->denom)*ulamek1->num - (new_denom/ulamek2->denom)*ulamek2->num;
    ulamek2->num = new_num;
    ulamek2->denom = new_denom;
}
void mul_v2(Ulamek* ulamek1, Ulamek* ulamek2){
    int new_num = ulamek1->num*ulamek2->num;
    int new_denom = ulamek1->denom*ulamek2->denom;
    ulamek2->num = new_num;
    ulamek2->denom = new_denom;
}
void div_v2(Ulamek* ulamek1, Ulamek* ulamek2){
    int new_num = ulamek1->num*ulamek2->denom;
    int new_denom = ulamek1->denom*ulamek2->num;
    ulamek2->num = new_num;
    ulamek2->denom = new_denom;
}
void show(Ulamek *u){
    if(u==NULL) return;
    printf("%d/%d = %f", u->num, u->denom, (float)u->num/u->denom);
}
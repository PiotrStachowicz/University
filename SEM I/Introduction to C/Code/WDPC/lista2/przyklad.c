#include <stdio.h>
int main(void){
    int a;
    int b;
    printf("Podaj a:");
    if(scanf("%d", &a) != 1){
        printf("bledne dane!");
        return 1;
    }
    printf("Podaj b:");
    if(scanf("%d", &b) != 1){
        printf("bledne dane!");
        return 1;
    }
    int x;
    int y;
    double rx = a;
    double ry = b;
    for(y=b;y>=-b;y--){
        double Py = y;
        for(x=-a;x<=a;x++){
            double Px = x;
            double cz1 = (Px/rx)*(Px/rx);
            double cz2 = (Py/ry)*(Py/ry);
            if((cz1 + cz2) <=1){
                printf("#");
            } else{
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
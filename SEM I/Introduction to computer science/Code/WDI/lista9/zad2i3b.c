#include <stdbool.h>
#include <stdio.h>
#define MAX_N 27
int n;
int w = 0;
int b[MAX_N];
void queens();
bool isfree(int k, int be);
int main(void){
    scanf("%d", &n);
    queens();
    printf("%d", w);
    return 0;
}
void queens(){
    int k;
    b[0]=0;
    k=1;
    while (k<n && k>=0){
        do{
            b[k]++;
        }while (b[k]<n && !isfree(k,b[k]));
        if (b[k]<n){
            k++;
            if(k==n){
                w++;
                b[k]=-1;
                k--;
            }
        }else {
            b[k]=-1;
            k--;
        }
    }
}
bool isfree(int x, int y){
    int i;
    for (i=0; i<x; i++){
        if (b[i]-i==y-x || b[i]+i==y+x || b[i]==y) return false;
    }
    return true;
}
int poprawne(int a[], int en, int k){
    for(int i = 0;i<k-2;i++){
        int j = i+1;
        int x1 = i;
        int y1 = a[i];
        while(j<k-1){
            int x2 = j;
            int y2 = a[j];
            if(x2==x1 || y1==y2 || x1+y1==x2+y2 || x1-y1+en==x2-y2+en){
                return 0;
            }
            j++;
        }
    }
    return 1;
}


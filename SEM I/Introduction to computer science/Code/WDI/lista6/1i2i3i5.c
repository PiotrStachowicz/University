#include <stdio.h>
#include <math.h>
int pierwsze(int i, int a[i]){
    int x=a[i];
    int lewy=0;
    int prawy=i-1;
    while (lewy<prawy-1) {
        int k=(lewy+prawy)/2;
        if (a[k]<x) lewy=k;
        else prawy=k;
    }
    a[lewy+1] = x;
}
int select_sort(int n,int tab[n]){
    int l = 0;
    for(int i = 0;i<n;i++){
        int min = tab[i];
        int minidx = i;
        int cp = 0;
        for(int j = i;j<n;j++){
            if(tab[j]<min){
                minidx = j;
                min = tab[j];
                cp = 1;
            }
        }
        if(cp){
            tab[minidx] = tab[i];
            tab[i] = min;
            l++;
        }
    }
    return l;
    //O(n^2), bo ma dwie pętle które w każdym możliwym przypadku wykonują się n*n razy!
    //instrukcja dominująca forfor
    //dla tablicy n elementowej uporządkowanej rosnąco:0*n ???
    //dla tablicy n elementowej uporządkowanej malejąco:1*n ???
}//💀
int bumbel_sort(int n, int tab[n]){
    while(n>0){
        for(int j = 1;j<n;j++){
            int l = tab[j-1];
            int p = tab[j];
            if(l>p){
                tab[j-1] = p;
                tab[j] = l;
            }
        }
        n--;
    }
}//😎
int sito(int n, int tab[n]){
    for(int k = 2;k<n;k = k+2){
        tab[k] = 0;
    }
    for(int i = 3;i<n;i = i + 2){
        if(tab[i]){
            for(int j = i*i;j<n;j = j+i){
                tab[j] = 0;
            }
        }
    }
}
int sito_zad6(int n, int m, int tab[n-m]){
    int k = sqrt(n);
    if(m==0){
        tab[0] = 0;
        tab[1] = 0;
    }
    for(int i = 2;i<=k;i++){// sqrt(n)
        for(int j = 0;j<n-m;j++){
            if((m+j)%i==0 && (m+j)!=i){//max 10000
                tab[j]=0;
            }
        }
    }
}
int main(void){
    int n, m;
    scanf("%d %d", &n, &m);
    int tab[n-m];
    for(int j = 0;j<n-m;j++){
        tab[j] = 1;
    }
    sito_zad6(n,m,tab);
    for(int i =0;i<n-m;i++){
        if(tab[i]) printf("%d\n", m + i);
    }
    return 0;
}

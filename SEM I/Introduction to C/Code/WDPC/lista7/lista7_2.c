#include <stdio.h>
int main(void){
    long int n;
    scanf("%ld", &n);
    long int tab[n];
    for (int i=n-1;i>=0;i--){
        scanf(" %ld", &tab[i]);
    }
    printf("#include <stdio.h>\n");
    printf("#define C(idx,s,M) C##idx(s,M)\n");
    printf("unsigned long c;\n");
    for(int i = 0;i<=n;i++){
        if(i==0){
            printf("void C0(long s,long M){c+=!s&&M<=10;}\n");
        } else{
            printf("void C%d(long s,long M){C%d(s,M);C%d(s+%ld,M+1);}\n",i,i-1,i-1,tab[i-1]);
        }
    }
    printf("int main(void){\n");
    printf("    C(3,0,0);\n", n);
    printf("    printf(\"%%lu\\n\",c);\n");
    printf("    return 0;\n");
    printf("}");
    return 0;
}
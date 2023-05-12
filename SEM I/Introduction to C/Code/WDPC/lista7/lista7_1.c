#include <stdio.h>
int main(void){
    long int n;
    scanf("%ld", &n);
    long int tab[n];
    for (int i=0;i<n;i++){
        scanf(" %ld", &tab[i]);
    }
    printf("#include <stdio.h>\n");
    printf("unsigned long counter;\n");
    for(int i = 0;i<=n;i++){
        if(i==0){
            printf("void countSumZero0(long sum) { if (sum == 0) counter++; }\n");
        } else{
            printf("void countSumZero%d(long sum) { countSumZero%d(sum); countSumZero%d(sum + %ld); }\n",i,i-1,i-1,tab[i-1]);
        }
    }
    printf("int main(void){\n");
    printf("    countSumZero%ld(0);\n", n);
    printf("    printf(\"%%lu\\n\",counter);\n");
    printf("    return 0;\n");
    printf("}");
    return 0;
}

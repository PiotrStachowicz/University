#include <stdio.h>
#define min(a, b) ((a) < (b) ? (a) : (b))
int main(){
    int n;
    scanf("%d", &n);
    int a[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &a[i][j]);
    int dp[n][n];
    dp[0][0] = a[0][0];
    for (int i = 1; i < n; i++)
        dp[i][0] = dp[i-1][0] + a[i][0];
    for (int j = 1; j < n; j++)
        dp[0][j] = dp[0][j-1] + a[0][j];
    for (int i = 1; i < n; i++)
        for (int j = 1; j < n; j++)
            dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + a[i][j];
    printf("%d\n", dp[n-1][n-1]);
    return 0;
}
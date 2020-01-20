#include <bits/stdc++.h>
int  main() {
    int N, n;   //总个数， 倒三角层数
    char ch;
    scanf("%d %c", &N, &ch);
    for(int i = 1; i <= 1001; i++) {    //计算层数
        n = i - 1;
        if(2 * i * i - 1 > N) break;    //总个数：2*n*n - 1,(n为倒三角的层数)
    }
    for(int i = n; i >= 1; i--) {   //倒三角：第n -> 1层
        for(int j = 0; j < n + i - 1; j++) {    //右侧多余空格输出会格式错误
            if(j >= n - i && j < n + i - 1) printf("%c", ch);   //中间部分
            else printf(" ");
        }
        printf("\n");
    }
    for(int i = 2; i <= n; i++) {   //正三角: 第2 -> n层
        for(int j = 0; j < n + i - 1; j++) {
            if(j >= n - i && j < n + i - 1) printf("%c", ch);
            else printf(" ");
        }
        printf("\n");
    }
    printf("%d", N - 2 * n * n + 1);    //剩余个数
    return 0;
}
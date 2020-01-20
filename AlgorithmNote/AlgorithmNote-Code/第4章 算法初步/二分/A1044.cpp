/*
 * @Author: wuyangjun
 * @Date: 2019-08-02 22:29:28
 * @LastEditTime: 2019-08-02 23:07:20
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int a[N+1], b[N+1] = {0};
    a[0] = 0;
    // a[i] = a[1]+...+a[i] -> i-j = a[j] - a[i-1]
    for(int i = 1; i <= N; i++) {
        scanf("%d", &a[i]);
        a[i] += a[i-1];
    }
    int minNum = 0x3fffffff; //存放间距超出M的最小值
    bool isPrint = false;   //记录是否间距为M的i-j
    // 枚举N个a[i]，查找第一个大于或等于a[i-1]+M的下标
    for(int i = 1; i <= N; i++) {
        int j = lower_bound(a + i, a + N + 1, a[i-1] + M) - a;
        if(a[i-1] + M == a[j]) {
            printf("%d-%d\n", i, j);
            isPrint = true;
        }
        else if(j != N + 1){ // =N+1表示为找到满足条件的数
            b[i] = j;
            if(minNum > a[j] - a[i-1]) minNum = a[j] - a[i - 1];
        }
    }
    if(!isPrint) {
        for(int i = 1; i <= N; i++) {
            if(b[i] != 0 && a[b[i]] - a[i - 1] == minNum) printf("%d-%d\n", i, b[i]);
        }
    }
    return 0;
}
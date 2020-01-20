/*
 * @Author: wuyangjun
 * @Date: 2019-08-06 15:25:49
 * @LastEditTime: 2019-08-06 15:52:41
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
void solve(LL n) {
    LL sqrn = (LL)sqrt(1.0*n);
    LL ansIdx, ansLen = 0;
    for(LL i = 2; i <= sqrn; i++) {
        LL product = i, j = i;
        // 此处不可限制j <= sqrn，否则6就过不了
        while(n % product == 0) {
            j ++;
            product *= j;
        }
        // 若使用等于，无法从多对中筛选出最小的
        if(j - i > ansLen) {
            ansIdx = i;
            ansLen = j - i;
        }
    }
    if(ansLen == 0) printf("1\n%d\n", n);
    else {
        printf("%d\n", ansLen);
        for(int i = ansIdx; i < ansIdx + ansLen; i++) {
            printf("%d%s", i, i == ansIdx + ansLen - 1? "\n" : "*");
        }
    }
} 
int main() {
    LL n;
    scanf("%lld", &n);
    solve(n);
    return 0;
}
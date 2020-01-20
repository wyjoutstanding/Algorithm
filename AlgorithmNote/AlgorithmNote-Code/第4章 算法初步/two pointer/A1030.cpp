/*
 * @Author: wuyangjun
 * @Date: 2019-08-03 11:20:30
 * @LastEditTime: 2019-08-03 11:26:33
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int main() {
    LL N, p;
    scanf("%lld %lld", &N, &p);
    vector<LL> a(N);
    for(int i = 0; i < N; i++) scanf("%lld", &a[i]);
    sort(a.begin(), a.end()); // 从小到大排序
    // two pointer
    int cnt = 1, i = 0, j = 0;
    while(i < N && j < N) {
        while(j < N && a[j] <= p * a[i]) {
            cnt = max(cnt, j - i + 1); //最大间距
            j ++;
        }
        i ++;
    }
    printf("%d\n", cnt);
    return 0;
}
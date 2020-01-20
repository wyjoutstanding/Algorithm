/*
 * @Author: wuyangjun
 * @Date: 2019-07-31 15:19:25
 * @LastEditTime: 2019-07-31 16:06:01
 * @Github: https://github.com/wyjoutstanding
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
// [left, right]第一个大于val的下标
// vector不使用&会超时
int binarySearch(vector<LL> &a, int left, int right, LL val) {
    int mid;
    while(left < right) {
        mid = left + (right - left) / 2;
        if(a[mid] > val) right = mid;
        else left = mid + 1;
    }
    return left;
}
int main() {
    LL N, p;
    scanf("%lld %lld", &N, &p);
    vector<LL> res(N);
    for(int i = 0; i < N; i++) {
        scanf("%lld", &res[i]);
    }
    sort(res.begin(), res.end());
    int ans = 0, last;
    for(int i = 0; i < N; i++) {
        last = binarySearch(res, i + 1, N, res[i] * p) - i;
        //  last = upper_bound(res.begin() + i, res.end(), res[i] * p) - res.begin() - i;
        ans = max(ans, last);
    }
    printf("%d\n", ans);
    return 0;
}
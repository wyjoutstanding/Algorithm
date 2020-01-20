/*
 * @Author: wuyangjun
 * @Date: 2019-07-30 19:54:07
 * @LastEditTime: 2019-07-31 09:45:59
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 10001;
string res[maxn];
// 结合时小的放在前
bool cmp(string a, string b) {
    return a + b < b + a;
}
int main() {
    int N;
    scanf("%d", &N);
    for(int i = 0; i < N; i++) cin >>res[i];
    sort(res, res + N, cmp);
    string ans;
    // 拼接
    for(int i = 0; i < N; i ++) {
        ans += res[i];
    }
    // 去除前导0
    while(ans.size() != 0 && *ans.begin() == '0') {
        ans.erase(ans.begin());
    }
    // 考虑0的情况
    if(ans.size() == 0) printf("0\n");
    else cout <<ans <<endl;
    return 0;
}
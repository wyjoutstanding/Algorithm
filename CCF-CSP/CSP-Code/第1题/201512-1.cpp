/*
 * @Author: wuyangjun
 * @Date: 2019-09-13 15:14:04
 * @LastEditTime: 2019-09-13 15:15:03
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    int ans = 0;
    cin >>s;
    for(auto& p : s) ans += (p - '0');
    printf("%d\n", ans);
    return 0;
}
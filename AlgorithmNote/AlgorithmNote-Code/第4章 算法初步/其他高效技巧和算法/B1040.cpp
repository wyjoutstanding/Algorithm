/*
 * @Author: wuyangjun
 * @Date: 2019-08-03 23:33:05
 * @LastEditTime: 2019-08-03 23:52:25
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100005;
const int mod = 1000000007;
int P[maxn] = {0}, T[maxn] = {0};
int main() {
    string s;
    cin >>s;
    int sum = 0;
    // 统计每个数左侧P个数
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == 'P') P[i] ++;
        if(i != 0) P[i] += P[i-1];
    }
    // 统计每个数右侧T个数
    for(int i = s.size() - 1; i >= 0; i--) {
        if(s[i] == 'T') T[i] ++;
        if(i != s.size() - 1) T[i] += T[i+1];
    }
    // 累加每个A左右P*T的和值
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == 'A') {
            sum += T[i] * P[i];
            sum %= mod; //取模
        }
    }
    printf("%d\n", sum);
    return 0;
}
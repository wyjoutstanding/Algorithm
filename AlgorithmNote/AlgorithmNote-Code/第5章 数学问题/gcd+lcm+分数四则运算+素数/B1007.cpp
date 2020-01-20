/*
 * @Author: wuyangjun
 * @Date: 2019-08-05 16:34:16
 * @LastEditTime: 2019-08-05 17:05:54
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
int prime[maxn], pNum = 0; //素数表和素数个数
bool p[maxn] = {0};
// Eratosthenes筛法：O(nloglogn)，找出[2,n]的素数
void findPrime(int n) {
    for(int i = 2; i <= n; i++) {
        if(!p[i]) {
            prime[pNum++] = i;
            for(int j = i + i; j <= n; j += i) p[j] = true;
        }
    }
}
// 统计间距为2且不大于n的素数对数
int solve(int n) {
    int cnt = 0;
    for(int i = 0; i < pNum - 1; i++) {
        if(prime[i+1] - prime[i] == 2) cnt ++;
    }
    return cnt;
}
int main() {
    int n;
    scanf("%d", &n);
    findPrime(n);
    printf("%d\n", solve(n));
    return 0;
}
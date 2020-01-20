/*
 * @Author: wuyangjun
 * @Date: 2019-08-06 12:54:42
 * @LastEditTime: 2019-08-06 13:32:21
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
int prime[maxn], pNum = 0;
bool p[maxn] = {0};
// 筛法查找[2,n]的素数表
void findPrime(int n) {
    for(int i = 2; i <= n; i++) {
        if(!p[i]) {
            prime[pNum++] = i;
            for(int j = i + i; j <= n; j += i) {
                p[j] = true;
            }
        }
    }
}
struct Factor {
    int x, cnt; //因子，次数
}fac[10]; //int足够
int fNum = 0; //不同因子个数
void primeFactor(int n) {
    int sqrn = (int)sqrt(1.0 * n);
    findPrime(sqrn);
    // 先在[2,sqrt(n)]找
    for(int i = 0; i < pNum; i++) {
        if(n % prime[i] == 0) {
            // 初始化
            fac[fNum].x = prime[i];
            fac[fNum].cnt = 0;
            // 计数
            while(n % prime[i] == 0) {
                fac[fNum].cnt ++;
                n /= prime[i];
            }
            fNum ++;
        }
        if(n == 1) break;
    }
    // 若不为1，必定存在一个因子位于(sqrt(n), n]
    if(n != 1) {
        fac[fNum].x = n;
        fac[fNum].cnt = 1;
        fNum ++;
    }
}
void print(int n) {
    printf("%d=", n);
    for(int i = 0; i < fNum; i++) {
        if(i != 0) printf("*");
        printf("%d", fac[i].x);
        if(fac[i].cnt != 1) printf("^%d", fac[i].cnt);
    }
    printf("\n");
}
int main() {
    int n;
    scanf("%d", &n);
    if(n == 1) printf("1=1\n"); //注意特判
    else {
        primeFactor(n);
        print(n);
    }
    return 0;
}
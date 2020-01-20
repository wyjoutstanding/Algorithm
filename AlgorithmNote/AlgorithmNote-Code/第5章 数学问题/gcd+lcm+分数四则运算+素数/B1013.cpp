/*
 * @Author: wuyangjun
 * @Date: 2019-08-05 17:13:53
 * @LastEditTime: 2019-08-05 17:52:39
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int prime[maxn], num = 0; //第m~n个素数
// 判断是否为素数，是->true；否->false
bool isPrime(int n) {
    if(n < 2) return false; //小于2不可能是素数
    int sqr = (int)sqrt(1.0 * n); //要乘1.0变成浮点数
    for(int i = 2; i <= sqr; i++) {
        if(n % i == 0) return false;
    }
    return true;
}
// 寻找第[m,n]个素数
void findPrime(int m, int n) {
    int pNum = 0, i = 2;
    do {
        if(isPrime(i)) {
            pNum ++;
            if(pNum >= m && pNum <= n) prime[num++] = i;
        }
        i ++;
    }while(pNum != n);
}
void print() {
    for(int i = 0; i < num; i++) {
        printf("%d%s", prime[i], (i % 10 == 9 || i == num - 1) ? "\n" : " ");
    }
}
int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    findPrime(m, n);
    print();
    return 0;
}
/*
 * @Author: wuyangjun
 * @Date: 2019-08-05 19:22:24
 * @LastEditTime: 2019-08-05 19:42:14
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
bool isPrime(int n) {
    if(n < 2) return false;
    for(int i = 2; i <= (int)sqrt(1.0 * n); i++) { //等于号别漏，否则4,10就过不了
        if(n % i == 0) return false;
    }
    return true;
}
bool solve(int n, int d) {
    if(!isPrime(n)) return false; //n不是素数直接返回false
    // 将10进制的n转为d进制再转为10进制，这里利用其倒序性质同步进行
    int sum = 0;
    do {
        sum = sum * d + n % d;
        n /= d;
    }while(n != 0);
    return isPrime(sum);
}
int main() {
    int n, d;
    while(true) {
        scanf("%d", &n);
        if(n < 0) break;
        scanf("%d", &d);
        printf("%s\n", solve(n, d) ? "Yes" : "No");
    }
    return 0;
}
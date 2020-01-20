/*
 * @Author: wuyangjun
 * @Date: 2019-08-05 20:18:45
 * @LastEditTime: 2019-08-05 20:53:52
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
bool pos[maxn] = {0}; //标记位置是否被使用
bool isPrime(int n) {
    if(n < 2) return false;
    // 等于号别漏！！！！
    for(int i = 2; i <= (int)sqrt(1.0 * n); i++) {
        if(n % i == 0) return false; 
    }
    return true;
}
//找到第一个大于等于m的素数
int initMSize(int m) {
    while(true) {
        if(isPrime(m)) return m;
        else m ++;
    }
}
// 正向平方探查
int quadraticProbing(int n, int MSize) {
    int idx;
    for(int i = 1; i < MSize; i++) {
        idx = ((n % MSize) + i * i) % MSize;
        if(!pos[idx]) {
            pos[idx] = true;
            return idx;
        }
    }
    return -1; //未找到位置
}
// 哈希映射
int hashing(int n, int MSize) {
    int idx = n % MSize;
    if(!pos[idx]) {
        pos[idx] = true;
        return idx;
    }
    return quadraticProbing(n, MSize); //冲突
}
int main() {
    int MSize, N;
    scanf("%d %d", &MSize, &N);
    MSize = initMSize(MSize);
    int t;
    for(int i = 0; i < N; i ++) {
        scanf("%d", &t);
        int ret = hashing(t, MSize);
        if(ret == -1) printf("-%s", i + 1 == N ? "\n" : " ");
        else printf("%d%s", ret, i + 1 == N ? "\n" : " ");
    }
    return 0;
}
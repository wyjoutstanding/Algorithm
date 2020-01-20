/*
 * @Author: wuyangjun
 * @Date: 2019-07-28 09:15:59
 * @LastEditTime: 2019-07-28 09:21:03
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int N;
    scanf("%d", &N);
    int hashTable[101] = {0}; //哈希映射
    for(int i = 0; i < N; i++) {
        int t;
        scanf("%d", &t);
        hashTable[t] ++;//统计该分数的人数
    }
    // K次查询
    int K;
    scanf("%d", &K);
    for(int i = 0; i < K; i++) {
        int t;
        scanf("%d", &t);
        if(i == 0) printf("%d", hashTable[t]);
        else printf(" %d", hashTable[t]);
    }
    return 0;
}
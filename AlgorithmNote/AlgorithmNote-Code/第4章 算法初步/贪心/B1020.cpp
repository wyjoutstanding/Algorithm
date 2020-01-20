/*
 * @Author: wuyangjun
 * @Date: 2019-07-29 17:27:16
 * @LastEditTime: 2019-07-29 18:49:57
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
// 题目说是正数，并非正整数
struct Moon {
    double store; //库存
    double price; //价格
    double rate;  //单价
};
bool cmp(Moon a, Moon b) {
    return a.rate > b.rate;
}
int main() {
    int N;
    double D;
    scanf("%d %lf", &N, &D);
    Moon moon[N];
    for(int i = 0; i < N; i++) {
        scanf("%lf", &moon[i].store);
    }
    for(int i = 0; i < N; i++) {
        scanf("%lf", &moon[i].price);
        moon[i].rate = moon[i].price / moon[i].store; //性价比
    }
    // 按性价比从高到低排序
    sort(moon, moon + N, cmp);
    // 尽可能用性价比高的库存
    double sum = 0;
    for(int i = 0; i < N; i++) {
        if(D > moon[i].store) { //库存不足
            sum += moon[i].store * moon[i].rate;
            D -= moon[i].store;
        }
        else {
            sum += D * moon[i].rate;
            break;
        }
    }
    printf("%.2lf", sum);
    return 0;
}
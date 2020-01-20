/*
 * @Author: wuyangjun
 * @Date: 2019-08-03 19:58:27
 * @LastEditTime: 2019-08-03 21:51:28
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n1, n2;
    scanf("%d", &n1);
    vector<int> a(n1);
    for(int i = 0; i < n1; i++) scanf("%d", &a[i]);
    scanf("%d", &n2);
    // 避免内存超限，第二个数组边读边计数
    int idx; //第idx个输出
    if((n1 + n2) % 2 == 0) idx = (n1 + n2 - 1) / 2; //偶数
    else idx = (n1 + n2) / 2;   //奇数
    int t, j = 0, cnt = 0;
    for(int i = 0; i < n2; i++) {
        scanf("%d", &t);
        // a数组找到比t大的数
        while(j < n1 && a[j] < t) {
            // 满足条件立刻输出
            if(idx == cnt) {
                printf("%d", a[j]);
                return 0;
            }
            j ++;
            cnt ++;
        }
        // a遍历完或找到比t 大的数
        if(idx == cnt) {
            printf("%d", t);
            return 0;
        }
        cnt ++;
    }
    // 第二个数组遍历完依旧不到中位数
    while(j < n1) {
        if(idx == cnt) {
            printf("%d", a[j]);
            return 0;
        }
        cnt ++;
        j ++;
    }
    return 0;
}
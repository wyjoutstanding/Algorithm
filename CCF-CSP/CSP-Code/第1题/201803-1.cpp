/*
 * @Author: wuyangjun
 * @Date: 2019-09-13 12:58:30
 * @LastEditTime: 2019-09-13 13:03:25
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int t, pre = 1, sum = 0;
    while(scanf("%d", &t)) {
        if(t == 0) break;
        if(t == 1) {
            pre = 1;
            sum += 1;
        }
        else if(t == 2) {
            if(pre == 1) pre = 2;
            else pre += 2;
            sum += pre;
        }
    }
    printf("%d\n", sum);
    return 0;
}
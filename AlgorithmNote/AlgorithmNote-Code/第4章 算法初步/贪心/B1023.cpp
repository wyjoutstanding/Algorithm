/*
 * @Author: wuyangjun
 * @Date: 2019-07-29 14:08:23
 * @LastEditTime: 2019-07-29 14:12:48
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int a[10];
    for(int i = 0; i < 10; i++) scanf("%d", &a[i]);
    // 找到最小正数作为最高位
    for(int i = 1; i < 10; i++) {
        if(a[i] != 0) {
            printf("%d", i);
            a[i] --;
            break;
        }
    }
    // 从小依次输出
    for(int i = 0; i < 10; i++) {
        if(a[i] != 0) {
            for(int j = 0; j < a[i]; j++) printf("%d", i);
        }
    }
    return 0;
}
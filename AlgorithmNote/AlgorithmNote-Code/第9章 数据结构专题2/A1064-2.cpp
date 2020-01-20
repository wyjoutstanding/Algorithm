/*
 * @Author: wuyangjun
 * @Date: 2019-08-13 00:21:19
 * @LastEditTime: 2019-08-13 01:02:55
 * @Github: https://github.com/wyjoutstanding
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
int CBST[maxn], number[maxn]; //完全二叉排序树、中序遍历序列
int N, idx = 0; //结点数
void adjust() {
    for(int i = 1; i <= N; i ++) {
        int x = i, n = i;
        printf("==x=%d n=%d==\n", x, n);
        while(x / 2 != 0) {
            printf("1_x:%d\n", x);
            if(x % 2 == 1 && (number[x] < number[x / 2] || number[x] > number[1])) {
                swap(number[x], number[x / 2]);
                x = x / 2;
            }
            else if(x % 2 == 0 && (number[x] >= number[x / 2] || number[x] > number[1]) ) {
                swap(number[x], number[x / 2]);
                x = x / 2;
            }
            else break;
        }
        while(x * 2 <= n) {
            printf("2_x:%d\n", x);
            if(number[2 * x] >= number[x]) {
                swap(number[x], number[2 * x]);
                x = 2 * x;
            }
            else if(2 * x + 1 <= n && number[2 * x + 1] < number[x]) {
                swap(number[x], number[2 * x + 1]);
                x = 2 * x + 1;
            }
            else break;
        }
    }
}
int main() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i ++) {
        scanf("%d", &number[i]);
    }
    adjust();
    // 数组存放顺序即为层序遍历，从1开始存
    for(int i = 1; i <= N; i ++) {
        printf("%d%s", number[i], i == N ? "\n" : " ");
    }
    return 0;
}
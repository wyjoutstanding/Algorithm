/*
 * @Author: wuyangjun
 * @Date: 2019-08-06 20:26:20
 * @LastEditTime: 2019-08-06 21:01:25
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct bign {
    int d[1000]; //低到高位依次存放
    int len; //位数
    // 无参构造函数
    bign() {
        memset(d, 0, sizeof(d)); //按位赋值
        len = 0;
    }
};
// 将读入的字符串反转，小端存储
bign change(char *str) {
   bign res;
   res.len = strlen(str);
   for(int i = 0; i < res.len; i ++) {
       res.d[i] = str[res.len - 1 - i] - '0'; //转换为整数
   }
   return res;
}
// 高精度和低精度除法，r为余数，初值必须为0
bign div(bign a, int b, int &r) {
    bign res;
    res.len = a.len; //商与被除数位数相同
    // 从高位开始枚举
    for(int i = a.len - 1; i >= 0; i --) {
        r = r * 10 + a.d[i];
        if(r < b) res.d[i] = 0;
        else {
            res.d[i] = r / b;
            r = r % b;
        }
    }
    // 去除高位多余0，为0时需保留一位
    while(res.len > 1 && res.d[res.len - 1] == 0) res.len --;
    return res;
}
void printBign(bign a) {
    for(int i = a.len - 1; i >= 0; i --) printf("%d", a.d[i]);
    // printf("\n");
}
int main() {
    char str[1000];
    int b;
    scanf("%s %d", str, &b);
    bign a = change(str);
    int r = 0; // 余数初始值必须为0
    bign res = div(a, b, r);
    printBign(res);
    printf(" %d\n", r);
    return 0;
}
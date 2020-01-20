/*
 * @Author: wuyangjun
 * @Date: 2019-08-06 23:45:58
 * @LastEditTime: 2019-08-07 00:16:44
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct bign {
    int d[1000];
    int len;
    bign() {
        memset(d, 0, sizeof(d));
        len = 0;
    }
};
bign change(char *str) {
    bign res;
    res.len = strlen(str);
    for(int i = 0; i < res.len; i ++) {
        res.d[i] = str[res.len - 1 - i] - '0'; //记得减0
    }
    return res;
}
bign add(bign a, bign b) {
    bign res;
    int carry = 0;
    for(int i = 0; i < a.len || i < b.len; i ++) {
        int tmp = a.d[i] + b.d[i] + carry;
        res.d[res.len++] = tmp % 10;
        carry = tmp / 10;
    }
    if(carry != 0) res.d[res.len++] = carry;
    return res;
}
// a反转
bign reverse(bign a) {
    bign b;
    b.len = a.len;
    for(int i = 0; i < a.len; i ++) {
        b.d[i] = a.d[a.len - 1 - i];
    }
    return b;
}
// 判断大整数a是否为回文数
bool isPalindromicNum(bign a) {
    for(int i = 0; i < a.len / 2; i ++) {
        if(a.d[i] != a.d[a.len - 1 - i]) return false;
    }
    return true;
}
void print(bign a) {
    for(int i = a.len - 1; i >= 0; i --) printf("%d", a.d[i]);
    printf("\n");
}
void solve(bign a, int k) {
    bign res = a;
    int cnt = 0;
    while(cnt < k && !isPalindromicNum(res)) {
        res = add(res, reverse(res));
        cnt ++;
    }
    print(res);
    printf("%d\n", cnt);
}
int main() {
    char str[100];
    int k;
    scanf("%s %d", str, &k);
    bign a = change(str);
    solve(a, k);
    return 0;
}
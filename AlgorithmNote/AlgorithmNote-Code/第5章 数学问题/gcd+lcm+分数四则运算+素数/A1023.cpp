/*
 * @Author: wuyangjun
 * @Date: 2019-08-06 21:32:32
 * @LastEditTime: 2019-08-06 21:50:22
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct bign {
    int d[100];
    int len;
    bign() {
        memset(d, 0, sizeof(d));
        len = 0;
    }
};
bign change(char *str) {
    bign res;
    res.len = strlen(str);
    for(int i = res.len - 1; i >= 0; i --) {
        res.d[i] = str[res.len - 1 - i] - '0';
    }
    return res;
}
bign add(bign a, bign b) {
    bign res;
    int carry = 0; //进位
    // 低位到高位，取较长者，较短者高位已经初始化为0
    for(int i = 0; i < a.len || i < b.len; i ++) {
        int tmp = a.d[i] + b.d[i] + carry;
        res.d[res.len++] = tmp % 10;
        carry = tmp / 10;
    }
    // 最高位的进位
    if(carry != 0) res.d[res.len++] = carry;
    return res;
}
// 哈希表判断两个序列是互为否为排列
bool isFind(bign a, bign b) {
    if(a.len != b.len) return false;
    int hashTable[10] = {0};
    for(int i = 0; i < a.len; i ++) {
        hashTable[a.d[i]] ++;
    }
    for(int i = 0; i < b.len; i ++) {
        hashTable[b.d[i]] --;
    }
    for(int i = 0; i < 10; i ++) {
        if(hashTable[i] != 0) return false;
    }
    return true;
}
void print(bign a) {
    for(int i = a.len - 1; i >= 0; i --) printf("%d", a.d[i]);
    printf("\n");
}
int main() {
    char str[21];
    scanf("%s", str);
    bign a = change(str);
    bign res = add(a, a);
    printf("%s\n", isFind(a, res) ? "Yes" : "No");
    print(res);
    return 0;
}
/*
 * @Author: wuyangjun
 * @Date: 2019-09-14 20:37:46
 * @LastEditTime: 2019-09-15 00:09:20
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct Action {
    int keyId, type, time; // 钥匙编号，动作类型（0：借，1：还），动作发生时间
}a[2010]; // 借还动作 
int N, K, key[1010]; // 钥匙盒1~N
bool cmp(Action& a, Action& b) {
    if(a.time != b.time) return a.time < b.time; // 动作时间小者优先
    else if(a.type != b.type) return a.type > b.type; // 动作还优先，字母打错了！！！！
    else return a.keyId < b.keyId; // 多个还id小者优先
}
int main() {
    scanf("%d %d", &N, &K);
    int k, s, c;
    for(int i = 0; i < 2*K; i += 2) { // 拆分借还动作
        scanf("%d %d %d", &k, &s, &c);
        a[i].keyId = a[i+1].keyId = k;
        a[i].type = 0; a[i+1].type = 1;
        a[i].time = s; a[i+1].time = s + c; // 借还时间
    }
    sort(a, a + 2*K, cmp); // 动作排序
    for(int i = 0; i <= N; i ++) key[i] = i; // 初始化钥匙盒
    for(int i = 0; i < 2*K; i ++) { // 2*K个事件模拟
        if(a[i].type == 0) key[find(key+1, key+N+1, a[i].keyId) - key] = -1; // 取钥匙，置为-1
        else key[find(key+1, key+N+1, -1) - key] = a[i].keyId; // 还钥匙，从左开始找到第一个空位
    }
    for(int i = 1; i <= N; i ++) printf("%d ", key[i]);
    return 0;
}
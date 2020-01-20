/*
 * @Author: wuyangjun
 * @Date: 2019-08-09 19:58:11
 * @LastEditTime: 2019-08-09 20:30:49
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
struct LNode {
    int addr, data, next;
    int order;
    LNode() {order = maxn;}
}SLink[maxn], node;
bool cmp(LNode a, LNode b) {
    return a.order < b.order;
}
int main() {
    int n, head;
    scanf("%d %d", &head, &n);
    for(int i = 0; i < n; i ++) {
        scanf("%d %d %d", &node.addr, &node.data, &node.next);
        node.order = n + 1; //表示存在该点
        SLink[node.addr] = node; 
    }
    // 遍历计数，节点编号
    int cnt = 0; // 有效个数
    for(int p = head; p != -1; p = SLink[p].next) {
        if(SLink[p].order == maxn) break; //空链表
        SLink[p].order = cnt ++;
    }
    sort(SLink, SLink + maxn, cmp);
    vector<int> a, b;
    bool keys[maxn] = {0}; //记录data绝对值是否出现
    for(int i = 0; i < cnt; i ++) {
        int idx = abs(SLink[i].data); //数据绝对值
        if(!keys[idx]) { //第一次出现
            keys[idx] = true; 
            a.push_back(i); //保留
        }
        else b.push_back(i); //删除
    }
    // 输出
    for(int i = 0; i < a.size(); i ++) {
        int p = a[i];
        printf("%05d %d ", SLink[p].addr, SLink[p].data);
        if(i == a.size() - 1) printf("-1\n");
        else printf("%05d\n", SLink[a[i+1]].addr);
    }
    for(int i = 0; i < b.size(); i ++) {
        int p = b[i];
        printf("%05d %d ", SLink[p].addr, SLink[p].data);
        if(i == b.size() - 1) printf("-1\n");
        else printf("%05d\n", SLink[b[i+1]].addr);
    }
    return 0;
}
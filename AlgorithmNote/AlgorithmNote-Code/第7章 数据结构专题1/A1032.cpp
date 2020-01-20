/*
 * @Author: wuyangjun
 * @Date: 2019-08-09 16:26:18
 * @LastEditTime: 2019-08-09 16:53:57
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
struct LNode {
    int addr, next;
    char data;
}SLink[maxn], node;
bool hashTable[maxn] = {0};
void traverseSLink(int head) {
    int now = head;
    while(now != -1) {
        hashTable[now] = true;
        now = SLink[now].next;
    }
}
int main() {
    int head1, head2, n;
    scanf("%d %d %d", &head1, &head2, &n);
    for(int i = 0; i < n; i ++) {
        scanf("%d %c %d", &node.addr, &node.data, &node.next);
        SLink[node.addr] = node;
    }
    // 遍历第一个链表，将其有效节点对应的标记置为true
    traverseSLink(head1);
    int ans = -1; //答案
    int cur = head2; 
    // 遍历第二条链表
    while(cur != -1) {
        if(hashTable[cur]) { //找到第一个为true节点，记录答案，立刻退出
            ans = SLink[cur].addr;
            break;
        }
        cur = SLink[cur].next;
    }
    if(ans == -1) printf("-1\n");
    else printf("%05d\n", ans);
    return 0;
}
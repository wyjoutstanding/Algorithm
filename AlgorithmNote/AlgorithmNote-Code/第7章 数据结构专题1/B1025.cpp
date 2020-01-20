/*
 * @Author: wuyangjun
 * @Date: 2019-08-09 15:04:56
 * @LastEditTime: 2019-08-09 15:52:24
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100001;
struct LNode {
    int addr, data, next; //地址，数据，下个地址
    int order; //编号，第几个节点
    // 默认构造函数，初始化
    LNode() {
        order = maxn;
    }
}SLink[maxn], node; //静态链表
bool cmp(LNode a, LNode b) {
    return a.order < b.order; //按序号升序排列
}
int main() {
    int head, N, K; 
    scanf("%d %d %d", &head, &N, &K);
    // 构造静态链表
    for(int i = 0; i < N; i ++) {
        scanf("%d %d %d", &node.addr, &node.data, &node.next);
        SLink[node.addr] = node;
    }
    // 遍历链表，给每个节点按顺序编号,可能存在无效点
    int now = head, cnt = 0; //cnt计数有效点个数
    while(SLink[now].next != -1) {
        SLink[now].order = cnt ++;
        now = SLink[now].next;
    }
    SLink[now].order = cnt ++;
    // 将有效节点移到数组左端
    sort(SLink, SLink + maxn, cmp);
    int groupNum = cnt / K; //需要反转的组数
    // 分组反转
    for(int i = 0; i < groupNum; i ++) {
        reverse(SLink + i * K, SLink + (i + 1) * K);
    }
    // 输出
    for(int i = 0; i < cnt; i ++) {
        printf("%05d %d ", SLink[i].addr, SLink[i].data);
        if(i == cnt - 1) printf("-1\n");
        else printf("%05d\n", SLink[i+1].addr);
    }
    return 0;
}
/*
 * @Author: wuyangjun
 * @Date: 2019-08-09 18:45:34
 * @LastEditTime: 2019-08-09 19:17:27
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
struct LNode {
    int addr, data, next;
    int order;
    LNode() {
        order = maxn;
    }
}SLink[maxn], node;
bool cmp(LNode a, LNode b) {
    // 有效点优先
    if(a.order != b.order) return a.order < b.order;
    else return a.data < b.data; //数据小者优先
}
void print(LNode node) {
    printf("==%05d %d %05d %d\n", node.addr, node.data, node.next, node.order);
}
int main() {
    int N, head;
    scanf("%d %d", &N, &head);
    for(int i = 0; i < N; i ++) {
        scanf("%d %d %d", &node.addr, &node.data, &node.next);
        node.order = 10; //表示有元素
        SLink[node.addr] = node;
    }
    int cnt = 0; //有效点总数
    // 计数有效点，同时打上标记
    for(int p = head; p != -1; p = SLink[p].next) {
        if(SLink[p].order == 10) {
            SLink[p].order = 1; //想分类排序，必须赋同样的值
            cnt ++;
        }
        else break;
    }
    sort(SLink, SLink + maxn, cmp);
    // 输出
    printf("%d ", cnt);
    if(cnt == 0) printf("-1\n"); //一个有效点都没有
    else printf("%05d\n", SLink[0].addr);
    for(int i = 0; i < cnt; i ++) {
        printf("%05d %d ", SLink[i].addr, SLink[i].data);
        if(i == cnt - 1) printf("-1\n");
        else printf("%05d\n", SLink[i+1].addr);
    }
    return 0;
}
/*
 * @Author: wuyangjun
 * @Date: 2019-08-12 11:31:15
 * @LastEditTime: 2019-08-12 12:01:12
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
struct STNode {
    int layer;
    vector<int> child;
}STree[maxn];
int cnt[maxn] = {0};
void layerTraversal(int root) {
    queue<int> q;
    STree[root].layer = 1;
    q.push(root);
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        cnt[STree[now].layer] ++; // 层号出现次数计算
        for(auto p : STree[now].child) {
            STree[p].layer = STree[now].layer + 1;
            q.push(p);
        }
    }
} 
void readData() {
    int N, M;
    scanf("%d %d", &N, &M);
    int cur, n, idx;
    for(int i = 0; i < M; i++) {
        scanf("%d %d", &cur, &n);
        for(int j = 0; j < n; j ++) {
            scanf("%d", &idx);
            STree[cur].child.push_back(idx);
        }
    }
}
int main() {
    readData();
    layerTraversal(1);
    int maxCnt = -1, ans;
    for(int i = 0; i < maxn; i ++) {
        if(maxCnt < cnt[i]) {
            maxCnt = cnt[i];
            ans = i;
        }
    }
    printf("%d %d\n", maxCnt, ans);
    return 0;
}
/*
 * @Author: wuyangjun
 * @Date: 2019-08-12 14:11:40
 * @LastEditTime: 2019-08-12 14:29:01
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
struct STNode {
    vector<int> child;
    bool isRoot; //判断是否为根
    STNode() {isRoot = true;}
}STree[maxn];
int N, M, maxLayer = -1; //结点个数、非叶子个数、最大层数
int leafs[maxn] = {0}; // 每一层叶子个数
// root：当前结点 depth：当前深度
void dfs(int root, int depth) {
    if(STree[root].child.empty()) {
        leafs[depth] ++;
        if(maxLayer < depth) maxLayer = depth; //最大深度
        return;
    }
    for(auto p : STree[root].child) {
        dfs(p, depth + 1);
    }
}
void readData() {
    scanf("%d %d", &N, &M);
    int id, k, idx;
    for(int i = 0; i < M; i ++) {
        scanf("%d %d", &id, &k);
        for(int j = 0; j < k; j ++) {
            scanf("%d", &idx);
            STree[id].child.push_back(idx);
            STree[idx].isRoot = false; //不是根
        }
    }
}
// 从1开始找
int findRoot() {
    for(int i = 1; i < N; i ++) {
        if(STree[i].isRoot) return i;
    }
}
int main() {
    readData();
    int root = findRoot();
    dfs(root, 1);
    for(int i = 1; i <= maxLayer; i ++) {
        printf("%d%s", leafs[i], i == maxLayer ? "\n" : " ");
    }
    return 0;
}
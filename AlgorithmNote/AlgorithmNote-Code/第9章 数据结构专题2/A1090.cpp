/*
 * @Author: wuyangjun
 * @Date: 2019-08-12 10:35:31
 * @LastEditTime: 2019-08-12 10:54:34
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
struct STNode {
    vector<int> child;
}STree[maxn];
double P, r, maxPrice = -1; //root单价，增加比率，最大单价
int tot = 0; // 最大单价的个数
// 找到单价最高的叶子个数及其最大值
void dfs(int root, double price) {
    // 叶子，retailers
    if(STree[root].child.empty()) {
        if(maxPrice < price) {
            maxPrice = price;
            tot = 1; //重新找到最大值
        } 
        else if(maxPrice == price) tot ++; //最大值个数
        return;
    }
    // 遍历所有子结点
    for(auto p : STree[root].child) {
        dfs(p, price * (1 + r / 100));
    }
}
int readData() {
    int n;
    scanf("%d %lf %lf", &n, &P, &r);
    int t, root;
    for(int i = 0; i < n; i ++) {
        scanf("%d", &t);
        if(t != -1) {
            STree[t].child.push_back(i);
        }
        else root = i; // 根节点
    }
    return root;
}
int main() {
    int root = readData();
    dfs(root, P);
    printf("%.2lf %d\n", maxPrice, tot);
    return 0;
}
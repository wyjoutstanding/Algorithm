/*
 * @Author: wuyangjun
 * @Date: 2019-08-12 13:43:22
 * @LastEditTime: 2019-08-12 13:53:27
 * @Github: https://github.com/wyjoutstanding
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
struct STNode {
    vector<int> child;
    bool isRoot;
    STNode() {isRoot = true;}
}STree[maxn];
double P, r, minPrice = 0x7fffffffffff; //root单价，增加比率，最大单价
int N, tot = 0; // 最大单价的个数
// 找到单价最高的叶子个数及其最大值
void dfs(int root, double price) {
    // 叶子，retailers
    if(STree[root].child.empty()) {
        if(minPrice > price) {
            minPrice = price;
            tot = 1; //重新找到最大值
        } 
        else if(minPrice == price) tot ++; //最大值个数
        return;
    }
    // 遍历所有子结点
    for(auto p : STree[root].child) {
        dfs(p, price * (1 + r / 100));
    }
}
void readData() {
    scanf("%d %lf %lf", &N, &P, &r);
    int n, idx;
    double t;
    for(int i = 0; i < N; i ++) {
        scanf("%d", &n);
        if(n != 0) { //叶子，，retailers
            for(int j = 0; j < n; j ++) {
                scanf("%d", &idx);
                STree[i].child.push_back(idx);
                STree[idx].isRoot = false; //i为idx的父结点
            }
        }
    }
}
// 找到root
int findRoot() {
    for(int i = 0; i < N; i ++) {
        if(STree[i].isRoot) return i;
    }
}
int main() {
    readData();
    int root = findRoot();
    dfs(root, P);
    printf("%.4lf %d\n", minPrice, tot);
    return 0;
}
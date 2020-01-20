/*
 * @Author: wuyangjun
 * @Date: 2019-08-12 09:54:35
 * @LastEditTime: 2019-08-12 10:15:26
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
// 静态二叉树
struct STNode {
    double data, price; //权值和单价
    vector<int> child; //孩子
    bool isRoot; //便于判断是否为根
    STNode() {isRoot = true;}
}STree[maxn];
double P, r, tot = 0; //根单价、增加比率、总价
int N; //结点个数
// root：当前结点 price：当前销售单价
double dfs(int root, double price) {
    // 叶子，即retailer
    if(STree[root].child.empty()) return price * STree[root].data;
    double tot = 0; //总和
    // 遍历所有孩子
    for(auto p : STree[root].child) {
        tot += dfs(p, price * (1 + r / 100)); //r%增比
    }
    return tot;
}
void readData() {
    scanf("%d %lf %lf", &N, &P, &r);
    int n, idx;
    double t;
    for(int i = 0; i < N; i ++) {
        scanf("%d", &n);
        if(n == 0) { //叶子，，retailers
            scanf("%lf", &t);
            STree[i].data = t;
        }
        else { //suppliers，distributors
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
    tot = dfs(root, P);
    printf("%.1lf\n", tot);
    return 0;
}
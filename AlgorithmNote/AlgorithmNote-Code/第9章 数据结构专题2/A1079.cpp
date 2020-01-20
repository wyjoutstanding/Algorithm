/*
 * @Author: wuyangjun
 * @Date: 2019-08-12 08:35:40
 * @LastEditTime: 2019-08-12 09:20:57
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
void layerTravesal(int root) {
    queue<int> q;
    q.push(root);
    STree[root].price = P; //根销售的单价
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        double price = (now == root) ? STree[now].price : STree[now].price * (1 + r / 100); //下一层的单价,r%，有百分号
        // 叶子，即retailer
        if(STree[now].child.empty()) tot += price * STree[now].data;
        else {
            for(auto p : STree[now].child) {
                STree[p].price = price;
                q.push(p);
            }
        }
    }
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
    layerTravesal(root);
    printf("%.1lf\n", tot);
    return 0;
}
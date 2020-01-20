/*
 * @Author: wuyangjun
 * @Date: 2019-08-13 13:55:20
 * @LastEditTime: 2019-08-13 14:21:22
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
struct STNode {
    int data;
    int lchild, rchild;
    STNode() {
        lchild = -1;
        rchild = -1;
    }
}STree[maxn];
int N, number[maxn], idx = 0; //结点总数、输入权值序列、升序排列后权值序列下标、
vector<int> layer; //层序遍历序列，便于输出
void inorderTraversal(int root) {
    if(root == -1) return;
    inorderTraversal(STree[root].lchild);
    STree[root].data = number[idx++]; //中序遍历填入
    inorderTraversal(STree[root].rchild);
}
void layerTraversal(int root) {
    queue<int> q;
    q.push(root);
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        layer.push_back(STree[now].data);
        if(STree[now].lchild != -1) q.push(STree[now].lchild);
        if(STree[now].rchild != -1) q.push(STree[now].rchild);
    }
}
void showResult() {
    for(int i = 0; i < N; i ++) {
        printf("%d%s", layer[i], i == N - 1 ? "\n" : " ");
    }
}
void readData() {
    scanf("%d", &N);
    int l, r;
    for(int i = 0; i < N; i ++) {
        scanf("%d %d", &l, &r);
        STree[i].lchild = l;
        STree[i].rchild = r;
    }
    for(int i = 0; i < N; i ++) {
        scanf("%d", &number[i]);
    }
}
int main() {
    readData();
    sort(number, number + N); //升序排序，BST中序遍历为升序
    inorderTraversal(0);
    layerTraversal(0);
    showResult();
    return 0;
}
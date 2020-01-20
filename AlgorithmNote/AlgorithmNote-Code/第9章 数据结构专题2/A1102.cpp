/*
 * @Author: wuyangjun
 * @Date: 2019-08-11 20:27:00
 * @LastEditTime: 2019-08-11 21:02:23
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 21;
struct STNode {
    int data; //和下标一样，所以不要此项也行
    int lchild, rchild, father; //左右子树, 父结点下标
    STNode() { //初始化，-1表示NULL
        lchild = -1;
        rchild = -1;
        father = -1;
    }
}STree[maxn]; //静态数组实现
vector<int> layer, in;
// 查找根结点，类似并查集
int findRoot(int N) {
    for(int i = 0; i < N; i ++) {
        if(STree[i].lchild != -1) STree[STree[i].lchild].father = i;
        if(STree[i].rchild != -1) STree[STree[i].rchild].father = i;        
    }
    for(int i = 0; i < N; i ++) {
        if(STree[i].father == -1) return i;
    }
}
// 交换左右子树
void invertBT(int root) {
    // 空结点则结束
    if(root == -1) return;
    swap(STree[root].lchild, STree[root].rchild); //交换左右子树下标
    invertBT(STree[root].lchild);
    invertBT(STree[root].rchild);
}
// 层序遍历
void layerTraverse(int root) {
    queue<int> q;
    q.push(root);
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        layer.push_back(now);
        if(STree[now].lchild != -1) q.push(STree[now].lchild);
        if(STree[now].rchild != -1) q.push(STree[now].rchild);
    }
}
// 先序遍历
void inTraverse(int root) {
    if(root == -1) return;
    inTraverse(STree[root].lchild);
    in.push_back(root);
    inTraverse(STree[root].rchild);
}
void showResult() {
    for(int i = 0; i < layer.size(); i ++) {
        printf("%d%s", layer[i], i == layer.size() - 1 ? "\n" : " ");
    }
    for(int i = 0; i < in.size(); i ++) {
        printf("%d%s", in[i], i == in.size() - 1 ? "\n" : " ");
    }
}
int main() {
    int n;
    scanf("%d", &n);
    char a, b;
    for(int i = 0; i < n; i ++) {
        getchar(); //必须先吸收换行
        scanf("%c %c", &a, &b);
        if(a != '-') STree[i].lchild = a - '0';
        if(b != '-') STree[i].rchild = b - '0';
    }
    int root = findRoot(n);
    invertBT(root);
    layerTraverse(root);
    inTraverse(root);
    showResult();
    return 0;
}
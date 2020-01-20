/*
 * @Author: wuyangjun
 * @Date: 2019-08-11 16:47:03
 * @LastEditTime: 2019-08-11 17:19:26
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct TNode {
    int data;
    TNode *lchild, *rchild;
};
vector<int> op, post; //操作序列、后序遍历结果
int N, cnt = 0; //结点总数、当前操作下标
// 遍历操作数组，idx为全局变量cnt的引用，表示当前的操作
TNode* createTree(int &idx) {
    // 遍历完所有操作或pop直接返回空
    if(idx == 2 * N || op[idx] == -1) return NULL;
    TNode* root = new TNode;
    root->data = op[idx];
    root->lchild = createTree(++idx); //左子树优先
    root->rchild = createTree(++idx);
    return root;
}
// 后序遍历
void postTraverse(TNode* root) {
    if(root == NULL) return;
    postTraverse(root->lchild);
    postTraverse(root->rchild);
    post.push_back(root->data);
}
// 打印结果
void showResult() {
    for(int i = 0; i < N; i ++) {
        printf("%d%s", post[i], i == N - 1 ? "\n" : " ");
    }
}
int main() {
    scanf("%d", &N);
    string s;
    int t;
    for(int i = 0; i < 2 * N; i ++) {
        cin >>s;
        if(s == "Push") { //push存放输入的数据
            scanf("%d", &t);
            op.push_back(t);
        }
        else op.push_back(-1); //pop用-1表示
    }
    postTraverse(createTree(cnt));
    showResult();
    return 0;
}
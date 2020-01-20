/*
 * @Author: wuyangjun
 * @Date: 2019-08-12 20:58:11
 * @LastEditTime: 2019-08-12 21:34:22
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct TNode {
    int data;
    TNode *lchild, *rchild;
    TNode() {
        lchild = NULL;
        rchild = NULL;
    }
};
TNode *root = NULL, *rootImage = NULL; //正常和镜像BST
vector<int> origin, preNormal, preImage, post; //存放输入、先序、先序镜像、后序序列
// 正常插入
void insert(TNode* &root, int x) {
    if(root == NULL) {
        root = new TNode;
        root->data = x;
        return;
    }
    if(x < root->data) insert(root->lchild, x);
    else insert(root->rchild, x);
}
// 镜像插入：只需改变大小关系即可
void insertImage(TNode* &root, int x) {
    if(root == NULL) {
        root = new TNode;
        root->data = x;
        return;
    }
    if(x >= root->data) insertImage(root->lchild, x);
    else insertImage(root->rchild, x);
}
// 创建正常和镜像BST
void createBST() {
    int N;
    scanf("%d", &N);
    int t;
    for(int i = 0; i < N; i ++) {
        scanf("%d", &t);
        origin.push_back(t); //保存原始序列
        insert(root, t); //正常BST
        insertImage(rootImage, t); //镜像BST
    }
}
// 先序遍历
void preorderTraversal(TNode* root, vector<int> &pre) {
    if(root == NULL) return;
    pre.push_back(root->data);
    preorderTraversal(root->lchild, pre);
    preorderTraversal(root->rchild, pre);
}
// 后序遍历
void postorderTraversal(TNode* root) {
    if(root == NULL) return;
    postorderTraversal(root->lchild);
    postorderTraversal(root->rchild);
    post.push_back(root->data);
}
void print(TNode* root) {
    printf("YES\n");
    postorderTraversal(root);
    for(int i = 0; i < post.size(); i ++) {
        printf("%d%s", post[i], i == post.size() - 1 ? "\n" : " ");
    }
}
int main() {
    createBST();
    preorderTraversal(root, preNormal);
    preorderTraversal(rootImage, preImage);
    if(origin == preNormal) print(root);
    else if(origin == preImage) print(rootImage); 
    else printf("NO\n");
    return 0;
}
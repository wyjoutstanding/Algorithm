/*
 * @Author: wuyangjun
 * @Date: 2019-08-13 15:12:12
 * @LastEditTime: 2019-08-13 16:42:19
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct TNode {
    int data, height;
    TNode *lchild, *rchild;
    TNode() {
        height = 0;
        lchild = NULL;
        rchild = NULL;
    }
};
// 获取当前结点高度，需考虑空
int getHeight(TNode* root) {
    return root == NULL ? 0 : root->height;
}
// 更新当前结点高度，左右子树较高者加1
void updateHeight(TNode* root) {
    root->height = max(getHeight(root->lchild), getHeight(root->rchild)) + 1;
}
// 获取平衡因子：左-右
int getBalanceFactor(TNode* root) {
    return getHeight(root->lchild) - getHeight(root->rchild);
}
// 右旋：改变结构，需引用&
void R(TNode* &root) {
    TNode* tmp = root->lchild;
    root->lchild = tmp->rchild;
    tmp->rchild = root;
    updateHeight(root); //更新根的高度，必须先更新根，因为他在下方
    updateHeight(tmp);  //更新被交换上去的点的高度
    root = tmp; //新的根结点
}
// 左旋：与右旋互逆，交换左右子树即可
void L(TNode* &root) {
    TNode* tmp = root->rchild;
    root->rchild = tmp->lchild;
    tmp->lchild = root;
    updateHeight(root);
    updateHeight(tmp);
    root = tmp;
}
// 封装结点平衡判断及其旋转操作
void adjust(TNode* &root) {
    updateHeight(root); //更新当前结点高度
    if(getBalanceFactor(root) == 2) { // 离插入点最近的不平衡点
        if(getBalanceFactor(root->lchild) == 1) { // LL
            R(root);
        }
        else { // LR
            L(root->lchild);
            R(root);
        }
    }
    else if(getBalanceFactor(root) == -2) { // 该分支必须明确指出，否则平衡因子为1时也会调整
        if(getBalanceFactor(root->rchild) == -1) { // RR
            L(root);
        }
        else { // RL
            R(root->rchild);
            L(root);
        }
    }
}
// 递归插入
void insert(TNode* &root, int x) {
    if(root == NULL) {
        root = new TNode;
        root->data = x;
        updateHeight(root); //更新插入的点高度，为后续点高度准备
        return;
    }
    if(x < root->data) insert(root->lchild, x);// 往左子树递归插入
    else insert(root->rchild, x); // 右子树递归插入
    adjust(root); // 判断是否失衡，若是则旋转调整
}
// 读入数据时插入创建AVL
void createAVL(TNode* &root) {
    int n;
    scanf("%d", &n);
    int t;
    for(int i = 0; i < n; i ++) {
        scanf("%d", &t);
        insert(root, t);
    }
}
int main() {
    TNode* root = NULL;
    createAVL(root);
    printf("%d\n", root->data);
    return 0;
}
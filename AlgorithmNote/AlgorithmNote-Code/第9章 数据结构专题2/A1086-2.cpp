/*
 * @Author: wuyangjun
 * @Date: 2019-08-11 19:17:16
 * @LastEditTime: 2019-08-11 19:33:31
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct TNode {
    int data;
    TNode *lchild, *rchild;
};
int n;
vector<int> pre, in, post; //前中后序遍历结果
TNode* createTree(int preL, int preR, int inL, int inR) {
    if(preL > preR) return NULL; //边界
    TNode* root = new TNode;
    root->data = pre[preL]; //左侧第一个数为根
    // 根在in中的位置
    int k = find(in.begin() + inL, in.begin() + inR + 1, root->data) - in.begin();
    int numLeft = k - inL;//左子树结点个数
    root->lchild = createTree(preL + 1, preL + numLeft, inL, k - 1);
    root->rchild = createTree(preL + numLeft + 1, preR, k + 1, inR);
    return root;
}
void postTraverse(TNode* root) {
    if(root == NULL) return;
    postTraverse(root->lchild);
    postTraverse(root->rchild);
    post.push_back(root->data);
}
void showResult() {
    for(int i = 0; i < post.size(); i ++) {
        printf("%d%s", post[i], i == post.size() - 1 ? "\n" : " ");
    }
}
void init() {
    scanf("%d", &n);
    string str;
    int t;
    stack<int> s; 
    // 读入数据并计算出先序和中序序列
    for(int i = 0; i < 2 * n; i ++) {
        cin >>str;
        if(str == "Push") {
            scanf("%d", &t);
            pre.push_back(t); //push对应前序
            s.push(t); //栈为了中序输出
        }
        else {
            in.push_back(s.top()); //中序
            s.pop();
        }
    }
}
int main() {
    init();
    postTraverse(createTree(0, n - 1, 0, n - 1));
    showResult();
    return 0;
}
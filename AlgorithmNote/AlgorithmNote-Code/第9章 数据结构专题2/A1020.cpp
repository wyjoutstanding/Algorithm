/*
 * @Author: wuyangjun
 * @Date: 2019-08-11 14:48:08
 * @LastEditTime: 2019-08-11 15:24:04
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct TNode { //树结点
    int data;
    TNode *lchild, *rchild;
    TNode() { //默认构造函数初始化
        lchild = NULL;
        rchild = NULL;
    }
};
int n; //结点个数
vector<int> post, in, layer; //存放后、中、层序遍历结果
TNode* createTree(int postL, int postR, int inL, int inR) {
    // printf("==%d %d %d %d\n", postL, postR, inL, inR);
    if(postL > postR) return NULL; //后序遍历结束，返回
    TNode* root = new TNode; //申请结点
    root->data = post[postR]; //数据域,后序从最右边开始
    // 找到根在中序的位置
    int k  = find(in.begin() + inL, in.begin() + inR + 1, post[postR]) - in.begin();
    int numLeft = k - inL; //左子树结点个数
    // 左子树：post:[postL,postL+numLeft-1] in:[inL,k-1]
    root->lchild = createTree(postL, postL + numLeft - 1, inL, k - 1);
    // 右子树：post:[postL+numLeft,postR-1] in:[k+1,inR]
    root->rchild = createTree(postL + numLeft, postR - 1, k + 1, inR);
    return root; //返回根结点
}
// 层序遍历：与BFS一样
void layerTraverse(TNode* root) {
    queue<TNode*> q;
    q.push(root);
    while(!q.empty()) {
        TNode* now = q.front();
        q.pop();
        layer.push_back(now->data);
        if(now->lchild != NULL) q.push(now->lchild);
        if(now->rchild != NULL) q.push(now->rchild);
    }
}
// 读入数据
void readData() {
    scanf("%d", &n);
    int t;
    for(int i = 0; i < n; i ++) {
        scanf("%d", &t);
        post.push_back(t);
    }
    for(int i = 0; i < n; i ++) {
        scanf("%d", &t);
        in.push_back(t);
    }
    // for(int i = 0; i < n; i ++) {
    //     printf("%d ", in[i]);
    // }
}
// 打印层序结果
void showResult() {
    for(int i = 0; i < n; i ++) {
        printf("%d%s", layer[i], i == n - 1 ? "\n" : " ");
    }
}
int main() {
    readData();
    layerTraverse(createTree(0, n - 1, 0, n - 1));
    showResult();
    return 0;
}
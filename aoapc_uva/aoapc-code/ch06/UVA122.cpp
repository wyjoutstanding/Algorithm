#include<bits/stdc++.h>
using namespace std;
struct Node {
    int val, assignCnt=0; // 值，被赋值次数
    Node *l=NULL, *r=NULL; // 左右子树
};
Node* btree=NULL; // 二叉树根
void insertNode(string s, Node* root) { // 根据路径s插入节点
    int i = s.find(',');
    string ds=s.substr(i+1,s.size()-i-1-1); // 方向
    for (int j=0; j < ds.size();  j++) { // 遍历路径
        if (ds[j] == 'L') {
            if (root->l == NULL) root->l = new Node; // 必须创建节点，否则连接会断开
            root = root->l;
        }
        else if (ds[j] == 'R') {
            if (root->r == NULL) root->r = new Node;
            root = root->r;
        }
    }
    root->val = stoi(s.substr(1,i)); // 赋值
    root->assignCnt ++; // 赋值次数累计
}
void layerTra(Node* root) { // 层次遍历
    bool isLegal=true; // 标记是否合法：每个点仅赋值一次
    vector<int> out; // 层次遍历输出存储
    queue<Node*> q; // 遍历队列
    if (root != NULL) q.push(root); // 初始化
    while (!q.empty() && isLegal) {
        Node* node = q.front(); q.pop();
        if (node->assignCnt != 1) isLegal = false; // 非法：赋值0或多次
        else {
            out.push_back(node->val);
            if (node->l != NULL) q.push(node->l); // 非空压入左右子树
            if (node->r != NULL) q.push(node->r);
        }
    }
    if (isLegal) { // 合法输出
        for (int i=0; i < out.size(); i ++) 
            printf("%d%s", out[i], i == out.size()-1 ? "\n" : " ");
    }
    else printf("not complete\n");
}
int main() {
    string s;
    while (cin >>s) {
        if (s == "()") {
            layerTra(btree);
            btree=NULL; // 此处可改为递归释放内存，偷个懒，不写了
        }
        else {
            if (btree == NULL) btree = new Node; // 根必须先创建，否则是空值则无法连接节点
            insertNode(s, btree);
        }
    }
    return 0;
}
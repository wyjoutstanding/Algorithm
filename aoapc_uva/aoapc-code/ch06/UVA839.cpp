#include<bits/stdc++.h>
using namespace std;
struct Node {
    int wl, wr, dl, dr;
    Node *l=NULL, *r=NULL;
};
string s;
int T;
bool readInput(int& wl, int& dl, int& wr, int& dr) { // 读取输入
    if (getline(cin, s) && !s.empty()) {
        stringstream input(s);
        input >>wl >>dl >>wr >>dr;
        return true; // 成功
    }
    else return false; // 失败
}
Node* createTree() { // 递归建树（先序）
    Node* root = NULL;
    int wl, dl, wr, dr;
    if (readInput(wl, dl, wr, dr)) { // 读入成功
        root = new Node;
        root->wl = wl; root->wr = wr;
        root->dl = dl; root->dr = dr;
        if (wl == 0) root->l = createTree();
        if (wr == 0) root->r = createTree(); 
    }
    return root;
}
int dfs(Node* root) { // 后序遍历并判断是否平衡
    if (root == NULL) return -1; // 空树
    if (root->l != NULL) root->wl = dfs(root->l); // 左子树
    if (root->r != NULL) root->wr = dfs(root->r); // 右子树
    if (root->wl == -1 || root->wr == -1) return -1; // 非法，剪枝
    if (root->wl * root->dl == root->wr*root->dr) return root->wl+root->wr; // 平衡，返回左右重量和
    else return -1; // 非法标志
}
int main() {
    scanf("%d  ", &T); // 两个空格可吸收换行
    for (int i = 0; i < T; i ++) {
        Node* bt = createTree();
        printf("%s%s\n", dfs(bt) != -1 ? "YES" : "NO", i != T-1 ? "\n" : "");
        if (i != T-1) getchar(); // 空行吸收
    }
    return 0;
}
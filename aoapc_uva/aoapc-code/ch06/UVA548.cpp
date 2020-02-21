#include<bits/stdc++.h>
using namespace std;
struct Node {
    int v; // 值
    Node *l=NULL, *r=NULL; // 左右子树
};
vector<int> in, post; // 中序，后序存储
int minSum=0x3fffff, ans=-1; // 路径最小和，答案
Node* createTree(int i1, int j1, int i2, int j2) { // 建树-- in:[i1,j1) post:[i2,j2)
    if (i1 >= j1 || i2 >= j2) return NULL; // 空树
    Node* root = new Node;
    root->v = post[j2-1]; // 后序结尾为个
    int j = find(in.begin()+i1, in.begin()+j1, post[j2-1]) - in.begin(); // 在in中查找
    root->l = createTree(i1, j, i2, i2+(j-i1)); // 左子树建立
    root->r = createTree(j+1, j1, i2+(j-i1), j2-1); // 右子树建立
    return root;
}
void dfs(Node* root, int sum) { // 计算到每个叶子的路径和并记录最小者
    if (root->l == NULL && root->r == NULL) { // 叶子
        sum += root->v;
        if (sum < minSum || (sum == minSum && ans > root->v)) { // 总和最小；若相同去叶子值最小者
            minSum = sum;
            ans = root->v;
        }
        return;
    }
    if (root->l != NULL) dfs(root->l, root->v+sum); // 非空，则访问左子树
    if (root->r != NULL) dfs(root->r, root->v+sum); // 非空，则访问右子树
}
int main() {
    string s1, s2, st;
    while (getline(cin, s1) && getline(cin, s2)) {
        in.clear(); post.clear(); // 初始化
        stringstream input1(s1), input2(s2);
        while (input1 >>st) in.push_back(stoi(st)); // 中序存储
        while (input2 >>st) post.push_back(stoi(st)); // 后续存储
        Node* btree = createTree(0, in.size(), 0, post.size()); // 建树
        minSum=0x3fffff; dfs(btree, 0); // 遍历计算
        printf("%d\n", ans);
    }
    return 0;
}
/*
 * @Author: wuyangjun
 * @Date: 2019-08-12 23:32:22
 * @LastEditTime: 2019-08-12 23:42:13
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
int CBST[maxn], in[maxn]; //完全二叉排序树、中序遍历序列
int N, idx = 0; //结点数
// 中序遍历将in的值依次填入相应结点
void inorderTravesal(int root) {
    if(root > N) return;
    inorderTravesal(2 * root);
    CBST[root] = in[idx ++]; //填入相应值
    inorderTravesal(2 * root + 1);
}
int main() {
    scanf("%d", &N);
    for(int i = 0; i < N; i ++) {
        scanf("%d", &in[i]);
    }
    sort(in, in + N); //BST中序必为升序
    inorderTravesal(1);
    // 数组存放顺序即为层序遍历，从1开始存
    for(int i = 1; i <= N; i ++) {
        printf("%d%s", CBST[i], i == N ? "\n" : " ");
    }
    return 0;
}
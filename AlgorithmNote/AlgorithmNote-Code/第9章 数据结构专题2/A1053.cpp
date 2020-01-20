/*
 * @Author: wuyangjun
 * @Date: 2019-08-12 14:50:47
 * @LastEditTime: 2019-08-12 16:10:17
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
struct STNode {
    int data; //权重
    vector<int> child;
}STree[maxn];
int N, M, S;
vector<int> tmp; //临时存放符合条件序列
vector<vector<int> > ans; //结果存放
// root：当前结点 sum：从根到当前结点的权重总和（不包括当前结点）
void dfs(int root, int sum) {
    sum += STree[root].data;
    tmp.push_back(STree[root].data); //保存路径权重
    if(STree[root].child.empty()) { //叶子
        if(sum == S) { //满足条件
            ans.push_back(tmp); //保存结果
        }
        return ;
    }
    if(sum >= S) return; //剪枝
    for(auto p : STree[root].child) { //遍历所有子结点
        dfs(p, sum); 
        tmp.pop_back(); //弹出返回的结点
    }
}
// 字典序非升序
bool cmp(vector<int> &a, vector<int> &b) {
    int len = min(a.size(), b.size());
    for(int i = 0; i < len; i ++) {
        if(a[i] != b[i]) return a[i] > b[i];
    }
    return false; //完全相同，必须返回false，返回true/不写这个会报段错误
}
void showResult() {
    sort(ans.begin(), ans.end(), cmp); //字典序非降序排列
    for(auto vec : ans) {
        for(int i = 0; i < vec.size(); i ++) {
            printf("%d%s", vec[i], i == vec.size() - 1 ? "\n" : " ");
        }
    }
}
void readData() {
    scanf("%d %d %d", &N, &M, &S);
    for(int i = 0; i < N; i ++) scanf("%d", &STree[i].data);
    int id, k, idx;
    for(int i = 0; i < M; i ++) {
        scanf("%d %d", &id, &k);
        for(int j = 0; j < k; j ++) {
            scanf("%d", &idx);
            STree[id].child.push_back(idx);
        }
    }
}
int main() {
    readData();
    dfs(0, 0);
    showResult();
    return 0;
}
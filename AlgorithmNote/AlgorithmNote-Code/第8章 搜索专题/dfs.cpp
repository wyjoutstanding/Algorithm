/*
 * @Author: wuyangjun
 * @Date: 2019-08-10 19:45:33
 * @LastEditTime: 2019-08-10 21:38:08
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int N, K, X, maxSumSquare = -1;
vector<int> ans, tmp;
void print() {
    if(ans.empty()) printf("NULL SET\n");
    else {
        for(int i = 0; i < ans.size(); i ++) {
            printf("%d%s", ans[i], i == ans.size() - 1 ? "\n" : " ");
        }
    }
}
void dfs(int idx) {
    if(idx == N + 1) {
        print();
        return;
    }
    ans.push_back(idx);
    dfs(idx + 1); //选
    ans.pop_back();
    dfs(idx + 1); //不选
}
// idx：当前元素 nowK：已选个数
void dfs_K(int idx, int nowK) {
    if(nowK == K) { //满足条件，输出并返回，剪枝
        print();
        return;
    }
    if(idx == N + 1) return; //边界
    ans.push_back(idx);
    dfs_K(idx + 1, nowK + 1); //选
    ans.pop_back();
    dfs_K(idx + 1, nowK); //不选
}
// idx：当前元素 nowK：已选个数 sum：已选元素总和
void dfs_K_X(int idx, int nowK, int sum) {
    if(nowK == K && sum == X) { //添加边界+剪枝条件
        print();
        return;
    }
    if(idx == N + 1 || sum >= X) return; //添加剪枝条件
    ans.push_back(idx);
    dfs_K_X(idx + 1, nowK + 1, sum + idx); //选
    ans.pop_back();
    dfs_K_X(idx + 1, nowK, sum); //不选
}
// idx：当前元素 nowK：已选个数 sum：已选元素总和 sumSquare：已选元素平方和
void dfs_K_X_MaxSumSquare(int idx, int nowK, int sum, int sumSquare) {
    if(nowK == K && sum == X) { //满足条件
        if(sumSquare > maxSumSquare) { //最优选择，maxSumSquare为全局最大平方和
            maxSumSquare = sumSquare;
            ans = tmp;
        }
        return;
    }
    if(idx == N + 1 || sum >= X) return; //剪枝边界
    tmp.push_back(idx); //存到中间容器
    dfs_K_X_MaxSumSquare(idx + 1, nowK + 1, sum + idx, sumSquare + idx * idx); //选
    tmp.pop_back();
    dfs_K_X_MaxSumSquare(idx + 1, nowK, sum, sumSquare); //不选
}
int main() {
    N = 5;
    K = 3;
    X = 10;
    // dfs(1);
    // dfs_K(1, 0);
    // dfs_K_X(1, 0, 0);
    dfs_K_X_MaxSumSquare(1, 0, 0, 0);
    print();
    return 0;
}
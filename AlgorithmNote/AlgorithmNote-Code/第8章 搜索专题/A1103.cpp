/*
 * @Author: wuyangjun
 * @Date: 2019-08-10 09:35:52
 * @LastEditTime: 2019-08-10 12:34:04
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
vector<int> tmp, ans; //存放中间序列和结果序列
int maxSum = -1; //最大P次方和
int N, K, P;
int powP[22]; //P次方表
// 初始化1~21的P次方表
void initPow() {
    for(int i = 1; i < 22; i ++) {
        int sum = 1;
        for(int j = 0; j < P; j ++) {
            sum *= i;
        }
        powP[i] = sum;
    }
}
void print(vector<int> ans) {
    if(ans.empty()) printf("Impossible\n");
    else {
        printf("%d = ", N);
        for(int i = ans.size() - 1; i >= 0; i --) {
            printf("%d^%d%s", ans[i], P, i == 0 ? "\n" : " + ");
        }
    }
}
// 降序排列后比较字典序
int cmpVec(vector<int>& a, vector<int>& b) {
    for(int i = a.size() - 1; i >= 0; i --) {
        if(a[i] < b[i]) return -1;
        if(a[i] > b[i]) return 1;
    }
}
// idx：取值[1,N] nowK:当前已选取个数 sum：当前已选取序列和 sumP：当前已选序列P次方和
void dfs(int idx, int nowK, int sum, int sumP) {
    // K个数的P次方和为N
    if(nowK == K && sumP == N) {
        if(sum > maxSum) { //序列和大者优先
            maxSum = sum;
            ans = tmp;
        }
        else if(sum == maxSum) {  // 选排序后字典序大者
            if(cmpVec(ans, tmp) == -1) ans = tmp;
        }
        return;
    }
    // 已遍历所有取值、当前已选个数大于K、K个数的P次方和大于N
    if(sumP + powP[idx] > N || nowK >= K) return; //边界+剪枝
    tmp.push_back(idx); //选
    dfs(idx, nowK + 1, sum + idx, sumP + powP[idx]); //idx不加1，可能重复选取
    tmp.pop_back(); //不选
    dfs(idx + 1, nowK, sum, sumP);
}
int main() {
    scanf("%d %d %d", &N, &K, &P);
    initPow();
    dfs(1, 0, 0, 0);
    print(ans);
    return 0;
}
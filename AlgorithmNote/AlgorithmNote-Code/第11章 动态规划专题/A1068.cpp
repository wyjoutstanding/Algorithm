/*
 * @Author: wuyangjun
 * @Date: 2019-08-23 21:08:07
 * @LastEditTime: 2019-08-23 23:12:31
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 10010;
int a[maxn] = {0}, N, M;
vector<int> tmp, ans;
void dfs(int idx, int sum) {
    if(sum == M) { // 满足条件
        ans = tmp;
        return;
    }
    if(idx == N || sum > M || !ans.empty()) return; // 边界+剪枝，找到第一个解就退出
    tmp.push_back(idx);
    dfs(idx + 1, sum + a[idx]); // 选
    tmp.pop_back();
    dfs(idx + 1, sum); // 不选
}
int main() {
    scanf("%d %d", &N, &M);
    for(int i = 0; i < N; i ++) scanf("%d", &a[i]);
    sort(a, a + N); 
    dfs(0, 0);
    if(ans.empty()) printf("No Solution\n");
    else {
        for(int i = 0; i < ans.size(); i ++) {
            printf("%d%s", a[ans[i]], i == ans.size() - 1 ? "\n" : " ");
        }
    }
    return 0;
}
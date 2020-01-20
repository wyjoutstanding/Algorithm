/*
 * @Author: wuyangjun
 * @Date: 2019-08-13 19:16:26
 * @LastEditTime: 2019-08-13 20:00:57
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
int hobby[maxn], father[maxn], cnt[maxn] = {0};
int N; // 总人数
void init() {
    fill(hobby, hobby + maxn, -1);
    for(int i = 1; i < maxn; i ++) father[i] = i;
}
// 查
int findRoot(int x) {
    int a = x; // 保存起点
    while(x != father[x]) x = father[x]; //找到根结点
    // 路径压缩
    while(a != father[a]) {
        int t = a; // 保存孩子
        a = father[a]; // 回溯父亲
        father[t] = x; // 父亲改为root
    }
    return x;
}
// 并
void unionSet(int a, int b) {
    int fa = findRoot(a);
    int fb = findRoot(b);
    if(fa != fb) {
        father[fa] = fb;
    }
}
void showResult() {
    vector<int> ans;
    for(int i = 1; i <= N; i ++) cnt[findRoot(i)] ++; // 计算每个根结点出现次数，保证每个点都被查找，压缩路径
    for(int i = 1; i <= N; i ++) {
        if(cnt[i] != 0) ans.push_back(cnt[i]); // 将每个根结点出现次数存到ans，便于排序，统计个数
    }
    sort(ans.begin(), ans.end(), [](int a, int b){return a > b;}); //非降序，lamda语法
    int len = ans.size();
    printf("%d\n", len);
    for(int i = 0; i < len; i ++) printf("%d%s", ans[i], i == len - 1 ? "\n" : " ");
}
int main() {
    init();
    scanf("%d", &N);
    int n, t;
    // 第i个人
    for(int i = 1; i <= N; i ++) {
        scanf("%d:", &n);
        for(int j = 0; j < n; j ++) { // 兴趣
            scanf("%d", &t);
            if(hobby[t] == -1) hobby[t] = i;
            else unionSet(hobby[t], i);
        }
    }
    showResult();
    return 0;
}
/*
 * @Author: wuyangjun
 * @Date: 2019-08-07 16:04:30
 * @LastEditTime: 2019-08-07 16:27:36
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 51;
set<int> sets[maxn];
void initSets() {
    int n;
    scanf("%d", &n);
    int m;
    for(int i = 1; i <= n; i ++) {
        scanf("%d", &m);
        int t;
        for(int j = 0; j < m; j ++) {
            scanf("%d", &t);
            sets[i].insert(t);
        }
    }
}
// 计算两个集合的交并集的元素个数即可
double getSimilarity(set<int> a, set<int> b) {
    int Nc = 0, Nt = 0;
    // 交集元素个数
    for(auto p : b) {
        if(a.count(p) != 0) Nc ++;
    }
    Nt = a.size() + b.size() - Nc; //并集元素个数
    return ((double)Nc / Nt) * 100;
}
void query() {
    int n;
    scanf("%d", &n);
    int a, b;
    for(int i = 0; i < n; i ++) {
        scanf("%d %d", &a, &b);
        printf("%.1lf%\n", getSimilarity(sets[a], sets[b]));
    }
}
int main() {
    initSets();
    query();
    return 0;
}
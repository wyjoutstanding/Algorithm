#include<bits/stdc++.h>
using namespace std;
map<int,int> cnt; //  位置->个数；统计每叠对应权值总和
void createTree(int pos=0) { // 先序隐式建树，同时累加每个位置的值
    int v; scanf("%d", &v);
    if (v != -1) {
        cnt[pos] += v; // 累加值
        createTree(pos-1); // 左子树
        createTree(pos+1); // 右子树
    }
}
int main() {
    for (int i = 1; ; i ++) {
        cnt.clear(); createTree(0); // 初始化，隐式建树求值
        if (cnt.empty()) break; // 读到最后一个-1，结束
        printf("Case %d:\n", i);
        for (auto p : cnt) { // map按照key的字典序升序排列
            printf("%d%s", p.second, p.first == cnt.rbegin()->first ? "\n" : " ");
        }
        puts(""); // 每个测试用例后均有空行
    }
    return 0;
}
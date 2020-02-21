#include<bits/stdc++.h>
using namespace std;
int n, m, op, a, b, num=0;
int main() {
    while (scanf("%d %d", &n, &m) == 2) {
        list<int> l(n); // 存储1-n
        vector<list<int>::iterator> pos(n+1); // pos[i]表示数字i在list中的指针
        int idx=1, inv=0;
        for (auto p=l.begin(); p != l.end(); p++, idx++) { // 初始化
            *p = idx;
            pos[idx] = p;
        }
        for (int i = 0; i < m; i ++) { // m个操作
            scanf("%d", &op);
            if (op != 4) scanf("%d %d", &a, &b);
            if (op == 4) inv = !inv; // 反转标记
            else if (op == 3) swap(*pos[a],*pos[b]), swap(pos[a], pos[b]); // 交换
            else {
                l.erase(pos[a]); // 先擦除
                if (inv == 1) op = 3 - op; // 反转则左右交换
                auto p=pos[b];
                if (op == 2) p ++; // 插入右侧
                pos[a] = l.insert(p, a); // a的新位置
            }
        }
        long long cnt=1, oddsum=0; // 避免溢出
        for (auto p=l.begin(); p != l.end(); p++, cnt++) {
            if (cnt % 2 == 1) oddsum += *p;
        }
        printf("Case %d: %lld\n", ++num, (inv == 1 && n%2 == 0) ?  (long long)n*(n+1)/2-oddsum : (long long)oddsum);
    }
    return 0;
}
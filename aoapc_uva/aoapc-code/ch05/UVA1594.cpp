#include<bits/stdc++.h>
using namespace std;
int T, n, t;
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        vector<int> a, b(n), zero(n, 0);
        for (int i = 0; i < n; i ++) { // 输入n元组
            scanf("%d", &t);
            a.push_back(t);
        }
        set<vector<int> > _set; // 集合判重
        int flag = 0; // 标记结果
        while (flag == 0) {
            if (a == zero) flag = 1; // 全0
            else if (_set.find(a) != _set.end()) flag = 2; // 重复
            else {
                _set.insert(a);
                for (int i = 0; i < n; i ++) b[i] = abs(a[i] - a[(i+1)%n]); // ducci下一个序列
                a = b;
            }
        }
        printf("%s\n", flag == 1 ? "ZERO" : "LOOP");
    }
    return 0;
}
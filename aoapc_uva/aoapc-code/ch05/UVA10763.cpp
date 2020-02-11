#include<bits/stdc++.h>
using namespace std;
int n, a, b;
int main() {
    while (cin >>n && n != 0) {
        map<int, int> cnt; // 每个学校对应的人数增减变化量
        for (int i = 0; i < n; i ++) {
            scanf("%d %d", &a, &b);
            cnt[a] --; // 出去-
            cnt[b] ++; // 进来+
        }
        bool isWork = true; // 标记是否可行
        for (auto p : cnt) {
            if (p.second != 0) { // 出现非0，说明有人不匹配
                isWork = false;
                break;
            }
        }
        printf("%s\n", isWork ? "YES" : "NO");
    }
    return 0;
}
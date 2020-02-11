#include<bits/stdc++.h>
using namespace std;
int n;
int main() {
    while (cin >>n && n != 0) {
        printf("Discarded cards:");
        queue<int> q;
        for (int i = 1; i <= n; i ++) q.push(i);
        while (q.size() != 1) {
            printf("%s%d", q.front() == 1 ? " " : ", ", q.front()); // 第一个退出无输出,
            q.pop();
            q.push(q.front()); q.pop(); // 头入队后删除
        }
        printf("\nRemaining card: %d\n", q.front());
    }
    return 0;
}
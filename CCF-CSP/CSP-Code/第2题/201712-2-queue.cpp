#include <bits/stdc++.h>
using namespace std;
int n, k, cnt = 0;
queue<int> q;
int main() {
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i ++) q.push(i);
    while(q.size() > 1) {
        int now = q.front(); // 当前报数的人的编号
        q.pop();
        cnt ++; // 报数
        if(cnt % k != 0 && cnt % 10 != k) q.push(now); // 没死继续加入队列
    }
    printf("%d\n", q.front());
    return 0;
}
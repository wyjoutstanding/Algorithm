#include<bits/stdc++.h>
using namespace std;
struct Job {
    int pos, pty; // 位置，优先级
}job;
int T, n, m;
int main() {
    scanf("%d", &T);
    while (T --) {
        scanf("%d %d", &n, &m);
        queue<Job> q;
        map<int, int> mp; // 每个优先级对应的人数
        for (int i = 0; i < n; i ++) {
            scanf("%d", &job.pty);
            job.pos = i; // 位置，0开始
            q.push(job);
            mp[job.pty] ++; // 计算该优先级人数
        }
        int num = 0;
        while (!q.empty()) {
            if (q.front().pty < mp.rbegin()->first) q.push(q.front()), q.pop(); // 有优先级高者，后移
            else if (q.front().pos == m) break; // 目标位置可输出
            else { // 非目标位置
                if (mp[q.front().pty] == 1) mp.erase(q.front().pty); // 维护mp
                else mp[q.front().pty] --;
                q.pop(); num ++;
            }
        }
        printf("%d\n", num+1);
    }
    return 0;
}
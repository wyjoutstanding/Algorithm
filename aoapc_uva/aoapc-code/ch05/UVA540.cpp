#include<bits/stdc++.h>
using namespace std;
int t, n, x, num=0;
string cmd;
int main() {
    while (cin >>t && t != 0) {
        map<int, int> team; // 编号x->组别编号
        for (int i = 0; i < t; i ++) { // 组别编号
            cin >>n;
            for (int j = 0; j < n; j ++) { // 每一组
                cin >>x;
                team[x] = i;
            }
        }
        printf("Scenario #%d\n", ++num); // 输出测试用例编号
        queue<int> q1, q2[1010]; // 总团队队列，组内部队列
        while (cin >>cmd && cmd[0] != 'S') {
            if (cmd[0] == 'E') { // 入队
                cin >>x;
                if (q2[team[x]].empty()) { // 组内不存在队员
                    q1.push(team[x]); // 进入总队列
                }
                q2[team[x]].push(x); // 组内不存在队员，加入总队列最后
            }
            else if (cmd[0] == 'D') { // 出队
                printf("%d\n", q2[q1.front()].front());
                q2[q1.front()].pop();
                if (q2[q1.front()].empty()) q1.pop(); // 维护总队列
            }
        }
        puts("");
    }
    return 0;
}
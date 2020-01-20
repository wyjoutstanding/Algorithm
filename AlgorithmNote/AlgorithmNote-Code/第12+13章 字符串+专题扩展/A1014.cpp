/*
 * @Author: wuyangjun
 * @Date: 2019-08-25 11:44:35
 * @LastEditTime: 2019-08-25 14:23:30
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxwin = 30, INF = 0x3fffffff;
queue<int> q[maxwin]; // 窗口队列
int lastTime[maxwin]; // 每个窗口处理完最后一个顾客的时刻
vector<int> a(1010), ans(1010); // 排队队列，结束时间结果（从1开始）
int beginTime = 8 * 60, endTime = 17 * 60; // 开始和结束时间，分钟为单位
int N, M, K, Q; // 窗口个数、窗口容量、排队人数、查询个数
int main() {
    scanf("%d %d %d %d", &N, &M, &K, &Q);
    for(int i = 1; i <= K; i ++) scanf("%d", &a[i]);
    fill(lastTime, lastTime + maxwin, beginTime); // 初始化每个窗口的当前时间
    // 模拟排队服务
    int i = 1; // 第一个人
    while(i <= K) { // K个人
        // 长度最小的窗口队列
        int MIN = INF, j;
        for(int w = 0; w < N; w ++) { // N个窗口
            if(q[w].size() < MIN) {
                MIN = q[w].size();
                j = w;
            }
        }
        // 有等待的人&&有空位
        if(MIN != M) {
            if(lastTime[j] >= endTime) { // 17:00之前没服务，超出下班时间
                ans[i] = INF; // 表示需要输出sorry
            }
            else {
                lastTime[j] += a[i]; // 计算a[i]的结束时间
                ans[i] = lastTime[j]; // 保存结束时间
            }
            q[j].push(ans[i]); // 无论是否为sorry，均需进队
            i ++; //下个人
        }
        else { // 无空位 
            int MIN = INF, idx;
            for(int w = 0; w < N; w ++) { // 找最早结束的窗口
                if(!q[w].empty() && q[w].front() < MIN) {
                    MIN = q[w].front();
                    idx = w;
                }
            }
            q[idx].pop(); // 弹出最早结束的人
        }
    }
    // Q条查询
    int query; // 查询
    for(int i = 0; i < Q; i ++) {
        scanf("%d", &query);
        if(ans[query] != INF) { // 有效查询
            printf("%02d:%02d\n", ans[query] / 60, ans[query] % 60);
        }
        else printf("Sorry\n");
    }
    return 0;
}
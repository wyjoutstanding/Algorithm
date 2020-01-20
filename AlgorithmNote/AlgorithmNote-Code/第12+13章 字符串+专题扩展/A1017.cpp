/*
 * @Author: wuyangjun
 * @Date: 2019-08-24 23:44:07
 * @LastEditTime: 2019-08-25 10:21:49
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct Customer { // 以秒做单位
    int arrTime; // 到达时刻
    int proTime; // 处理时间
    int startTime; // 服务开始时刻
    int endTime; // 服务结束时刻
    // 优先队列重载操作符<
    friend bool operator < (const Customer &a, const Customer &b) {
        return a.endTime > b.endTime; // 结束时刻小者在top
    }
}customer;
priority_queue<Customer> pq; // 优先队列模拟服务窗口
vector<Customer> a; // 模拟顾客排队队列
int beginTime = 8 * 3600, endTime = 17 * 3600; // 开始时间8:00，关闭时间17:00
int N, K; // 有效人数、窗口个数
int tot = 0; // 总等待时间
int main() {
    int n;
    scanf("%d %d", &n, &K);
    int hh, mm, ss, pm;
    for(int i = 0; i < n; i ++) {
        scanf("%d:%d:%d", &hh, &mm, &ss);
        customer.arrTime = 3600 * hh + 60 * mm + ss;
        scanf("%d", &pm);
        customer.proTime = 60 * pm;
        if(customer.arrTime <= endTime) a.push_back(customer); // 关门前来为有效
    }
    N = a.size(); // 有效人数
    // 按到达时间从小到达排序
    sort(a.begin(), a.end(), [](Customer& a, Customer& b) {return a.arrTime < b.arrTime;});
    // 模拟服务队列
    int nowTime = beginTime; // 初始化当前时间为开始营业时间
    int i = 0;
    while(i < N) { // N个顾客模拟
        // 当前服务批次：K个窗口已满或无人等待时结束 
        while(pq.size() < K && i < N) {
            a[i].startTime = max(a[i].arrTime, nowTime); // 开始服务时间
            a[i].endTime = a[i].startTime + a[i].proTime; // 结束服务时间
            tot += a[i].startTime - a[i].arrTime; // 累加等待时间
            pq.push(a[i]); // 进入服务优先队列
            i ++;
        }
        // 第一个结束的人
        if(!pq.empty()) {
            nowTime = pq.top().endTime; // 更新当前时间
            pq.pop();
        }
    }
    printf("%.1lf\n", (double)tot / (60 * N));
    return 0;
}
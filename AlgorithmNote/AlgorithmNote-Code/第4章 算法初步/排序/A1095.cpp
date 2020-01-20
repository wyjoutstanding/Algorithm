/*
 * @Author: wuyangjun
 * @Date: 2019-07-26 23:14:33
 * @LastEditTime: 2019-07-27 10:54:11
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct Car {
    string plateNum; //车牌号
    int time; //转换为秒
    int status; // in:1; out:-1
}car;
struct MaxTime {
    string plateNum;
    int ptime; //停留时间
}maxTime;
const int maxn = 24 * 60 * 60; //一天24小时
int res[maxn] = {0}; //存放每一秒的进出情况
vector<MaxTime> ansTime; //存放每辆车停放时间
bool cmp(Car a, Car b) {
    return a.time < b.time; //根据进出时间点升序排列
}
// 停车总时间
bool cmp2(MaxTime a, MaxTime b) {
    if(a.ptime != b.ptime) return a.ptime > b.ptime; / /总时间从小到大
    else return a.plateNum < b.plateNum; // 字典序升序
}
int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    map<string, vector<Car> > mp; //车牌 -> 进出记录
    int h, m, s;
    char plateNum[8], status[5];
    // N条记录，分类存储
    for(int i = 0; i < N; i++) {
        scanf("%s %d:%d:%d %s", plateNum, &h, &m, &s, status); //不用cin避免超时
        car.plateNum = plateNum; //转换为string类型
        car.time = h * 60 * 60 + m * 60 + s; //化为秒为单位
        if(strcmp(status, "in") == 0) car.status = 1; //in为1，on为-1
        else car.status = -1;
        mp[car.plateNum].push_back(car); //车牌 - > 记录
    }
    // 遍历所有车，找出每辆车的所有有效记录并计算总停留时间
    map<string, vector<Car> >::iterator mit;
    for(mit = mp.begin(); mit != mp.end(); mit++) {
        // cout <<"====:" <<mit->first <<endl;
        vector<Car> vit = mit->second;
        // 按时间升序排列
        sort(vit.begin(), vit.end(), cmp);
        // 寻找有效配对
        int ptime = 0;
        for(int i = 1; i < vit.size(); i++) {
            if(vit[i-1].status == 1 && vit[i].status == -1) {
                ptime += (vit[i].time - vit[i-1].time); //停留时间
                // 时间点的状态
                res[vit[i-1].time]++; //in多辆车同时进
                res[vit[i].time]--;  //out
                // i += 2; 多此一举！！！
                i ++; //这个可以有
            }
        }
        // 每辆车对应的总停留时间
        maxTime.plateNum = mit->first;
        maxTime.ptime = ptime;
        ansTime.push_back(maxTime);
    }
    // 计算每一秒的停留车辆
    for(int i = 1; i < maxn; i++) {
        res[i] += res[i-1];
    }
    // K个查询
    for(int i = 0; i < K; i++) {
        scanf("%d:%d:%d", &h, &m, &s);
        printf("%d\n", res[60 * 60 * h + 60 * m + s]);
    }
    // 输出最长停留时间的车牌号和停留时间
    sort(ansTime.begin(), ansTime.end(), cmp2);
    cout <<ansTime[0].plateNum; //至少一个
    int pt = ansTime[0].ptime;
    // 并列最长，字典升序输出
    for(int i = 1; i < ansTime.size(); i++) {
        if(pt == ansTime[i].ptime) cout <<" " <<ansTime[i].plateNum;
        else break;
    }
    printf(" %02d:%02d:%02d\n", pt / 3600, (pt / 60) % 60, pt % 60); //转换为标准格式，radix=60
    return 0;
}
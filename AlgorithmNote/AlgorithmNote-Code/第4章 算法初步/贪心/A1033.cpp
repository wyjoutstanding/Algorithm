/*
 * @Author: wuyangjun
 * @Date: 2019-07-29 23:48:35
 * @LastEditTime: 2019-07-30 10:27:49
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct Station {
    double price;
    double dist;
};
bool cmp(Station a, Station b) {
    return a.dist < b.dist;
}
int main() {
    double Cmax, D, Davg;
    int N;
    scanf("%lf %lf %lf %d", &Cmax, &D, &Davg, &N);
    Station stat[N + 1];
    // 初始化终点
    stat[N].dist = D;
    stat[N].price = 0;
    // 读入N个站点价格和坐标
    for(int i = 0; i < N; i++) {
        scanf("%lf %lf", &stat[i].price, &stat[i].dist);
    }
    // 按距离从小到大排序，类似X轴排列
    sort(stat, stat + N + 1, cmp);
    // 判断是否可到达终点
    bool isArrival = true;
    double maxDist = 0; 
    for(int i = 0; i < N; i++) {
        // 存在两个加油站距离大于加满油可达量程 || 起点无加油站
        if(stat[i+1].dist - stat[i].dist > Cmax * Davg || stat[0].dist != 0) {
            isArrival = false;
            if(stat[0].dist == 0) maxDist = stat[i].dist + Cmax * Davg; //最远距离
            else maxDist = 0.00;//起点无加油站
            break;
        }
    }
    // 不可达终点
    if(!isArrival) printf("The maximum travel distance = %.2lf", maxDist);
    else { //可达终点
        double minCount = 0, curGas = 0;
        for(int i = 0; i < N; ) {
            int k = i + 1;
            for(int j = k; j <= N && stat[j].dist - stat[i].dist <= Cmax * Davg; j++) {
                // 第一个比i便宜的车站
                if(stat[j].price < stat[i].price) {
                    k = j;
                    break;
                }
                // 无比i便宜车站,选其中最小
                if(stat[k].price > stat[j].price) k = j;
            }
            // 当前点价格低
            if(stat[i].price < stat[k].price) {
                minCount += stat[i].price * (Cmax - curGas); //加满油
                curGas = Cmax - (stat[k].dist - stat[i].dist) / Davg; //到达下一个点剩余的油
            }
            // 当前点价格高，加恰好到下个点的油
            else {
                minCount += stat[i].price * ((stat[k].dist - stat[i].dist) / Davg - curGas); //正好到k点
                curGas = 0; //到达下个点油量不剩
            }
            i = k;
        }
        printf("%.2lf", minCount);
    }
    return 0;
}
/*
 * @Author: wuyangjun
 * @Date: 2019-08-25 18:03:05
 * @LastEditTime: 2019-08-26 10:47:48
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3fffffff;
int beginTime = 8 * 3600, endTime = 21 * 3600;
struct Player { // 玩家，时间以秒为单位
    int arrTime; // 到达时刻
    int plaTime; // 打球时间
    int staTime; // 开始打球时刻
    int tag; // 1：VIP 0：ordinary
}player;
struct Table { // 球桌
    int endTime; // 结束时刻
    int tag; // 类型：1：VIP 0：ordinary
    int serNum; // 服务人数
    Table() {endTime = beginTime; tag = 0; serNum = 0;} // 默认构造初始化
}table[110];
vector<Player> a; // 排队队列
int N, K, M; // 人数，桌子数，vip桌子数， vip人数
// 分配桌子 pId:玩家下标 tId：桌子下标
void alloctTable(int pId, int tId) {
    a[pId].staTime = max(a[pId].arrTime, table[tId].endTime); // 取大者
    table[tId].endTime = a[pId].staTime + a[pId].plaTime; // 桌子结束时刻
    if(a[pId].staTime < endTime) table[tId].serNum ++; // 小于关门时刻，接受服务
}
int main() {
    scanf("%d", &N);
    int hh, mm, ss, pTime, tag;
    for(int i = 0; i < N; i ++) {
        scanf("%d:%d:%d", &hh, &mm, &ss);
        player.arrTime = 3600 * hh + 60 * mm + ss;
        scanf("%d %d", &pTime, &tag);
        player.plaTime = (pTime * 60 < 2 * 3600) ? pTime * 60 : 2 * 3600; // 最多两个小时
        player.tag = tag; // 标签
        player.staTime  = -1; // 表示未排到桌子
        a.push_back(player);
    }
    scanf("%d %d", &K, &M);
    int vip;
    for(int i = 0; i < M; i ++) {
        scanf("%d", &vip);
        table[vip].tag = 1; // vip号桌子，从1开始
    }
    sort(a.begin(), a.end(), [](Player& a, Player& b) {return a.arrTime < b.arrTime;}); // 别漏，按达到时间从小到达排序
    // 模拟
    int i = 0;
    while(i < N) { // N个人，从0开始
        if(a[i].staTime != -1) { // 跳过所有处理过的vip顾客
            i ++; // 已处理，跳过
            continue; // ！！！不写这句只能跳过一个
        }
        int firstMin = -1, MIN = INF, idx, firstVip = -1; // 第一个小于a[i].arrTime的桌子，桌子最小结束时间，桌子最小结束下标
        for(int t = 1; t <= K; t ++) { // K个桌子，从1开始
            if(MIN > table[t].endTime) { // 最早结束的桌子
                MIN = table[t].endTime;
                idx = t;
            }
            if(table[t].endTime <= a[i].arrTime) { // 所有小于等于到达时间
                if(firstMin == -1) firstMin = t; // 记录第一个
                if(firstVip == -1 && table[t].tag == 1) firstVip = t; // 第一个vip桌子
            }
        }
        if(firstMin != -1) { // 存在比a[i]到达时间早结束的桌子
            if(a[i].tag == 1 && firstVip != -1) { // vip用户&&存在对应的vip桌子
                alloctTable(i, firstVip);
            }
            else {
                alloctTable(i, firstMin);
            }
            i ++;
        }
        else { // 找到最早结束的桌子
            // 第一个未处理的vip顾客
            int vipIdx = -1; 
            for(int j = i; j < N; j ++) {
                if(a[j].tag == 1 && a[j].staTime == -1) {
                    vipIdx = j;
                    break;
                }
            }
            // 桌子是vip&&vip顾客存在&&其到达时间早于当前桌子的结束时间
            if(table[idx].tag == 1 && vipIdx != -1 && a[vipIdx].arrTime <= table[idx].endTime) {
                alloctTable(vipIdx, idx);
            }
            else {
                alloctTable(i, idx);
                i ++;
            }
        }
    }
    // 打印结果：按服务时刻从小到达排列
    sort(a.begin(), a.end(), [](const Player& a, const Player& b){return a.staTime < b.staTime;});
    for(auto p : a) {
        if(p.staTime < endTime) { // 关门前获得桌子
            printf("%02d:%02d:%02d ", p.arrTime / 3600, p.arrTime / 60 % 60, p.arrTime % 60);
            printf("%02d:%02d:%02d ", p.staTime / 3600, p.staTime / 60 % 60, p.staTime % 60);
            printf("%d\n", (int)round((double)(p.staTime - p.arrTime) / 60));
        }
    }
    for(int i = 1; i <= K; i ++) {
        printf("%d%s", table[i].serNum, i == K ? "\n" : " ");
    }
    return 0;
}
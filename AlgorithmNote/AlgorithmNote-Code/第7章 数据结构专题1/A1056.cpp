/*
 * @Author: wuyangjun
 * @Date: 2019-08-08 22:10:13
 * @LastEditTime: 2019-08-08 22:57:49
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct Mouse {
    int weight; //重量
    int rank; //排名
};
int main() {
    int Np, Ng;
    scanf("%d %d", &Np, &Ng);
    vector<Mouse> mouse(Np);
    for(int i = 0; i < Np; i ++) {
        scanf("%d", &mouse[i].weight);
    }
    int t;
    queue<int> q;
    for(int i = 0; i < Np; i ++) {
        scanf("%d", &t);
        q.push(t);
    }
    // 排名计算
    int group, rank; //组数、排名
    while(q.size() != 1) {
        queue<int> nextQueue;
        group = (int)ceil((float)q.size() / Ng); //组数
        rank = group + 1; //当前被淘汰的所有老鼠排名
        for(int i = 0; i < group; i ++) {
            int maxNum = -1, maxId; //找出每组的最大值下标
            for(int j = 0; !q.empty() && j < Ng; j ++) { //队列结束或Ng个结束
                int idx = q.front();
                if(maxNum < mouse[idx].weight) {
                    maxNum = mouse[idx].weight;
                    maxId = idx;
                }
                mouse[idx].rank = rank; //先全部设置为rank，最大值下轮会被更新
                q.pop();
           }
           nextQueue.push(maxId); //最大值下标入下一队
        }
        q = nextQueue;
    }
    mouse[q.front()].rank = 1; //第一名单独处理
    // 输出
    for(int i = 0; i < Np; i ++) {
        printf("%d%s", mouse[i].rank, i == Np - 1 ? "\n" : " ");
    }
    return 0;   
}
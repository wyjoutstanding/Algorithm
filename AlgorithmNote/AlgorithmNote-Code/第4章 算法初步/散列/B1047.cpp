/*
 * @Author: wuyangjun
 * @Date: 2019-07-28 11:24:40
 * @LastEditTime: 2019-07-28 11:29:52
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int N;
    scanf("%d", &N);
    int hashTable[1001] = {0};
    int team, id, score;
    // 统计每个队伍总分
    for(int i = 0; i < N; i++) {
        scanf("%d-%d %d", &team, &id, &score);
        hashTable[team] += score;
    }
    // 找出最高分队伍
    int winTeam = 1, winScore = hashTable[1];
    for(int i = 2; i < 1001; i++) {
        if(winScore < hashTable[i]) {
            winTeam = i;
            winScore = hashTable[i];
        }
    }
    printf("%d %d", winTeam, winScore);
    return 0;
}
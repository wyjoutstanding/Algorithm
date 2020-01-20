/*
 * @Author: wuyangjun
 * @Date: 2019-07-28 14:54:15
 * @LastEditTime: 2019-07-28 15:05:55
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct Info {
    int cnt; //出现次数
    int times;//最后一次出现的序号
}hashTable[10001];
int main() {
    int N;
    scanf("%d", &N);
    // 初始化
    for(int i = 0; i < 10001; i++) hashTable[i].cnt = 0; 
    int t;
    // 读入N个数并统计每个数的出现次数
    for(int i = 0; i < N; i++) {
        scanf("%d", &t);
        hashTable[t].cnt ++;
        hashTable[t].times = i + 1;
    }
    // 选出出现次数为1且最早出现的
    int times = 999999, ans = -1;
    for(int i = 1; i < 10001; i++) {
        if(hashTable[i].cnt == 1 && times > hashTable[i].times) {
            ans = i;
            times = hashTable[i].times;
        }
    }
    // 输出
    if(ans == -1) printf("None\n");
    else printf("%d\n", ans);
    return 0;
}
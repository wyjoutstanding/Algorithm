/*
 * @Author: wuyangjun
 * @Date: 2019-07-28 16:31:03
 * @LastEditTime: 2019-07-28 16:50:48
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int a[N];
    int hashTable[501] = {0};
    // 读入N个数并统计出现次数
    for(int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        hashTable[a[i]] ++;
    }
    // 遍历每一种可能
    vector<int> ans;
    for(int i = 0; i < N; i++) {
        // 排除两个相等的数，如7,7
        // if(M % a[i] == 0 && M / a[i] == 2) hashTable[a[i]] --;
        if(M - a[i] == a[i]) hashTable[a[i]] --; //更简单
        if(M >= a[i] && M - a[i] <= 500 && hashTable[M - a[i]] != 0) {
            hashTable[a[i]] --; //500特殊情况
            // 记录较小者
            if(M - a[i] < a[i]) ans.push_back(M - a[i]);
            else ans.push_back(a[i]);
        }
    }
    // 输出
    if(ans.empty()) printf("No Solution\n");
    else {
        sort(ans.begin(), ans.end());
        printf("%d %d\n", ans[0], M - ans[0]); //最小
    }
    return 0;
}
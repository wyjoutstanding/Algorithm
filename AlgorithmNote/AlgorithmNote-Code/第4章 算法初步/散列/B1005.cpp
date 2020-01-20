/*
 * @Author: wuyangjun
 * @Date: 2019-07-28 15:51:26
 * @LastEditTime: 2019-07-28 16:11:54
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int N, num;
    scanf("%d", &N);
    int a[N];
    bool hashTable[10000] = {0}; //计算过程会超过100
    // 存储每个输入的数并计算它覆盖的数，1直接排除，因为一定会覆盖
    for(int i = 0; i < N; i++) {
        scanf("%d", &num);
        a[i] = num;
        int t = num;
        // Callatz猜想
        while(t != 1) {
            if(t % 2 == 0) t /= 2;
            else t = (3*t + 1) / 2;
            hashTable[t] = true;
        }
    }
    // 存储结果
    vector<int> ans;
    for(int i = 0; i < N; i++) {
        if(!hashTable[a[i]]) ans.push_back(a[i]);
    }
    // 升序排列
    sort(ans.begin(), ans.end());
    // 降序输出
    for(int i = ans.size() - 1; i >= 0; i--) {
        if(i == ans.size() - 1) printf("%d", ans[i]);
        else printf(" %d", ans[i]);
    }
    return 0;
}
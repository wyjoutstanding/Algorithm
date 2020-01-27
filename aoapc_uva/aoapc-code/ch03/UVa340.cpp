#include<bits/stdc++.h>
using namespace std;
int n, cnta = 0, cntb = 0, num = 0;
vector<int> l1(1010), l2(1010), vl1(10), vl2(10);
int main() {
    while(scanf("%d", &n) == 1 && n != 0) {
        for (int i = 0; i < n; i ++) scanf("%d", &l1[i]); // 原答案序列
        printf("Game %d:\n", ++num);
        while (true) {
            for (int i = 0; i < n; i ++) scanf("%d", &l2[i]); // 猜测序列
            if (l2[0] == 0) break; // 读到0开头结束
            cnta = cntb = 0; // 初始化
            fill(vl1.begin(), vl1.end(), 0);
            fill(vl2.begin(), vl2.end(), 0);
            for (int i = 0; i < n; i ++) { // 第一次扫描
                if (l1[i] == l2[i]) cnta ++; // 统计同位置个数
                else { // 非同位置出现次数，哈希表实现
                    vl1[l1[i]] ++;
                    vl2[l2[i]] ++;
                }
            }
            for (int i = 0; i < 10; i ++) { // 非同位置取小者
                cntb += min(vl1[i], vl2[i]);
            }
            printf("    (%d,%d)\n", cnta, cntb); // 4个空格/Tab
        }
    }
    return 0;
}
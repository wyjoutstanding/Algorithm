#include<bits/stdc++.h>
using namespace std;
int n, k, m;
int main() {
    while(scanf("%d %d %d", &n, &k, &m) == 3 && n != 0) {
        vector<int> a(n);
        int ki=0, mi = n-1, cnt = 0, cntk=0, cntm=0;
        while(cnt < n) {
            while (true) { 
                if (a[ki] != -1) cntk ++; // 统计数过的人
                if (cntk == k) break;
                ki = (ki+1) % n; // 逆时针
            }
            while (true) {
                if (a[mi] != -1) cntm ++;
                if (cntm == m) break;
                mi = (mi+(n-1)) % n; // 顺时针，用加替代减
            }
            if (ki == mi) { // 指向同一个人
                a[ki] = -1;
                cnt ++; // 计算死亡人数，控制循环和末尾,
                printf("%3d%s", ki+1, cnt == n ? "" : ","); // 对齐宽度3！！！
            }
            else { // 指向不同人
                a[ki] = -1; a[mi] = -1;
                cnt += 2;
                printf("%3d%3d%s", ki+1, mi+1, cnt == n ? "" : ",");
            }
            cntk = cntm = 0;
        }
        printf("\n"); // 别漏
    }
    return 0;
}
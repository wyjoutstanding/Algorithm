#include<bits/stdc++.h>
using namespace std;
int n, m, a[100010], q, *p, num=0;
int main() {
    while (cin >>n >>m && (n != 0 && m != 0)) {
        for (int i = 0; i < n; i ++) cin >>a[i];
        sort(a, a+n); // 升序排列
        printf("CASE# %d:\n", ++num);
        while (m --) {
            cin >>q;
            p = lower_bound(a, a+n, q); // 找到>=q的第一个数
            if (p - a != n && *p == q) printf("%d found at %d\n", q, p-a+1); // 存在且为q
            else printf("%d not found\n", q); 
        }
    }
    return 0;
}
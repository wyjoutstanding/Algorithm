#include<bits/stdc++.h>
using namespace std;
int m, n, cubic, num = 0;
int main() {
    while (cin >>m >>n && m != 0) {
        vector<int> a(m*n+2); a[m*n+1] = 0x7ffff; // 太大会溢出
        for (int i = 1; i <= m*n; i ++) cin >>a[i];
        cin >>cubic; // 体积
        sort(a.begin()+1, a.end()); // 从小到大排序
        for (int i = 2; i <= m*n; i ++) a[i] += a[i-1]; // a[i]表示前i个长度和
        double ans1, ans2;
        for (int i = 1; i <= m*n; i ++) {
            if (((i+1)*(a[i+1]-a[i]) - a[i+1])*100 >= cubic) { // 必须用乘法，除法会产生误差
                ans1 = (double)(cubic + a[i]*100) / (i*100); // 高度，先乘后除
                ans2 = (double)i / (m*n); // 百分比
                break;
            }
        }
        printf("Region %d\nWater level is %.2lf meters.\n", ++num, round(ans1*100)/100);
        printf("%.2lf percent of the region is under water.\n\n", round(ans2*10000)/100);
    }
    return 0;
}
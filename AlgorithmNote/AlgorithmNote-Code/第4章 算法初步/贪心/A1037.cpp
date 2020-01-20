/*
 * @Author: wuyangjun
 * @Date: 2019-07-30 15:13:02
 * @LastEditTime: 2019-07-30 15:51:42
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
bool cmp(LL a, LL b) {
    if(a < 0 && b < 0) return a < b; //负数升序
    else return a > b; //整数，正负数降序
}
int main() {
    int n, m;
    // 输入
    scanf("%d", &n);
    vector<LL> coupon(n);
    for(int i = 0; i < n; i++) scanf("%lld", &coupon[i]);
    scanf("%d", &m);
    vector<LL> product(m);
    for(int i = 0; i < m; i++) scanf("%lld", &product[i]);
    // 排序
    sort(coupon.begin(), coupon.end(), cmp);
    sort(product.begin(), product.end(), cmp);
    // for(int i = 0; i < n; i++) printf("%d ", coupon[i]);
    // printf("\n");
    // for(int i = 0; i < m; i++) printf("%d ", product[i]);
    // 计算最大值
    LL sum = 0;
    int i = 0, j = 0;
    while(i < n && j < m) {
        // 同号
        if((coupon[i] > 0 && product[j] > 0) || (coupon[i] < 0 && product[j] < 0)) {
            sum += coupon[i] * product[j];
            i ++;
            j ++;
        }
        // 异号，移动正数
        else if(coupon[i] >= 0) i ++; //处理0
        else j ++;
    }
    printf("%lld\n", sum);
    return 0; 
}
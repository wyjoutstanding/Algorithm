/*
 * @Author: wuyangjun
 * @Date: 2019-08-03 22:16:44
 * @LastEditTime: 2019-08-03 22:27:03
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<int> a(n);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    sort(a.begin(), a.end());
    bool flag = false;
    int i = 0, j = n - 1;
    while(i < j) {
        if(a[i] + a[j] == m) {
            flag = true;
            printf("%d %d\n", a[i], a[j]);
            break;
        }
        else if(a[i] + a[j] < m) i++;
        else j--;
    }
    if(!flag) printf("No Solution\n");
    return 0;
}
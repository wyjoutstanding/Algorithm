/*
 * @Author: wuyangjun
 * @Date: 2019-09-13 13:25:19
 * @LastEditTime: 2019-09-13 13:27:51
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    scanf("%d", &n);
    n = n / 10;
    printf("%d\n", (n / 5) * 7 + ((n % 5) / 3) * 4 + (n % 5 % 3));
    return 0;
}
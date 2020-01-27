#include<bits/stdc++.h>
using namespace std;
int T, n, len, sum = 0;
string s;
int main() {
    scanf("%d", &T);
    for (int i = 0; i < T; i ++) {
        scanf("%d", &n);
        len = to_string(n).size(); // n的位数，数位之和最大为9*len(n)
        for (int j = n - len*9; j <= n; j ++) { // 确定枚举范围[n-len*9, n]
            sum = j;
            s = to_string(j);
            for (auto ch : s) sum += (ch - '0'); // 数位之和累加
            if (sum == n) {
                printf("%d\n", j);
                break;
            }
            if (j == n) printf("0\n");
        }
    }
    return 0;
}
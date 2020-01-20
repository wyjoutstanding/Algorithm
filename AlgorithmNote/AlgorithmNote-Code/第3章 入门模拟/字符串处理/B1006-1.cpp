#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >>n;
    int radix[3]; //存放个十百位数字
    for(int i = 0; i < 3; i++) {    //计算个十百位数字
        radix[i] = n % 10;
        n /= 10;
    }
    // 输出：输出个数和相应位数上的数字一样
    for(int i = 2; i >= 0; i--) {
        for(int j = 0; j < radix[i]; j++) {
            if(i == 2) cout <<'B';
            else if(i == 1) cout <<'S';
            else cout <<j + 1;
        }
    }
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
typedef long long LL; // 避免移位溢出
int main() {
    LL n, Sp, Sq;
    while (cin >>n >>Sp >>Sq) {
        LL K=LONG_LONG_MAX, A, B;
        for (int i = 0; i < 32; i ++) { // A
            for (int j = 0; j < 32; j ++) { // B
                if (((Sp + (Sp << i)) >= (Sq << j)) && (K > ((Sp*(n-1)+((Sp*(n-1))<<i))>>j)+Sq)) { // 公差大于Sq且k更大
                    K = ((Sp*(n-1)+((Sp*(n-1))<<i))>>j)+Sq; // 更新KAB
                    A = i; B = j;
                }
            }
        }
        printf("%lld %lld %lld\n", K, A, B); // 第一个即符合条件
    }
    return 0;
}
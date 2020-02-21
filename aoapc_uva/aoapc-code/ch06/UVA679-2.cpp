#include<bits/stdc++.h>
using namespace std;
int T, D, I;
int main() {
    scanf("%d", &T);
    while (T --) {
        scanf("%d %d", &D, &I);
        long long ans=1;
        for (int i = 1; i <= D-1; i ++) { // 模拟I个小球掉落
            if (I % 2 == 1) { // I表示第几个经过当前点
                I = (I+1)/2; // 更新
                ans *= 2;
            }
            else { // 偶数走右子树
                I /= 2;
                ans = ans*2 + 1;
            }
        }
        printf("%lld\n", ans);
    }
    scanf("%d", &T); // 最后的-1，多余的输入！
    return 0;
}
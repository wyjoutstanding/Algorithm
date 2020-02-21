#include<bits/stdc++.h>
using namespace std;
#define MAX(D) (1<<D)
int T, D, I;
bool tag[(1<<20)+1]={0}; // 标记数组
int main() {
    scanf("%d", &T);
    while (T --) {
        scanf("%d %d", &D, &I);
        fill(tag, tag+(1<<D)+1, 0); // 初始化false
        long long ans;
        for (int i = 1; i <= I; i ++) { // 模拟I个小球掉落
            ans = 1; //printf("I:%d ", i);
            while (true) {
                // printf("ans: %lld ", ans);
                if (ans*2 < MAX(D) && !tag[ans]) tag[ans] = !tag[ans], ans *= 2; // 走左边
                else if (ans*2+1 < MAX(D) && tag[ans]) tag[ans] = !tag[ans], ans = ans*2+1; // 走右边
                else break; // 否则结束
            }
        }
        printf("%lld\n", ans);
    }
    scanf("%d", &T); // 最后的-1，多余的输入！
    return 0;
}
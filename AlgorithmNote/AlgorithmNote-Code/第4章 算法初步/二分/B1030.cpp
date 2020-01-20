/*
 * @Author: wuyangjun
 * @Date: 2019-07-31 09:46:22
 * @LastEditTime: 2019-07-31 09:58:06
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int N, p;
    scanf("%d %d", &N, &p);
    vector<int> res(N);
    for(int i = 0; i < N; i++) {
        scanf("%d", &res[i]);
    }
    sort(res.begin(), res.end());
    int left = 0, right = 0;
    for(int i = 0; i < N; i++) {
        if(res[N-1] <= p * res[i]) {
            left = N - i;
            break;
        }
    }
    for(int i = N - 1; i >= 0; i--) {
        if(res[i] <= p * res[0]) {
            right = i + 1;
            break;
        } 
    }
    printf("%d\n", max(left, right));
    return 0;
}
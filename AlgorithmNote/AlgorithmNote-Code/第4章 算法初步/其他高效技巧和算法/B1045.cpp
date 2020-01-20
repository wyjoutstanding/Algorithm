/*
 * @Author: wuyangjun
 * @Date: 2019-08-04 00:20:15
 * @LastEditTime: 2019-08-04 07:21:19
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100005, inf = 0x3fffffff;
int leftMax[maxn], rightMin[maxn];
int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    // 找出每个元素左侧最大值
    leftMax[0] = -1;
    for(int i = 1; i < n; i++) {
        if(leftMax[i-1] < a[i-1]) leftMax[i] = a[i-1];
        else leftMax[i] = leftMax[i-1];
    }
    // 找出每个元素右侧最小值
    rightMin[n-1] = inf;
    for(int i = n - 2; i >= 0; i--) {
        if(rightMin[i+1] > a[i+1]) rightMin[i] = a[i+1];
        else rightMin[i] = rightMin[i+1];
    }
    // 存储符合条件的主元
    vector<int> ans;
    for(int i = 0; i < n; i++) {
        if(a[i] > leftMax[i] && a[i] < rightMin[i]) ans.push_back(a[i]);
    }
    // 输出
    printf("%d\n", ans.size());
    sort(ans.begin(), ans.end());
    for(int i = 0; i < ans.size(); i++) {
        if(i == 0) printf("%d", ans[i]);
        else printf(" %d", ans[i]);
    }
    printf("\n"); //不能省略，否则报格式错
    return 0;
}
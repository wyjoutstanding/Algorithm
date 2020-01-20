/*
 * @Author: wuyangjun
 * @Date: 2019-08-02 23:46:40
 * @LastEditTime: 2019-08-02 23:58:40
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100001;
int a[maxn];
int binarySearch(int left, int right, int val) {
    int mid;
    while(left <= right) {
        mid = left + (right - left) / 2;
        if(a[mid] == val) return mid;
        else if(a[mid] < val) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    for(int i = 0; i < N; i++) scanf("%d", &a[i]);
    sort(a, a + N);
    vector<int> ans;
    for(int i = 0; i < N; i++) {
        int ret = binarySearch(0, N-1, M - a[i]);
        if(ret != -1 && ret != i) {
            ans.push_back(min(a[i], M - a[i]));
        }
    }
    if(ans.empty()) printf("No Solution\n");
    else {
        sort(ans.begin(), ans.end());
        printf("%d %d\n", ans[0], M - ans[0]);
    }
    return 0;
}
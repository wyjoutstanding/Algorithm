#include<bits/stdc++.h>
using namespace std;
int main() {
    int n, ans, cnt;
    string s;
    scanf("%d", &n);
    while(n --) {
        cin >>s;
        ans = cnt = 0;
        for (auto ch : s) {
            if (ch == 'X') cnt = 0;
            else {
                cnt ++;
                ans += cnt;
            }
        }
        printf("%d\n", ans);
        
    }
    return 0;
}
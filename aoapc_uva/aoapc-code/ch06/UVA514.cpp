#include<bits/stdc++.h>
using namespace std;
int n, a[1010];
int main() {
    while (cin >>n && n != 0) {
        while (cin >>a[1] && a[1] != 0) {
            for (int i = 2; i <= n; i ++) scanf("%d", &a[i]); // 输入
            stack<int> stk; // 模拟栈
            int j = 1; // 判断联系满足的个数
            for (int i = 1; i <= n; i ++) { // 1-n依次压入
                stk.push(i); // 压栈
                while (!stk.empty() && stk.top() == a[j]) stk.pop(), j ++; // 当栈非空且栈顶为a[j]时，出栈
            }
            printf("%s\n", stk.empty() && j == n+1 ? "Yes" : "No"); // 栈空表示合法
        }
        puts(""); // 两组间空行
    }
    return 0;
}
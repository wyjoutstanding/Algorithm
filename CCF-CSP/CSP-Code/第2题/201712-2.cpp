#include <bits/stdc++.h>
using namespace std;
int n, k; 
set<int> a; // 存储人0~n-1
int main() {
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i ++) a.insert(i); // 标号0~n-1的参与者
    int i = 0, cnt = 0; // 当前的人的编号、报数的值
    while(true) {
        if(a.size() == 1) { // 最后一个人直接输出，结束
            printf("%d\n", *a.begin() + 1);
            break;
        }
        if(a.count(i) != 0) { // 没死
            cnt ++; // 报数 
            if(cnt % k == 0 || cnt % 10 == k) a.erase(i); // 满足条件，杀死
        }
        i = (i + 1) % n; // 更新下一个人
    }
    return 0;
}
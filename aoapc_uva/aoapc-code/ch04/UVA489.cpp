#include<bits/stdc++.h>
using namespace std;
set<char> ans, hit; // 答案序列，命中序列
string a,b;
int id, cnt; // round，错误次数
int main() {
    while (scanf("%d", &id) && id != -1) {
        cin >>a >>b;
        ans.clear(); hit.clear(); cnt = 0; // 初始化
        for (auto ch : a) ans.insert(ch);
        for (auto ch : b) { // 遍历猜测序列
            if (cnt == 7 || ans.size() == hit.size()) break; // 错误7次|完全猜中
            if (ans.find(ch) != ans.end()) hit.insert(ch); // 猜中
            else cnt ++; // 未猜中
        }
        printf("Round %d\n", id);
        if (cnt == 7) printf("You lose.\n");
        else if (ans.size() == hit.size()) printf("You win.\n");
        else printf("You chickened out.\n");
    }
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
map<char, int> mp{{'C',0}, {'H',1}, {'O',2}, {'N',3}}; // 便于循环处理
double mass[4] = {12.01, 1.008, 16.00, 14.01}, ans = 0;
int n, num[4] = {0}; // 统计个数
string str, s;
char pre; // 记录有明确数量的前置符号
int main() {
    scanf("%d", &n);
    while(n --) {
        cin >>str;
        fill(num, num+4, 0); // 初始化
        pre = str[0]; // 记录前一个元素
        int i = 0;
        while(i < str.size()) {
            s.clear();
            while (i < str.size() && isdigit(str[i])) s += str[i++]; // 计算数值
            if (!s.empty()) {
                num[mp[pre]] += stoi(s);
                i --; // 数值计算多后移一位
            }
            else {
                if (i + 1 == str.size() || !isdigit(str[i+1])) { // 符号后无明确数值
                    num[mp[str[i]]] += 1;
                }
                else pre = str[i];
            }
            i ++; // 移动标签
        }
        ans = 0;
        for (int i = 0; i < 4; i ++) { // 计算结果
            ans += (double)num[i] * mass[i];
        }
        printf("%.3lf\n", ans);
    }
    return 0;
}
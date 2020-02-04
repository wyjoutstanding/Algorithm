#include<bits/stdc++.h>
using namespace std;
int r, c, op, cnt = 0;
string s;
int main() {
    while (scanf("%d %d", &r, &c) == 2 && (r != 0 && c != 0)) {
        scanf("%d", &op); // 操作个数
        printf("%sSpreadsheet #%d\n", cnt != 1 ? "\n":"", ++cnt); // ++优先级高，控制空行
        vector<pair<string,vector<int> > > cmd; // 存储命令和对应的行列集合
        while (op --) { // 存储输入命令
            cin >>s;
            cmd.push_back({s, vector<int>()}); // 初始化
            int n, t;
            if (s == "EX") n = 4;
            else scanf("%d", &n);
            while (n --) {
                scanf("%d", &t);
                cmd.back().second.push_back(t);
            }
        }
        int n, x, y, ansX, ansY;
        scanf("%d", &n);
        while (n --) { // n个查询
            scanf("%d %d", &x, &y);
            ansX = x; ansY = y; // 最终结果初始化
            for (auto p : cmd) { // 遍历所有命令
                if (p.first != "EX") { // 插入/删除
                    sort(p.second.begin(), p.second.end(), [](int& a, int &b) {return a > b;}); // 降序排列
                    for (auto i : p.second) { // 遍历删除或插入的行/列号（从大到小，否则前面会影响后面）
                        if (p.first == "DR") { // 删除行
                            if (i == ansX) ansX = -1; // -1标记删除
                            else if (ansX > i) ansX --; // 行号大于i才改变
                        }
                        else if (p.first == "DC") { // 删除列，与删除行类似
                            if (i == ansY) ansY = -1;
                            else if (ansY > i) ansY --;
                        }
                        else if (p.first == "IR" && ansX >= i) ansX ++; // 插入行，>=i就会改变
                        else if (p.first == "IC" && ansY >= i) ansY ++; // 插入列，>=i就会改变
                        if (ansX == -1 || ansY == -1) break; // 发现删除，直接结束
                    }
                }
                else { // 交换单元格
                    if (ansX == p.second[0] && ansY == p.second[1]) ansX = p.second[2], ansY = p.second[3];
                    else if (ansX == p.second[2] && ansY == p.second[3]) ansX = p.second[0], ansY = p.second[1];
                }
            }
            if (ansX == -1 || ansY == -1) printf("Cell data in (%d,%d) GONE\n", x, y);
            else printf("Cell data in (%d,%d) moved to (%d,%d)\n", x, y, ansX, ansY);
        }
    }
    return 0;
}
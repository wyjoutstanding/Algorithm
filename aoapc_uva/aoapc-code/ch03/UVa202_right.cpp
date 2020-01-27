#include<bits/stdc++.h>
using namespace std;
int a, b, begIdx=-1;
string si, sd;
int main() {
    while(cin >>a >>b) {
        vector<pair<int,int>> d;
        si = to_string(a / b);
        printf("%d/%d = %s.", a, b, si.c_str());
        a = (a % b)*10; // 第一个必须舍弃
        begIdx = -1;
        while(begIdx == -1) { // 除法模拟
            d.push_back({a, a/b});
            a = (a%b)*10;
            for (int i = 0; i < d.size(); i ++) {
                if (d[i].first == a) {
                    begIdx = i; // 循环节开始
                    break;
                }
            }
        }
        for (int i = 0; i < begIdx; i ++) printf("%d", d[i].second);
        printf("(");
        for (int i = begIdx; i < ((d.size() > 50) ? 50 : d.size()); i ++) printf("%d", d[i].second);
        printf("%s", d.size() > 50 ? "...)" : ")");
        printf("\n   %d = number of digits in repeating cycle\n\n", d.size()-begIdx); // 诡异输出，每个输出后均两个换行
    }
    return 0;
}
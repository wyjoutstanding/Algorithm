#include<bits/stdc++.h>
using namespace std;
map<set<int>, int> box;
map<int, int> edge;
int a, b;
int main() {
    while(cin >>a >> b) {
        bool isBox = false, flag = true, flag2 = true;
        box.clear(); edge.clear();
        for (int i = 0; i < 6; i ++) {
            if (i != 0) cin >>a >>b;
            box[{a,b}] ++;
            edge[a] ++;
            edge[b] ++;
        }
        for (auto p : box) { // 每个面出现次数为2,4,6
            if (p.second % 2 != 0) {
                flag = false; break;
            }
        }    
        for (auto p : edge) { // 每条边出现次数为4,8,12
            if (p.second % 4 != 0) {
                flag2 = false; break;
            }
        }
        if (flag && flag2) isBox = true; // 满足两个条件可构造长方体
        printf("%s\n", isBox ? "POSSIBLE" : "IMPOSSIBLE");
    }
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
int n, m;
string s, st;
map<string, int> idmp; // 字符串->id
int getId(string s) { // 获取字符串id，若已存在，直接返回，否则分配id
    if (idmp.find(s) == idmp.end()) idmp.insert({s, idmp.size()}); // 不存在
    return idmp[s];
}
int main() {
    while (cin >>n >>m) {
        getchar(); vector<int> table[n+1]; idmp.clear(); // 初始化！！！
        for (int i = 0; i < n; i ++) {
            getline(cin, s); stringstream input(s);
            while (getline(input, st, ',')) table[i].push_back(getId(st));
        }
        bool isPNF = true; // 标记是否为PNF
        for (int i = 0; i < m-1 && isPNF; i ++) { // 遍历任意两列
            for (int j = i+1; j < m && isPNF; j ++) {
                map<pair<int,int>, int> pos; // 两列对应字符串标号->行
                for (int k = 0; k < n && isPNF; k ++) { // 每一行
                    if (pos.find({table[k][i],table[k][j]}) == pos.end()) {
                        pos[{table[k][i],table[k][j]}] = k;
                    }
                    else {
                        printf("NO\n%d %d\n%d %d\n", pos[{table[k][i],table[k][j]}]+1, k+1, i+1, j+1);
                        isPNF = false;
                    }
                }
            }
        }
        if (isPNF) printf("YES\n");
    }
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
int T;
void dfs(map<int,vector<int> >&tree, vector<char>& dict, int root=0) { // 根据多叉树递归打印
    if (dict.size() > root) printf("%c", dict[root]);
    if (!tree[root].empty()) {
        printf("(");
        for (auto t : tree[root]) dfs(tree, dict, t);
        printf(")");
    }
    else printf("()");
}
int main() {
    scanf("%d", &T); getchar(); // 吸收多余换行
    string s[4]; // 4行：根，|,-,孩子
    while (T --) {
        map<int,vector<int> > tree; // 多叉树
        vector<char> dict; // 结点字符字典（给每个字符进行编号，处理重复字符）
        map<int,int> id; // 每个位置->对应字符的id
        getline(cin, s[0]);
        if (s[0][0] == '#') {printf("()\n"); continue;} // 空树
        auto p = find_if(s[0].begin(), s[0].end(), [](char& ch){return ch != ' ';});
        id[p - s[0].begin()] = dict.size(); dict.push_back(*p);
        while (getline(cin, s[1]) && s[1][0] != '#') {
            getline(cin, s[2]); getline(cin, s[3]); 
            vector<int> a[3]; // a[1]表示|所在位置，a[2]表示每段-的起止位置
            for (int i=0; i < s[1].size(); i ++) if (s[1][i] == '|') a[1].push_back(i); // |的位置
            int flag=0;
            for (int i=0; i < s[2].size(); i ++) { // -分割区间：[起始,结束)
                if (flag == 0 && s[2][i] == '-') a[2].push_back(i), flag=1; // 起点
                else if (flag == 1 && s[2][i] == ' ') a[2].push_back(i), flag=0; // 终点
            }
            if (a[2].size() % 2 != 0) a[2].push_back(s[2].size()); // 最后一段-
            map<int,int> tid; // 临时存储
            for (int i=0; i < s[3].size(); i ++) { // 孩子处理
                if (s[3][i] != ' ') {
                    for (int j=0; j < a[2].size(); j += 2) // 查询在哪一段
                        if (a[2][j] <= i && i < a[2][j+1]) {
                            tid[i] = dict.size(); dict.push_back(s[3][i]);
                            for (int k=0; k < a[1].size(); k ++) { // 查询符合区间的父结点
                                if (a[2][j] <= a[1][k] && a[1][k] < a[2][j+1]) tree[id[a[1][k]]].push_back(dict.size()-1);
                            }
                        }
                }
            }
            id = tid; s[0] = s[3]; // 更新
        }
        putchar('('); dfs(tree, dict, 0); puts(")");
    }
    return 0;
}
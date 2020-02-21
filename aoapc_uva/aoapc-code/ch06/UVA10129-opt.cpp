#include<bits/stdc++.h>
using namespace std;
int T, n;
int findFather(int a, vector<int>& father) { // 并查集找父结点
    return father[a] = (father[a] == a) ? a : findFather(father[a], father);
}
int main() {
    scanf("%d", &T);
    string s;
    while (T --) {
        scanf("%d", &n);
        vector<int> degree(26,0), father(26); // 26个字母对应的入度表，父结点
        for (int i = 0; i < 26; i ++) father[i] = i; // 初始化并查集父结点
        set<char> _set; // 存储出现的字符个数（去重）
        for (int i = 0; i < n; i ++) {
            cin >>s; 
            _set.insert(s[0]); _set.insert(s.back()); // 头尾插入集合
            degree[s[0]-'a'] --; degree[s.back()-'a'] ++; // 出度和入度计算
            father[s[0]-'a'] = findFather(s.back()-'a', father); // 并查集计算
        }
        int even=0, sp=-1, ep=-1; // 偶度顶点
        for (int i=0; i < 26; i ++) {
            if (degree[i] == 0) even ++;
            else if (degree[i] == 1) sp = 1; // 奇度顶点，且出度-入度=1
            else if (degree[i] == -1) ep = 1; // 奇度顶点，且出度-入度=-1
        }
        for (int i=0; i < 26; i ++) father[i] = findFather(i, father); // 最后来一遍，防止有些顶点没被更新
        int num=0;
        for (int i=0; i < 26; i ++) if (father[i] == i) num ++; // 不同的集合个数
        if ((even == 26-2 && (sp==1&&ep==1) || even == 26) && num == 1+26-_set.size()) printf("Ordering is possible.\n");
        else printf("The door cannot be opened.\n");
    }
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
int T, n;
vector<string> words;
int findFather(int a, vector<int>& father) {
    return father[a] = (father[a] == a) ? a : findFather(father[a], father);
    // if (father[a] == a) return a;
    // else father[b] = findFather(a, father[a], father);
}
int main() {
    scanf("%d", &T);
    string s;
    while (T --) {
        scanf("%d", &n);
        words.clear(); map<char,set<int> > mp;
        for (int i = 0; i < n; i ++) {
            cin >>s; words.push_back(s); mp[s[0]].insert(i);
        }
        vector<int> degree(n,0);
        vector<set<int> > adj(n); // 邻接表存储图
        for (int i=0; i < n; i ++) { // 建立图
            set<int> _set = mp[words[i].back()];
            if (_set.find(i) != _set.end()) _set.erase(i); // 删除自身
            adj[i] = _set;
            degree[i] += _set.size(); // 出度
            for (int p : _set) degree[p] --; // 入度-1
        }
        int even=0, sp=-1, ep=-1;
        for (int i=0; i < n; i ++) {
            // printf("degree: %d \n", degree[i]);
            if (degree[i] == 0) even ++;
            else if (degree[i] < 0) sp = degree[i];
            else ep = degree[i];
        }
        vector<int> father(n);
        for (int i = 0; i < n; i ++) father[i] = i; // 初始化
        for (int i=0; i < n; i ++) {
            for (auto p : adj[i]) father[p] = findFather(i, father);
        }
        for (int i=0; i < n; i ++) findFather(i, father); // 最后来一遍
        int num=0;
        for (int i=0; i < n; i ++) if (father[i] == i) num ++;
        // for (int i = 0; i < n; i ++) cout <<" " <<father[i]; cout <<endl;
        // printf("----%d %d %d %d\n", even, sp, ep, num);
        // if (even == n-2 && sp+ep==0 && num == 1) printf("Ordering is possible.\n");
        if (even == n-2 && sp+ep==0 && num == 1 || n == 1) printf("Ordering is possible.\n");
        else printf("The door cannot be opened.\n");
        // for (int i=0; i < n; i ++) {
        //     printf("--%d %s\n", i, words[i].c_str());
        //     for (auto p : adj[i]) {
        //         printf("----%d %s\n", p, words[p].c_str());
        //     }
        // }
    }
    return 0;
}
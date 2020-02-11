#include<bits/stdc++.h>
using namespace std;
int T, n, x, y;
int main() {
    cin >>T;
    while (T --) {
        cin >>n;
        map<int, vector<int> > mp; // y->x坐标
        for (int i = 0; i < n; i ++) {
            scanf("%d %d", &x, &y);
            mp[y].push_back(x);
        }
        set<int> _set; // 最终大小为1表示左右对称
        for (auto p : mp) {
            sort(p.second.begin(), p.second.end()); // x坐标升序排列
            int right = (p.second.size() % 2 == 0) ? p.second.size()/2 : p.second.size()/2+1;
            for (int i = 0; i < right; i ++) 
                _set.insert(p.second[i]+p.second[p.second.size()-i-1]); // 两侧点之和
        }
        printf("%s\n", _set.size() == 1 ? "YES" : "NO");
    }    
    return 0;
}
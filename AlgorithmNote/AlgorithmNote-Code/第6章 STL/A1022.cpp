/*
 * @Author: wuyangjun
 * @Date: 2019-08-08 14:28:31
 * @LastEditTime: 2019-08-08 14:52:44
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    scanf("%d", &n);
    getchar();
    // 1~5分别存放书名，作者，关键词，出版社，年份 -> 编号
    map<string, vector<string> > mp[6];
    string id, s;
    for(int i = 0; i < n; i ++) {
        getline(cin, id); //编号
        for(int j = 1; j <= 5; j ++) {
            getline(cin, s);
            if(j != 3) {
                mp[j][s].push_back(id);
            }
            else { //key words拆分
                string tmp;
                stringstream input(s);
                while(input >>tmp) {
                    mp[j][tmp].push_back(id);
                }
            }
        }
    }
    // 对每个键值对应的id按字典序升序排列
    for(int i = 1; i < 6; i ++) {
        for(auto& p : mp[i]) {
            sort(p.second.begin(), p.second.end());
        }
    }
    int m, idx;
    scanf("%d", &m);
    string query;
    // 查询
    for(int i = 0; i < m; i ++) {
        scanf("%d: ", &idx);
        getline(cin, query);
        printf("%d: ", idx);
        cout <<query <<endl;
        if(mp[idx].count(query) == 0) {
            printf("Not Found\n");
        }
        else {
            for(auto p : mp[idx][query]) {
                cout <<p <<endl;
            }
        }
    }

    return 0;
}
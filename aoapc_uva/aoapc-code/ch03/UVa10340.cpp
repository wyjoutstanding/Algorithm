#include<bits/stdc++.h>
using namespace std;
map<char, vector<int>> mp; // 存储每个字符所在位置
string s,t;
int main() {
    while(cin>>s && cin >>t) {
        mp.clear(); // 初始化
        int dp[s.size()+1] = {1,0}; // dp计数
        for (int i = 0; i < s.size(); i ++) { // 统计每个字符所在位置，从1开始算
            if (mp.find(s[i]) == mp.end()) { // 未存在
                mp.insert({s[i], {i+1}});
            }
            else mp[s[i]].push_back(i+1); // 已存在，存入
        }
        for (int i = 0; i < t.size(); i++) { // 遍历字符串t
            if (mp.find(t[i]) != mp.end()) { // 字符出现在s中
                for (int k = mp[t[i]].size() - 1; k >= 0; k --) { // 逆序遍历字符所在s中位置，滚动数组优化
                    dp[mp[t[i]][k]] += dp[mp[t[i]][k]-1]; // dp[j]=dp[j]+dp[j-1]
                }
            }
        }
        printf("%s\n", dp[s.size()] == 0 ? "No" : "Yes"); // 最后一个为总序列个数
    }
    return 0;
}
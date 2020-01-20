#include <bits/stdc++.h>
using namespace std;
int main() {
    string s[1000], res;
    int N;
    cin >>N;
    getchar(); //读取一行必须先用它吸收换行
    for(int i = 0; i < N; i++) {
        getline(cin, s[i]);
    }
    res = s[0];//初始化为第一句
    // 两两取最长公共后缀
    for(int i = 1; i < N; i++) {
        int index = -1, lres = 0;//公共的后缀下标，长度
        int len = min(res.size(), s[i].size());
        for(int j = 0; j < len; j++) {
            if(res[res.size() - j - 1] == s[i][s[i].size() - j - 1]) {
                index = res.size() - j - 1;
                lres ++;
            }
            else break;//一个不满足，立刻退出
        }
        if(lres == 0) {//0个相等，必定无公共后缀
            cout <<"nai";
            return 0;
        }
        else {
            res = res.substr(index, lres);
        }
    }
    cout <<res;
    return 0;
}
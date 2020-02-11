#include<bits/stdc++.h>
using namespace std;
map<string, unordered_set<string> > mp; // 地址->人名
string s, addr, name, st;
int n;
int main() {
    while (cin >>s) {
        do {
            cin >>addr >>n;
            for (int i = 0; i < n; i ++) cin >>name, mp[addr].insert(name);
        } while (cin >>s && s[0] != '*');
        getchar(); // 吸收多余换行
        while (getline(cin, s) && s[0] != '*') {
            map<string, vector<string> > mp2; // 地址->人名
            vector<string> addr; // 按输入顺序存储地址，便于输出
            int cnt = 0;
            string sendaddr, sendname, saddr, sname;
            stringstream input(s);
            while (input >>st) {
                cnt ++;
                int i = st.find('@'); // 找到@位置下标
                saddr = st.substr(i+1); sname = st.substr(0,i); // 分割字符串
                if (cnt == 1) sendaddr = saddr, sendname = sname; // 第一个为发送者
                else { // 其余为接受者
                    if (mp2.find(saddr) == mp2.end()) addr.push_back(saddr); // 地址输入顺序存储 !!!
                    mp2[saddr].push_back(sname); // 地址->名字
                }
            }
            getline(cin, s); //读取*
            string data; // 存储数据文本
            while (getline(cin, s) && s[0] != '*') data += "     "+s + "\n"; // 拼接数据，前置5个空格
            for (auto p : addr) { // 每个发送地址
                printf("Connection between %s and %s\n", sendaddr.c_str(), p.c_str());
                printf("     HELO %s\n     250\n", sendaddr.c_str());
                printf("     MAIL FROM:<%s@%s>\n     250\n", sendname.c_str() ,sendaddr.c_str());
                int num = 0; set<string> _set; // 去重
                for (auto q : mp2[p]) { // 每个人名
                    if (_set.find(q) == _set.end()) _set.insert(q); // 去除重复人名！！！
                    else continue;
                    printf("     RCPT TO:<%s@%s>\n", q.c_str() ,p.c_str());
                    if (mp[p].find(q) != mp[p].end()) { // 存在此人
                        num ++; // 统计成功发送人数
                        printf("     250\n");
                    }                    
                    else printf("     550\n");
                }
                if (num != 0) printf("     DATA\n     354\n%s     .\n     250\n", data.c_str()); // 数据发送成功
                printf("     QUIT\n     221\n");
            }
        }
        break; // 直接退出循环
    }
    return 0;
}
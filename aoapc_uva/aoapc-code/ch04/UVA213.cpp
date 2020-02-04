#include<bits/stdc++.h>
using namespace std;
vector<string> bsv; // 存放二进制key
map<string, char> mp; // 构造key到字母映射
string decToBin(int val, int width) { // 10进制数值转为2进制字符串，并指定宽度
    string ret;
    do {
        ret.push_back((val % 2)+'0');
        val /= 2;
    } while(val != 0);
    reverse(ret.begin(), ret.end()); // 反转
    ret = string(width-ret.size(), '0') + ret; // 前置0
    return ret;
}
int binToDec(string s) { // 2进制字符串转为10进制数值
    int ret = 0;
    for (auto ch : s) ret = ret * 2 + (ch - '0');
    return ret;
}
void init() { // 构造0~1111111的二进制key
    string s; char str[1000];
    for (int l = 1; l < 8; l ++) { // [1,7]
        for (int j = 0; j < (1<<l)-1; j ++) { // [0,1<<l-1)
            bsv.push_back(decToBin(j, l)); // 保存
        }
    }
}
int main() {
    init();
    string head, mess, s, t;
    getline(cin, head); // 头部
    while(true) {
        while(getline(cin, s) && (s[0] == '0' || s[0] == '1')) mess += s; // 消息拼接
        if (mess.empty()) break; // 控制结束
        for (int i = 0; i < head.size(); i ++) mp.insert({bsv[i], head[i]}); // 构造映射
        int i = 0;
        while(i < mess.size()) { // 遍历信息串，解码规则实现
            t = mess.substr(i, 3); i += 3;// 开始3个字符
            if (t == "000") break;
            else {
                int l = binToDec(t); // 读取长度
                while (i < mess.size()) {
                    t = mess.substr(i, l); i += l;
                    if (t == string(l, '1')) break; // l个1，section结束
                    printf("%c", mp[t]); // 输出映射结果
                }
            }
        }
        puts(""); // 换行
        head = s; mess.clear(); mp.clear();// 下一个头部和清空
    }
    return 0;
}
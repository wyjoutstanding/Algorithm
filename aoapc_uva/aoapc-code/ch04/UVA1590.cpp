#include<bits/stdc++.h>
using namespace std;
void binstrToIP(string s) { // 二进制字符串转为IP形式
    for (int i = 0; i < 4; i ++) {
        bitset<8> bt(s.substr(i*8,8));
        printf("%u%s", bt.to_ulong(), i == 3 ? "\n" : ".");
    }
}
int main() {
    int n;
    while (cin >>n) {
        string smax, smin, smask, s, st;
        unsigned umin=UINT32_MAX, umax = 0;
        while (n --) {
            cin >>s;
            stringstream input(s);
            unsigned uint = 0;
            while (getline(input, st, '.')) { // 分割每个部分
                uint = (uint << 8) + (unsigned)stoi(st); // 256进制
            }
            if (umin >= uint) umin = uint, smin = s; // 最小值
            if (umax <= uint) umax = uint, smax = s; // 最大值
        }
        bitset<32> bmin(umin), bmax(umax), bmask(0xffffffffu);
        smin = bmin.to_string(); smax = bmax.to_string(); // 转为2进制字符串
        int cnt = 0;
        for (int i = 0; i < 32; i ++) { // 统计从头开始的公共子串长度
            if (smin[i] == smax[i]) cnt ++;
            else break;
        }
        for (int i = 0; i < 32-cnt; i ++) { // 设置IP地址和掩码低32-cnt位为0
            bmin.reset(i); bmask.reset(i); // 注意bitset逆序存储
        }
        binstrToIP(bmin.to_string()); binstrToIP(bmask.to_string());
    }
    return 0;
}
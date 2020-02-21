#include<bits/stdc++.h>
using namespace std;
int H, W, num=0;
string img[205], img2[205], s; // 原图像，加一轮白边的图像
map<char, string> mp; // 16进制字符->4位的2进制字符串
char word[6] = {'W', 'A', 'K', 'J', 'S', 'D'}; // 象形字内部对应的白色块个数
void trans() { // 一位16进制字符[0,f]转为4位的二进制字符串
    char c[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    for (int i = 0; i < 16; i ++) {
        bitset<4> bt(i); // 10->二进制数值->二进制字符串
        mp[c[i]] = bt.to_string();
    }
}
void dfs(int x, int y, char tag) { // tag='0'：遍历img的一个黑色连通块，并拷贝到img2；tag='0'：计算img2的白色连通块个数
    if (tag == '0') img[x][y] = '0';
    if (tag == '0') img2[x+1][y+1] = '1'; // 白色边框
    else img2[x][y] = '1';
    int xx, yy, h, w;
    for (int i = -1; i <= 1; i ++) { // 8个方向
        for (int j = -1; j <= 1; j ++) {
            if (i == 0 && j == 0) continue; // 不写也行，自身已经被赋值为1了
            xx = x + i; yy = y + j;
            h = (tag == '1') ? H+2 : H; w = (tag == '1') ? 4*W+2 : 4*W; // 边界控制
            if (xx >= 0 && xx < h && yy >= 0 && yy < w) {
                if (tag == '0' && img[xx][yy] == '1' || tag == '1' && img2[xx][yy] == '0') dfs(xx, yy, tag);
            }
        }
    }
}
int main() {
    trans(); // 16转二进制字符串初始化 
    while (cin >>H >>W && (H != 0 && W != 0)) {
        for (int i = 0; i < H; i ++) {
            cin >>s; img[i].clear();
            for (int j = 0; j < s.size(); j ++) img[i].append(mp[s[j]]); // 转为2进制
        }
        vector<char> res; // 保存结果
        for (int i = 0; i < H; i ++) {
            for (int j = 0; j < 4*W; j ++) {
                if (img[i][j] == '1') { // 发现一个黑色块
                    for (int k=0; k < H+2; k ++) img2[k] = string(4*W+2, '0'); // 初始化
                    dfs(i, j, '0'); // 拷贝连通块
                    int cnt=0; // 统计白色块个数
                    for (int i2 = 0; i2 < H+2; i2 ++) { // img2计算白色洞个数
                        for (int j2 = 0; j2 < 4*W+2; j2 ++) { // 注意长度和宽度
                            if (img2[i2][j2] == '0') {cnt++; dfs(i2, j2, '1');}
                        }
                    }
                    res.push_back(word[cnt-1]); // 存储对应象形字符结果
                }
            } 
        }
        sort(res.begin(), res.end()); // 字典序排列
        printf("Case %d: ", ++num);
        for (auto c : res) printf("%c", c);
        puts("");
    }
    return 0;
}
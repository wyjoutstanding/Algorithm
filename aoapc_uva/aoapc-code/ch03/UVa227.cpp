#include<bits/stdc++.h>
using namespace std;
string puzzle[5], s;
int cnt = 0, x, y, x2, y2, dict[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}}; // 上下左右偏移
map<char, int> mp{{'A',0}, {'B',1}, {'L',2}, {'R',3}}; // 字符映射到数字
bool isLegal = true, isOver = false; // 当前拼图是否有合法结果，是否结束
int main() {
    while(getline(cin,puzzle[0])) {
        if (puzzle[0][0] == 'Z') break;
        for (int i = 1; i < 5; i ++) getline(cin,puzzle[i]); // getline可读入空格
        for (int i = 0; i < 5; i ++) { // 找空格位置
            for (int j = 0; j < 5; j ++) { // 寻找空格坐标
                if(puzzle[i][j] == ' ') {
                    x = i; y = j;
                    break;
                }
            }
        }
        isOver = false; isLegal = true; // 初始化
        while(true) {
            cin >>s; getchar(); // 注意吸收换行
            for (auto ch : s) {
                if (ch == '0') { // 当前拼图结束
                    isOver = true; // 标记结束
                    if (cnt >= 1) printf("\n"); // 两个输出之间需有空行 
                    printf("Puzzle #%d:\n", ++cnt);
                    if (isLegal) { // 合法输出
                        for (int i = 0; i < 5; i ++) {
                            for (int j = 0; j < 5; j ++) {
                                printf("%c%c", puzzle[i][j], (j == 4) ? '\n' : ' ');
                            }
                        }
                    }
                    else printf("This puzzle has no final configuration.\n");
                }
                else {
                    x2 = x + dict[mp[ch]][0];
                    y2 = y + dict[mp[ch]][1];
                    if (x2 >= 0 && x2 < 5 && y2 >= 0 && y2 < 5) { // 是否合法
                        swap(puzzle[x][y], puzzle[x2][y2]); // 交换
                        x = x2; y = y2; // 更新x，y
                    }
                    else isLegal = false; // 非法
                }
            }
            if (isOver) break; // 跳出循环
        }
    }
    return 0;
}
/*
TRGSJ
XDOKI
M VLN
WPABE
UQHCF
ARRBBL0
ABCDE
FGHIJ
KLMNO
PQRS 
TUVWX
AAA
LLLL0
ABCDE
FGHIJ
KLMNO
PQRS 
TUVWX
AAAAABBRRRLL0
Z

*/
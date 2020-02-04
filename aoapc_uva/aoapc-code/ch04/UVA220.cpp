#include<bits/stdc++.h>
using namespace std;
int dict[8][2] = {{0,1},{1,0},{-1,0},{0,-1},{-1,1},{1,-1},{1,1},{-1,-1}}; // 8个方向
int n;
char now, rival; // 当前下棋者，对手
string board[9], s; // 棋盘，从1开始
void showResult() { // 打印棋盘
    for (int i = 1; i <= 8; i ++) cout <<board[i].substr(1) <<endl;
}
bool isLegal(int x, int y) { // 判断位置是否合法
    return (x >= 1 && x <= 8) && (y >= 1 && y <= 8);
}
int simulate(int x, int y, int isMoved) { // 模拟单个点8个方向的移动，isMoved控制是否改变值
    int ret = 0, legal=0,  px, py, cntb = 0, cntw = 0;
    for (int i = 0; i < 8; i ++) { // 8个方向
        vector<pair<int,int> > pos; ret = 0; // 存储经过的位置
        px = x + dict[i][0]; py = y + dict[i][1]; // 移动后位置
        if (isLegal(px, py) && board[px][py] == rival) { // 对应方向存在对手棋子
            while (isLegal(px, py)) { // 在此方向尽头是否存在now子
                pos.push_back({px,py}); // 保存路径
                px = px + dict[i][0]; py = py + dict[i][1];
                if (isLegal(px, py) && board[px][py] != rival) { // 发现非对手棋子
                    if (board[px][py] == now) { // 
                        ret = legal = 1; // 用于返回
                        if (isMoved == 1) { // 移动命令，标记点
                            for (auto p : pos) board[p.first][p.second] = now;
                            board[x][y] = now; // 新加入选择的点
                        }
                        break;
                    }
                    else break;
                }
            }
            if (isMoved == 0 && legal == 1) break;
        }
    }
    for (int i = 1; i <= 8 && isMoved == 1; i ++) { // 统计个数 
        for (int j = 1; j <= 8; j ++) {
            if (board[i][j] == 'B') cntb ++;
            else if (board[i][j] == 'W') cntw ++;
        }
    }
    if (isMoved == 1) printf("Black - %2d White - %2d\n", cntb, cntw); // 对齐：2个宽度
    return legal;
}
int move(int isList) { // 模拟遍历移动，isList控制是否打印合法位置信息
    int cnt = 0;
    for (int i = 1; i <= 8; i ++) {
        for (int j = 1; j <= 8; j ++) {
            if (board[i][j] == '-' && simulate(i, j, 0) == 1) { // 该点合法
                if (isList == 1) { // 控制输出
                    if (cnt != 0) printf(" ");
                    printf("(%d,%d)", i, j); 
                }
                cnt ++;
            }
        }
    }
    if (cnt != 0 && isList == 1) puts("");
    if (cnt == 0 && isList == 1) printf("No legal move.\n"); // 无合法移动
    return cnt; // 合法点数量
}
int main() {
    cin >>n; getchar(); // 吸收空行!!
    for (int k = 0; k < n; k ++) {
        if (k != 0) puts(""); // 两组输出间空行
        for (int i = 1; i <= 8; i ++) getline(cin, s), board[i] = "-"+s; // 从1开始
        cin >>now; // 当前玩家
        rival = (now == 'W') ? 'B' : 'W'; // 对手
        while (cin >>s && s[0] != 'Q') {
            if (s[0] == 'L') move(1);
            else if (s[0] == 'M') {
                if (move(0) == 0) { // 无合法位置
                    swap(now, rival); // 当前没有合法移动
                }
                simulate(s[1]-'0', s[2]-'0', 1);
                swap(now, rival); // 交换下棋者
            }
        }
        showResult(); getchar(); // 吸收空行
    }
    return 0;
}
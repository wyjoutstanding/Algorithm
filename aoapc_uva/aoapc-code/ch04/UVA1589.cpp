#include<bits/stdc++.h>
using namespace std;
int gdict[4][2] = {{0,1},{0,-1},{1,0},{-1,0}}; // 将军4个方向
int hdict[8][2] = {{-1,2},{1,2}, {1,-2},{-1,-2}, {2,1},{2,-1}, {-2,-1},{-2,1}}; // 马8个方向
bool isCheck = false, board[11][10] = {false}; // 标记点是否有子
typedef struct Pos {
    char type; // 类型
    int x, y; // 坐标
    Pos(char _type=0, int _x=0, int _y=0) :  type(_type), x(_x), y(_y) {} // 构造函数
}Pos;
bool isLegal(int x, int y, int isG) { // 判断位置是否合法
    if (isG) return (x >= 1 && x <= 3) && (y >=4 && y <= 6); // 将军，可以吃红子
    else return (x >= 1 && x <= 10) && (y >= 1 && y <= 9); // 普通棋子
}
int hpos(int px, int py, int y) { // 水平方向：判断将军和当前棋子相差个数
    int ans = 0, l = min(py, y), r = max(py, y);
    for (int j = l; j <= r; j ++) if (board[px][j]) ans ++;
    return ans - board[px][py]; // 考虑吃红子情况
}
int vpos(int px, int py, int x) { // 垂直方向：判断将军和当前棋子相差个数
    int ans = 0, l = min(px, x), r = max(px, x);
    for (int i = l; i <= r; i ++) if (board[i][py]) ans ++;
    return ans - board[px][py]; // 考虑吃红子情况
}
int main() {
    int n,  x, y, tx, ty;
    char type;
    while (scanf("%d %d %d", &n, &x, &y) == 3 && n != 0) {
        vector<Pos> red; // 存储红子坐标信息
        fill(board[0], board[0]+110, 0); // 棋盘初始化，仅记录是否有子
        while (n --) {
            cin >>type >>tx >>ty;
            board[tx][ty] = true; // 标记
            red.push_back(Pos{type, tx, ty}); // 存储
        }
        int px = x, py = y; // 将军移动可能达到的位置
        for (int i = 0; i < 4; i ++) { // 黑子将军4个方向
            px = x + gdict[i][0]; py = y + gdict[i][1]; // 黑方将军移动后的位置
            if (isLegal(px, py, 1)) { // 将军位置合法
                isCheck = false; // 初始化
                for (auto& p : red) { // 遍历所有红子
                    if (p.type == 'G' && py == p.y && vpos(px, py, p.x) == 1) isCheck = true; // 可杀死
                    else if (p.type == 'R' && (py == p.y && vpos(px, py, p.x) == 1 || px == p.x && hpos(px, py, p.y) == 1)) isCheck = true;
                    else if (p.type == 'C' && (py == p.y && vpos(px, py, p.x) == 2 || px == p.x && hpos(px, py, p.y) == 2)) isCheck = true;
                    else if (p.type == 'H') {
                        for (int j = 0; j < 8 && !isCheck; j ++) { // 马8个方向
                            int hx = p.x + hdict[j][0], hy = p.y + hdict[j][1]; // 日字格
                            int gx = p.x + gdict[j/2][0], gy = p.y + gdict[j/2][1]; // 马脚
                            if ((hx == px && hy == py) && isLegal(gx, gy, 0) && !board[gx][gy]) isCheck = true;
                        }
                    }
                    if (isCheck) break; // 一发现可以杀死立刻退出，进入下一个方向
                }
                if (!isCheck) break; // 可以不死，找到存活机会
            }
        }
        printf("%s\n", isCheck ? "YES" : "NO");
    }
    return 0;
}
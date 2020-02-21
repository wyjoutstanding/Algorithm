#include<bits/stdc++.h>
using namespace std;
int r1, c1, r2, c2, r0, c0, x, y;
char dc;
string name, ds;
map<pair<char,char>,pair<int,int> > dict { // 12个方向向量
    {{'N','L'},{0,-1}}, {{'S','L'},{0,+1}}, {{'E','L'},{-1,0}}, {{'W','L'},{+1,0}},
    {{'N','F'},{-1,0}}, {{'S','F'},{+1,0}}, {{'E','F'},{0,+1}}, {{'W','F'},{0,-1}},
    {{'N','R'},{0,+1}}, {{'S','R'},{0,-1}}, {{'E','R'},{+1,0}}, {{'W','R'},{-1,0}} 
};
map<char, pair<int,int> > dict2 {{'N',{-1,0}}, {'S',{+1,0}}, {'E',{0,+1}}, {'W',{0,-1}}};
map<char, int> tonum {{'N',0}, {'E',1}, {'S',2}, {'W',3},{'L',0},{'F',1},{'R',2}}; // 4个方向转为数字
map<char, string> maze[10][10]; // 迷宫存储
vector<int> path[10][10][4]; // 层次->上一个点路径记录
// vector<int> path[10][10][4][3]; // 层次->上一个点路径记录
int layer[10][10][4]={0}, vis[10][10][4]={0}; // 层次记录，标记是否在队列中
char getNextDir(char dir, char turn) { // 根据方向和转向确定下一个方向
    string dirs="NESW"; // 注意顺序
    switch (turn) {
        case 'F': return dir;
        case 'L': return dirs[(dirs.find(dir)+3) % 4];
        case 'R': return dirs[(dirs.find(dir)+1) % 4];
    }
    return 'e'; // 错误标记
}

void bfs() {
    queue<vector<int> > q; // 队列
    r0 = r1+dict2[dc].first-1; c0 = c1+dict2[dc].second-1;
    if (r0 == r2-1 && c0 == c2-1) {
        printf("  (%d,%d) (%d,%d)\n", r1,c1,r2,c2);
        return;
    }
    q.push({r1+dict2[dc].first-1,c1+dict2[dc].second-1,dc}); // 起始点坐标和前进方向
    vis[r0][c0][tonum[dc]] = 1;
    // vis[r1+dict2[dc].first][c1+dict2[dc].second][dc][] = 1; // 进队
    while (!q.empty()) {
        auto p = q.front(); q.pop(); //vis[p[0]][p[1]] = 0; // 出队
        // printf("--%d %d %c\n", p[0], p[1], p[2]);
        // if (p[0] == r2 && p[1] == c2) break; // 到达出口
        // if (vis[p[0]][p[1]][tonum[p[2]]] == 0) vis[p[0]][p[1]][tonum[p[2]]] = 1; // 标记该点的对于方向已走
        // else continue;
        if (p[0] == r2-1 && p[1] == c2-1) {
            // printf("FIND--------:%d\n", layer[p[0]][p[1]][tonum[p[2]]]);
            p[2] = tonum[p[2]];
            vector<pair<int,int> > ans{{r2,c2}};
            do {
                ans.push_back({p[0]+1, p[1]+1});
                // printf("(%d %d %d) ", p[0]+1, p[1]+1, p[2]);
                p = path[p[0]][p[1]][p[2]];
                // p = path[p[0]][p[1]][getNextDir(p[2],)];
            } while (p[0] != r0 || p[1] != c0 || p[2] != tonum[dc]);
            // printf("---ok-------\n");
            ans.push_back({r0+1,c0+1});
            ans.push_back({r1,c1});
            for (int i=ans.size()-1, j=0; i >= 0; i --, j ++) {
                if (j != 0 && j%10 == 0) puts("");
                printf("%s(%d,%d)", (j%10 == 0) ? "  " : " ", ans[i].first, ans[i].second);
            } puts("");
            return;
        }
        for (auto t : maze[p[0]][p[1]][p[2]]) {
            auto now = dict[{p[2], t}]; // 当前可达方向
            // printf("----%d %d  ", now.first, now.second);
            int x = p[0] + now.first, y = p[1] + now.second;
            // printf("---- %d %d %c ", x, y, getNextDir(p[2],t));
            char dir=getNextDir(p[2],t);
            if (maze[0][0][p[2]] == "") printf("1 1 empty***********\n");
            if (x >= 0 && x < 9 && y >= 0 && y < 9 && !maze[x][y].empty() && layer[x][y][tonum[dir] == 0]) {
            // if (x >= 0 && x < 9 && y >= 0 && y < 9 && !maze[x][y].empty() && vis[x][y][tonum[dir]] == 0) {
                printf("%d %d\n", x, y);
                q.push({x, y, getNextDir(p[2],t)});
                layer[x][y][tonum[getNextDir(p[2],t)]] = layer[p[0]][p[1]][tonum[p[2]]] + 1; // 层次增加
                path[x][y][tonum[dir]] = {p[0],p[1],tonum[p[2]]}; // 路径记录
                vis[x][y][tonum[dir]] == 1;
                // path[x][y][tonum[dir]][layer[x][y][tonum[dir]]] = {p[0],p[1],tonum[p[2]],layer[x][y][tonum[dir]]-1}; // 路径记录
                // printf("**** (%d %d %c %d)  -->  (%d %d %c %d)\n", x,y,dir,tonum[dir], p[0],p[1],p[2],tonum[p[2]]);
                // printf(" layer:%d\n", layer[x][y][tonum[getNextDir(p[2],t)]]);
            }
        }
    }
    printf("  No Solution Possible\n");
    // int x=r2, y=c2; // 输出
    // for (int i = layer[r2][c2]; i >= 1; i --) {
    //     printf("(%d,%d)\n", path[x][y][i].first, path[x][y][i].second);
    //     x = path[x][y][i].first; y = path[x][y][i].second;
    // }
}
int main() {
    while (cin >>name && name != "END") {
        cin >>r1 >>c1 >>dc >>r2 >>c2;
        fill(maze[0], maze[0]+100, map<char,string>{});
        while (cin >>x && x != 0) {
            cin >>y;
            while (cin >>ds && ds[0] != '*') {
                maze[x-1][y-1][ds[0]] = ds.substr(1); // 从0存储
            }
        }
        // maze[r1][c1][dc] = 
        // fill(path[0][0][0], path[0][0][0]+10*10*4*3, vector<int>{});
        fill(path[0][0], path[0][0]+10*10*4, vector<int>{});
        fill(layer[0][0], layer[0][0]+10*10*4, 0); // 初始化
        fill(vis[0][0], vis[0][0]+10*10*4, 0); // 初始化

        // puts("-----------maze----------------");
        // for (int i = 0; i < 10; i ++) {
        //     for (int j = 0; j < 10; j ++) {
        //         if (!maze[i][j].empty()) printf("(%d %d ", i, j);
        //         for (auto p : maze[i][j]) printf("%c%s ", p.first, p.second.c_str()); 
        //         if (!maze[i][j].empty()) puts(")");
        //     }
        // }
        cout <<name <<endl;
        bfs();
    }
    return 0;
}
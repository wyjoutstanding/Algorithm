/*
 * @Author: wuyangjun
 * @Date: 2019-08-10 16:52:24
 * @LastEditTime: 2019-08-10 17:55:47
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
// 像素点坐标
struct Node {
    int x, y, z;
}node, newNode;
int pixel[1230][130][61] = {0}; //3维数组(x,y,z)
bool inq[1230][130][61] = {0}; //记录是否入队
int M, N, L, T; //行，列，层，阈值
// x,y,z增量，控制6个方向
int X[] = {0, 0, 0, 0, 1, -1};
int Y[] = {0, 0, 1, -1, 0, 0};
int Z[] = {1, -1, 0, 0, 0, 0};
bool judge(int x, int y, int z) {
    // 越界
    if(x >= M || x < 0 || y >= N || y < 0 || z >= L || z < 0) return false;
    // 0或已在队列
    if(pixel[x][y][z] == 0 || inq[x][y][z] == true) return false;
    return true;
}
int bfs(int x, int y, int z) { 
    int cnt = 0; //统计1的个数
    queue<Node> q;
    node.x = x;
    node.y = y;
    node.z = z;
    q.push(node); //首节点入队
    inq[node.x][node.y][node.z] = true; //入队立刻标记
    while(!q.empty()) {
        node = q.front();
        q.pop();
        cnt ++; //出队统计1的个数
        // 遍历6个方向
        for(int i = 0; i < 6; i ++) {
            newNode.x = node.x + X[i];
            newNode.y = node.y + Y[i];
            newNode.z = node.z + Z[i];
            if(judge(newNode.x, newNode.y, newNode.z)) {
                q.push(newNode);
                inq[newNode.x][newNode.y][newNode.z] = true; //入队立刻标记
            }
        }
    }
    // 达到阈值T才有效
    if(cnt >= T) return cnt;
    else return 0;
}
int main() {
    scanf("%d %d %d %d", &M, &N, &L, &T);
    int sum = 0; //有效1的总数
    // 怎么存储就怎么访问
    for(int z = 0; z < L; z ++) {
        for(int x = 0; x < M; x ++) {
            for(int y = 0; y < N; y ++) {
                scanf("%d", &pixel[x][y][z]);
            }
        }
    }
    // 遍历每个点
    for(int z = 0; z < L; z ++) {
        for(int x = 0; x < M; x ++) {
            for(int y = 0; y < N; y ++) {
                if(pixel[x][y][z] == 1 && inq[x][y][z] == false) {
                    sum += bfs(x, y, z);
                }
            }
        }
    }
    printf("%d\n", sum);
    return 0;
}
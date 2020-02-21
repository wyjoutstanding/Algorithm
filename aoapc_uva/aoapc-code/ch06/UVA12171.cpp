// #include<bits/stdc++.h> // 不要用万能头文件,math.h中的x0,x1...会产生冲突
#include <cstdio> // scanf,printf
#include <algorithm> // sort,lower_bound
#include <queue> // queue
#include <cstring> // memset()
using namespace std; // 默认命名空间
const int maxn=55, maxp=1001; // 长方体个数最大值，坐标最大值
int color[maxn*2][maxn*2][maxn*2]; // 标记长方体是空气还是铜盘，bfs使用；0空气，1铜盘，2空气已访问
int x0[maxn], x1[maxn], y0[maxn], y1[maxn], z0[maxn], z1[maxn]; // 原始数据，每个长方体的xyz边长起止位置
int xs[2*maxn], ys[2*maxn], zs[2*maxn]; // 离散化坐标：xs存储x0和x1中所有去重升序排列后的坐标
int nx, ny, nz; // 记录xs,ys,zs的长度
int dirt[6][3]={{+1,0,0},{-1,0,0}, {0,+1,0},{0,-1,0}, {0,0,+1},{0,0,-1}}; // 沿着x,y,z轴的6个方向
int getId(int *a, int n, int val) { // 获取val在数组a中的下标
    return lower_bound(a, a+n, val) - a; // 复杂度logn，接近常数查找
}
struct Cell { // 存储逻辑上的长方体
    int x, y, z; // 用来bfs的坐标，表示长方体左下角
    Cell (int _x, int _y, int _z) : x(_x), y(_y), z(_z) {} // 构造函数
    bool isValid() {return (0 <= x && x < nx-1) && (0 <= y && y < ny-1) && (0 <= z && z < nz-1);} // 判断位置是否合法
    Cell getNeighbor(int dir) {return Cell(x+dirt[dir][0], y+dirt[dir][1], z+dirt[dir][2]);} // 返回dir方向的邻居
    int getVolume() { // 计算体积
        return (xs[x+1]-xs[x]) * (ys[y+1]-ys[y]) * (zs[z+1]-zs[z]); // 长*宽*高
    }
    int getArea(int dir) { // 根据方向获取内表面积
        if (dirt[dir][0] != 0) return (ys[y+1] - ys[y]) * (zs[z+1] - zs[z]); // 空气从x轴接触铜块，面积为y*z
        else if (dirt[dir][1] != 0) return (xs[x+1] - xs[x]) * (zs[z+1] - zs[z]); // 空气从y轴接触铜块
        else if (dirt[dir][2] != 0) return (xs[x+1] - xs[x]) * (ys[y+1] - ys[y]); // 空气从z轴接触铜块
        return -1; // 表示出错
    }
    bool isCopper() {return color[x][y][z] == 1;} // 判断是否为铜块
    bool isVisited() {return color[x][y][z] == 2;} // 若为空气，判断是否被访问
    void setVisited() {color[x][y][z] = 2;} // 设置为已访问
};
void discretize(int *a, int& n) { // 升序排列a，并去重；n为a的逻辑长度，注意引用
    sort(a, a+n); // 先排序
    n = unique(a, a+n) - a; // unique返回去重后的逻辑列表末尾指针
}
void bfs(int& v, int& m) { // 计算体积和表面积
    queue<Cell> q;
    q.push(Cell(0,0,0)); color[0][0][0] = 2; // 初始化，从加入的外围白边开始
    while (!q.empty()) {
        Cell cell = q.front(); q.pop();
        v += cell.getVolume(); // 累加空气体积
        for (int i=0; i < 6; i ++) { // 6个方向
            Cell neb = cell.getNeighbor(i); // 获取邻居
            if (neb.isValid()) { // 邻居有效
                // if (neb.isCopper()) m += neb.getArea(i); // 是铜块则累加从i方向接触的表面积
                if (neb.isCopper()) m += cell.getArea(i); // 是铜块则累加从i方向接触的表面积，若用neb计算面积，会导致重复计算
                else if (!neb.isVisited()) { // 未访问的空气块
                    neb.setVisited(); // 设为已访问
                    q.push(neb); // 加入队列
                }
            }
        }
    }
    v = (maxp*maxp*maxp) - v; // 铜块体积=总体积-空气体积
}
int main() {
    int T, n, lx, ly, lz; scanf("%d", &T);
    while (T --) {
        scanf("%d", &n);
        xs[0] = 0, ys[0] = 0, zs[0] = 0; // 增加一层外围起点
        xs[1] = maxp, ys[1] = maxp, zs[1] = maxp; // 外围终点
        nx = ny = nz = 2; // 当前长度
        for (int i=0; i < n; i ++) {
            scanf("%d %d %d %d %d %d", &x0[i], &y0[i], &z0[i], &lx, &ly, &lz);
            x1[i] = x0[i] + lx; y1[i] = y0[i] + ly; z1[i] = z0[i] + lz; // 终止位置
            xs[nx++] = x0[i], xs[nx++] = x1[i]; // 离散化准备
            ys[ny++] = y0[i], ys[ny++] = y1[i];
            zs[nz++] = z0[i], zs[nz++] = z1[i];
        }
        discretize(xs, nx); discretize(ys, ny); discretize(zs, nz); // 离散化三维坐标
        memset(color, 0, sizeof(color)); // 初始化
        for (int i=0; i < n; i ++) { // 遍历n个长方体，标记铜块
            int X0 = getId(xs, nx, x0[i]), X1 = getId(xs, nx, x1[i]); // 获取x0[i]在xs中的位置
            int Y0 = getId(ys, ny, y0[i]), Y1 = getId(ys, ny, y1[i]);
            int Z0 = getId(zs, nz, z0[i]), Z1 = getId(zs, nz, z1[i]);
            for (int x=X0; x < X1; x ++) { // (x,y,z)为铜块的左下角坐标
                for (int y=Y0; y < Y1; y ++) 
                    for (int z=Z0; z < Z1; z ++) {
                        color[x][y][z] = 1; // 标记左下角为(x,y,z)的长方体为铜块
                    }
            }
        }
        int v=0, m=0; // 体积，面积
        bfs(v, m); // floodfill类似连通块求解,dfs可能会超时
        printf("%d %d\n", m, v); // 面积，体积
    }
    return 0;
}
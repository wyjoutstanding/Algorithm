#include<bits/stdc++.h>
using namespace std;
struct Building {
    int id;
    double x, y, w, d, h;
    bool operator < (const Building& b) const { // 重载<;排序使用
        return (x < b.x) || (x == b.x && y < b.y); // x小优先；y小优先 
    }
} b[200]; // 存放建筑
int n, num=0;
bool isVisible(int i, double midx) { // 判断建筑i在midx所在区间是否可见
    if (!(b[i].x <= midx && b[i].x+b[i].w >= midx)) return false; // 不在区间
    for (int j = 0; j < n; j ++) {
        if (b[j].h >= b[i].h && b[j].y < b[i].y // 更高&&y更小&&存在于此区间
        && b[j].x <= midx && b[j].x+b[j].w >= midx) return false; // 建筑i被j挡住
    }
    return true; // 不被挡住
}
int main() {
    while (cin >>n && n != 0) {
        if (num != 0) puts(""); // 相邻测试输出的空行
        printf("For map #%d, the visible buildings are numbered as follows:\n", ++num);
        set<double> setx;
        for (int i = 0; i < n; i ++) {
            scanf("%lf %lf %lf %lf %lf", &b[i].x, &b[i].y, &b[i].w, &b[i].d, &b[i].h);
            b[i].id = i+1; // 标号，出现顺序
            setx.insert(b[i].x); setx.insert(b[i].x+b[i].w); // 两个x坐标，去重排序
        }
        sort(b, b+n); // 按输出顺序排列
        vector<double> x(setx.begin(), setx.end()); // set转为vector
        int cnt = 0; // 控制输出
        for (int i = 0; i < n; i ++) { // n个建筑
            for (int j = 0; j < x.size()-1; j ++) { // 每一段区间
                if (isVisible(i, (x[j]+x[j+1])/2)) { // x[j]和x[j+1]中任意一点状态一样
                    cnt ++;
                    printf("%s%d", cnt != 1 ? " ":"", b[i].id); // 前置空格
                    break;
                }
            }
        }
        puts("");
    }
    return 0;
}
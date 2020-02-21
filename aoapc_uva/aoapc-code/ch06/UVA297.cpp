#include<bits/stdc++.h>
using namespace std;
int T, cnt, img[1025][1025]={0}, idx;
// 根据s[idx]绘制左上角为(r,c)，边长为w的正方形区域
void draw(string s, int& idx, int r, int c, int w) {
    if (idx >= s.size()) return;
    idx ++; // 先后移,注意引用
    if (s[idx-1] == 'p') { // 父结点，绘制4个子方格
        draw(s, idx, r, c+w/2, w/2);     // 1
        draw(s, idx, r, c, w/2);         // 2
        draw(s, idx, r+w/2, c, w/2);     // 3
        draw(s, idx, r+w/2, c+w/2, w/2); // 4
    }
    else if (s[idx-1] == 'f') { // 黑色才处理，白色默认0，不计数
        for (int i = r; i < r+w; i ++)  // 按最小方块标记上色
            for (int j = c; j < c+w; j ++) 
                if (img[i][j] == 0) {cnt++; img[i][j] = 1;} // 统计黑色个数，记得加标记
    }
}
int main() {
    scanf("%d", &T);
    string s1, s2;
    while (T --) {
        cin >>s1 >>s2;
        cnt=0; fill(img[0], img[0]+1025*1025, 0); // 初始化 
        draw(s1, idx=0, 0, 0, 32); // 1024=32*32个格子
        draw(s2, idx=0, 0, 0, 32); // 注意初始化idx=0
        printf("There are %d black pixels.\n", cnt);
    }
    return 0;
}
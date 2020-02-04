#include<bits/stdc++.h>
using namespace std;
int n, m, cnt = 0, a, b;
char ch;
int main() {
    while (cin >>n >>m) {
        int h[10][10]={0}, v[10][10]={0}; // 存储水平和垂直连线
        while (m --) { // 输入
            cin >>ch >>a >>b;
            if (ch == 'H') h[a][b] = b+1;
            else v[b][a] = b+1; // 注意顺序
        }
        int right[10][10]={0}, down[10][10]={0}, num[10]={0}; // 向右/下最远可达距离，每种长度正方形计数
        for (int i = 1; i <= n; i ++) { // 每一行列
            for (int j = n-1; j >= 1; j --) {
                right[i][j] = (h[i][j] == j+1) ? right[i][j+1]+1 : 0; // 行：左->右
                down[j][i] = (v[j][i] == j+1) ? down[j+1][i]+1 : 0; // 列：上->下
            }
        }
        for (int l = 1; l <= n; l ++) { // 遍历每个正方形长度：l:[1,n]
            for (int i = 1; i <= n - l; i ++) { // x:[1,n-l]
                for (int j = 1; j <= n - l; j ++) { // y:[1,n-l]
                    if (right[i][j] >= l && down[i][j] >= l && down[i][j+l] >= l && right[i+l][j] >= l) num[l] ++, num[0] = 1; // num[0]标记存在解
                }
            }
        }
        if (cnt != 0) printf("\n**********************************\n\n"); // 以下为输出
        printf("Problem #%d\n\n", ++cnt);
        for (int i = 1; i <= n; i ++) 
            if (num[i] != 0) printf("%d square (s) of size %d\n", num[i], i);
        if (num[0] == 0) printf("No completed squares can be found.\n");
    }
    return 0;
}
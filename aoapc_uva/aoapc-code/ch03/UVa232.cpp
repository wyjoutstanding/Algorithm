#include<bits/stdc++.h>
using namespace std;
#define MAXN 11
string puzzle[MAXN];
int n, m, cnt = 0, num = 0, now, id[MAXN][MAXN] = {0}; // 编号
int main() {
    while(scanf("%d", &n) == 1 && n != 0) {
        scanf("%d", &m);
        if (num != 0) printf("\n"); // 仅两个puzzle间需空行
        printf("puzzle #%d:\n", ++num); // puzzle标号
        cnt = 0; // 统计每个有编号的格子
        printf("Across\n"); // 横向输出
        for (int i = 0; i < n; i ++) {
            cin >>puzzle[i];
            for (int j = 0; j < m; j ++) { // 标记有编号的格子
                if ((i == 0 || j == 0) && puzzle[i][j] != '*') id[i][j] = ++cnt; // 第一行/列全部编号
                else { // 当前白格子上方或左方存在黑格子
                    if (puzzle[i][j] != '*' 
                    && (puzzle[i][j-1] == '*' || puzzle[i-1][j] == '*')) id[i][j] = ++cnt;
                }
            }
            for (int j = 0; j < m; ) { // 横向输出
                if (puzzle[i][j] == '*') j++;
                else {
                    printf("%3d.", id[i][j]); // 宽度3，右对齐！！！
                    while(j < m && puzzle[i][j] != '*') printf("%c", puzzle[i][j++]);
                    printf("\n");
                }
            }
        }
        printf("Down\n"); // 纵向输出
        string ans[101]; // 保存每个标号对应结果
        for (int j = 0; j < m; j ++) { // 存放与ans中
            for (int i = 0; i < n; ) {
                if (puzzle[i][j] == '*') i ++;
                else {
                    now = id[i][j];
                    while(i < n && puzzle[i][j] != '*') ans[now] += puzzle[i++][j];// printf("%c", puzzle[i++][j]);
                }
            }
        }
        for (int i = 1; i < 101; i ++) { // 将ans中记录的值顺序输出
            if (!ans[i].empty()) {
                printf("%3d.%s\n", i, ans[i].c_str()); // 宽度3，右对齐！！！
            }
        }
    }
    return 0;
}
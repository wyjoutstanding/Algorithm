#include<bits/stdc++.h>
using namespace std;
int a[3][4] = {{2,4,5,3}, {2,6,5,1}, {1,4,6,3}}; // 3个旋转轴对应改变的轮换序列
string sa, sb, st;
void rotate(string& sr, int i, int j) { // sr绕i轴旋转j*90度
    string s = sr;
    for (int k = 0; k <= 3; k ++) { // 轮换：模拟旋转
        sr[a[i][k]-1] = s[a[i][(j+k)%4]-1]; // 从0开始存储,正方体标号从1开始
    }
}
int main() {
    while (cin >>st) {
        sa = st.substr(0,6); sb = st.substr(6);
        bool isSame = false; // 判断是否存在一样的情况
        for (int i = 0; i < 4 && !isSame; i ++) { // x轴4种转动角度
            for (int j = 0; j < 4 && !isSame; j ++) { // y轴
                for (int k = 0; k < 4 && !isSame; k ++) { // z轴
                    st = sb; // 更新
                    rotate(st, 0, i); // x轴转i*90角度
                    rotate(st, 1, j); // y轴转j*90角度
                    rotate(st, 2, k); // z轴转k*90角度
                    if (st == sa) isSame = true;
                }
            }
        }
        printf("%s\n", isSame ? "TRUE" : "FALSE");
    }
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define epison 1e-5 // 精度设置,1e-6也行
#define log10_2 log10(2)
double A, AP[11][31]; // A实际值，预测值
long long  B, BP[11][31]; // B实际值，预测值
string s;
void init() { // 打表，将所有可能的值记录下来
    for (int i = 0; i < 10; i ++) {
        for (int j = 1; j < 31; j ++) {
            double t = log10(1-pow(2,-i-1)) + (pow(2,j)-1)*log10_2; // 等式左侧：lg(1-(1/2)^(M+1)) + lg(2^(2^E-1))
            BP[i][j] = t; // 取整数部分，也就是B的值
            AP[i][j] = pow(10, t-BP[i][j]); // A = 10^(t-B)
        }
    }
}
int main() {
    init();
    while(cin >>s && s != "0e0") {
        s[s.find('e')] = ' '; // e替换为空格
        stringstream input(s);
        input >>A >>B;
        while(A < 1) A *= 10, B --; // 转换为科学计数法
        for (int i = 0; i < 10; i ++) { // 查表
            for (int j = 1; j < 31; j ++) {
                if (B == BP[i][j] && fabs(AP[i][j]-A) < epison) {
                    printf("%d %d\n", i, j);
                }
            }
        }
    }
    return 0;
}
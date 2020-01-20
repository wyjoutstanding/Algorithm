/*
 * @Author: wuyangjun
 * @Date: 2019-08-04 13:46:31
 * @LastEditTime: 2019-08-04 14:34:04
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
bool cmp(char a, char b) {
    return a < b;
}
//  模拟减法：根据val，得到其非降序排列a，非升序排列b
string solve(int val, string &a, string &b) {
    char tmp[5];
    sprintf(tmp, "%04d", val); //数字拆分为字符串
    a = tmp;
    sort(a.begin(), a.end(), cmp); //从小到大排序
    b = a;
    reverse(b.begin(), b.end()); //逆置
    // 将a,b转换为int型
    int num1, num2;
    sscanf(a.c_str(), "%d", &num1);
    sscanf(b.c_str(), "%d", &num2);
    // 计算差值后转为字符型
    sprintf(tmp, "%04d", num2 - num1);
    string ret = tmp;
    return ret;
}
int main() {
    int n;
    string a, b, ret;
    scanf("%d", &n);
    do {
        ret = solve(n, a, b);
        if(ret == "0000") {
            printf("%s - %s = 0000\n", b.c_str(), a.c_str());
            break;
        } 
        else {
            printf("%s - %s = %s\n", b.c_str(), a.c_str(), ret.c_str());
            sscanf(ret.c_str(), "%d", &n);
        }
        
    }while(ret != "6174");
    return 0;
}
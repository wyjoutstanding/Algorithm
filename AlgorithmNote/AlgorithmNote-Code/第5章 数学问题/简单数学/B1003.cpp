/*
 * @Author: wuyangjun
 * @Date: 2019-08-04 12:00:43
 * @LastEditTime: 2019-08-04 13:02:30
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    regex pattern("A*PAA*TA*"); // 匹配模式
    int N;
    scanf("%d", &N);
    // N个测试字符串
    for(int i = 0; i < N; i++) {
        cin >>s;
        bool ret = regex_match(s, pattern); //全文匹配成功返回true
        if(ret) { //成功
            string::iterator itP = find(s.begin(), s.end(), 'P'); //找到P的位置
            string::iterator itT = find(s.begin(), s.end(), 'T'); //找到T的位置
            // 3个部分A的个数
            int a = itP - s.begin(); 
            int b = itT - itP - 1; 
            int c = s.end() - itT - 1;
            // 满足a * b == c说明符合条件
            if(a * b == c) printf("YES\n");
            else printf("NO\n");
        }
        else printf("NO\n"); //失败
    }
    return 0;
}
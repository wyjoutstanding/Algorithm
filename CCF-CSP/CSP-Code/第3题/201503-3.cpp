/*
 * @Author: wuyangjun
 * @Date: 2019-09-07 08:36:48
 * @LastEditTime: 2019-09-07 09:01:51
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int monthDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 平年月份天数
bool isLeap(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}
int getMonthDays(int y, int m) { // 获取当前月份的天数
    if(m == 2 && isLeap(y)) return 29;
    else return monthDays[m];
}
int getWeekday(int year, int month, int day) { // 当前日期为周几，根据1850年1月1日周二
    int ret = 2;
    for(int y = 1850; y < year; y ++) { // 年
        int sum = isLeap(y) ? 366 : 365;
        ret = (ret + sum) % 7;
    }
    for(int m = 1; m < month; m ++) { // 月
        int sum = getMonthDays(year, m);
        ret = (ret + sum) % 7;
    }
    return (ret + day - 1) % 7; // 天
}
int main() {
    int a, b, c, _y1, _y2; // y1若定义成全局变量和math库冲突
    scanf("%d %d %d %d %d", &a, &b, &c, &_y1, &_y2);
    if(c == 7) c = 0; // 周天处理为0，便于模运算
    for(int y = _y1; y <= _y2; y ++) { // 每年
        int ret = getWeekday(y, a, 1), cnt = 0; // 当前年月的1号是周几；第几个周c
        for(int d = 1; d <= getMonthDays(y, a); d ++) { // 天
            int tmp = (ret + d - 1) % 7;
            if(tmp == c) cnt ++;
            if(cnt == b) {
                printf("%d/%02d/%02d\n", y, a, d);
                break;
            }
        }
        if(cnt != b) printf("none\n");
    }
    return 0;
}
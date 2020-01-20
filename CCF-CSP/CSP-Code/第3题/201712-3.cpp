/*
 * @Author: wuyangjun
 * @Date: 2019-08-31 12:13:20
 * @LastEditTime: 2019-09-03 15:30:43
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL s, t; // 起止时间
vector<string> command; // 命令名称，避免超时
map<LL, vector<int> > ans; // 每个时间对应的命令名字下标，避免超时
set<int> cmdTime[5]; // 命令5项的所有可能取值：minute,hour,monthDay,month,weekDay
map<string, int> monthAndWeekday = { // 月份和星期的映射，约定用小写
    {"jan", 1}, {"feb", 2}, {"mar", 3}, {"apr", 4}, {"may", 5}, {"jun", 6}, 
    {"jul", 7}, {"aug", 8}, {"sep", 9}, {"oct", 10}, {"nov", 11}, {"dec", 12}, 
    {"sun", 0}, {"mon", 1}, {"tue", 2}, {"wed", 3}, {"thu", 4}, {"fri", 5}, {"sat", 6}
};
vector<pair<int, int> > timeRange = {{0, 59}, {0, 23}, {1, 31}, {1, 12}, {0, 6}}; // 对应五个部分的所有取值范围
const LL year = 1e8, month = 1e6, day = 1e4, hour = 1e2;
int monthDay[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 平年月份天数
// 将字符串转为数值
int getNumber(string s) {
    int ret;
    if(isdigit(s[0])) { // 数值型
        sscanf(s.c_str(), "%d", &ret);
    }
    else { // 字符型
        for(auto& c : s) c = tolower(c); // 统一转为小写
        ret = monthAndWeekday[s];
    }
    return ret;
}
// 获取一条命令的五个时间取值及名字
void getCmdTime() {
    string s, tmp, name;
    for(int i = 0; i < 5; i ++) {
        cmdTime[i].clear(); // 清空
        cin >>s;
        if(s[0] == '*') { // 任意值
            for(int j = timeRange[i].first; j <= timeRange[i].second; j ++) cmdTime[i].insert(j);
            continue; // 直接进入下一部分
        }
        // 具体范围
        stringstream input(s);
        while(getline(input, tmp, ',')) { // 以,分割字符串
            int pos = tmp.find('-'), l, r; // 以-分割左右区间
            if(pos == string::npos) { // 左右相同
                l = getNumber(tmp);
                r = l;
            }
            else { // 左右区间不同
                l = getNumber(tmp.substr(0, pos));
                r = getNumber(tmp.substr(pos + 1, tmp.size() - pos - 1));
            }
            for(int j = l; j <= r; j ++) { // 保存所有取值
                cmdTime[i].insert(j); // set去重
            }
        }
    }
    cin >>name;
    command.push_back(name); // 保存命令名称
}
bool isLeap(int year) { // 判断闰年
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}
int maxMonthDay(int year, int month) { // 返回当前月份的最大天数
    if(isLeap(year) && month == 2) return monthDay[month] + 1;
    else return monthDay[month];
}
int getWeekday(int year, int month, int day) { // 1970.1.1为周4 => 获取当前日期是星期几
    int ret = 4;
    for(int y = 1970; y < year; y ++) { // 年
        int sum = (isLeap(y)) ? 366 : 365; // 闰平年
        ret = (ret + sum) % 7;
    }
    for(int m = 1; m < month; m ++) { // 月
        int sum = maxMonthDay(year, m); // 当前月份天数
        ret = (ret + sum) % 7;
    }
    ret = (ret + day - 1) % 7; // 日
    return ret;
}
void calCmd(int c) { // 计算编号为c的命令对应的合法时间
    for(int y = s / year; y <= t / year; y ++) { // 年
        for(auto m : cmdTime[3]) { // 月
            for(auto d : cmdTime[2]) { // 日
                if(d > maxMonthDay(y, m)) continue; // 当前年月没有这一天
                if(cmdTime[4].count(getWeekday(y, m, d)) != 0) { // 星期匹配
                    for(auto h : cmdTime[1]) { // 时
                        for(auto minute : cmdTime[0]) { // 分
                            LL time = y * year + m * month + d * day + h * hour + minute; // 计算当前时间
                            if(time >= s && time < t) ans[time].push_back(c); // 范围之内保存结果
                        }                        
                    }
                }
            }
        }
    }
}
void showResult() { // 输出结果
    for(auto t : ans) {
        for(auto c : t.second) {
            printf("%lld %s\n", t.first, command[c].c_str());
        }
    }
}
int main() {
    int n;
    cin >>n >>s >>t;
    for(int i = 0; i < n; i ++) {
        getCmdTime();
        calCmd(i);
    }
    showResult();
    return 0;
}
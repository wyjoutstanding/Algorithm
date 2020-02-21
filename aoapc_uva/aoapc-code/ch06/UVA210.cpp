#include<bits/stdc++.h>
using namespace std;
int T, a[7]; // 测试用例个数，a[0-6]分别表示输入的7个数
string s, ans;
int main() {
    cin >>T;
    for (int i = 0; i < T; i ++) {
        for (int j = 0; j < 7; j ++) scanf("%d", &a[j]);
        getchar(); // 吸收多余字符
        queue<string> q1[a[0]]; deque<int> qr; queue<int> qb; // 每个程序对应指令；ready；阻塞
        for (int j = 0; j < a[0]; j ++) { // n个程序
            while (getline(cin, s) && s != "end") q1[j].push(s);
            qr.push_back(j);
        }
        if (i != 0) puts(""); // 连续输出的空行
        map<string, string> vmp; // 变量对应的值
        bool isLock = false; // 标记是否有锁
        while (!qr.empty()) { // 等待队列非空
            int t = 0, k = qr.front(); qr.pop_front(); // 耗费时间，当前程序编号
            bool isBlock = false; // 标记是否发生阻塞
            while (t < a[6] && !q1[k].empty()) { // 未超时
                s = q1[k].front(); // 取出第一条命令
                int j = s.find('=');
                if (j != string::npos) { // 赋值
                    vmp[s.substr(0,j-1)] = s.substr(j+2);
                    t += a[1]; // 计时
                }
                else {
                    j = s.find(' ');
                    if (j != string::npos) { // 打印输出
                        ans = "0"; // 初始化
                        if (vmp[s.substr(j+1)] != "") ans = vmp[s.substr(j+1)];  
                        printf("%d: %s\n", k+1, ans.c_str()); // print val
                        t += a[2];
                    }
                    else {
                        if (s[0] == 'l') { // lock
                            if (!isLock) { // 未有锁定
                                isLock = true;
                                t += a[3]; // 时间增加
                            }
                            else { // 已有锁定
                                qb.push(k); // 加入阻塞队列尾部
                                isBlock = true;
                                break; // 直接退出，忽略其它剩余时间
                            }
                        }
                        else if (s[0] == 'u') { // unlock
                            isLock = false; // 标记未锁定
                            if (!qb.empty()) { // 阻塞非空
                                qr.push_front(qb.front()); // 阻塞头部加入ready头部
                                qb.pop();
                            }
                            t += a[4];
                        }
                    }
                }
                q1[k].pop(); // 确保阻塞时lock命令不会被删除
            }
            if (!q1[k].empty() && !isBlock) qr.push_back(k); // 非空再次加入等待队列尾部
        }
    }
    return 0;
}
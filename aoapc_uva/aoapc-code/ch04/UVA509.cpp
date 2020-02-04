#include<bits/stdc++.h>
using namespace std;
char parity, trans[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
int d, s, b, num = 0;
string disks[10]; // disks[i]表示第i块硬盘
bool isValid() { // 判断是否有效并计算缺失位
    bool ret = true;
    for (int j = 0; j < disks[0].size() && ret; j ++) { // j列
        int idx=-1, cnt=0, ex=(parity == 'E') ? 0 : 1; // x的下标，当前列x个数，列异或值
        for (int i = 0; i < d; i ++) { // i行
            if (disks[i][j] == 'x') idx = i, cnt ++; // 当前bit是x
            else ex ^= disks[i][j] - '0'; // 非x，计算异或值
        }
        if (cnt == 1) disks[idx][j] = ex + '0'; // 仅1个x，可计算恢复
        if (cnt >= 2 || (cnt == 0 && ex != 0)) ret = false; // 大于1个x||当前列和校验位异或值不为0
    }
    return ret; // 返回结果
}
void showContent() { // 显示恢复结果
    string ans;
    for (int j = 0; j < b; j ++) { // 第j列
        for (int i = 0; i < d; i ++) { // 第i行
            if (i != j % d) ans += disks[i].substr(j*s, s); // j%d==i判断是否为校验位
        }
    }
    ans += string((ans.size() % 4 == 0) ? 0 : (4-(ans.size()%4)), '0'); // 末尾补0凑成4整倍数
    for (int i = 0; i < ans.size() / 4; i ++) { // 转为16进制输出
        bitset<4> bt(ans.substr(i*4,4)); // bitset完成2进制字符串转换10进制
        cout <<trans[bt.to_ulong()];
    }
    cout <<endl;
}
int main() {
    while (cin >>d && d != 0) {
        cin >>s >>b >>parity;
        for (int i = 0; i < d; i ++) cin >>disks[i];
        bool valid = isValid();
        if (valid) {
            printf("Disk set %d is valid, contents are: ", ++num);
            showContent();
        }
        else printf("Disk set %d is invalid.\n", ++num);
    }
    return 0;
}
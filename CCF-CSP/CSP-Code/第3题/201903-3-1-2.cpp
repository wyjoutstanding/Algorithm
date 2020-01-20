/*
 * @Author: wuyangjun
 * @Date: 2019-08-27 19:40:47
 * @LastEditTime: 2019-08-27 20:50:14
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 82000; // 单个硬盘内容最大
char disk[1010][maxn]; // 硬盘内容存储
int n, s, l, m;
int len = 0, blkNum, stpNum; // 单个硬盘的总长、块数、条带数
int main() {
    scanf("%d %d %d", &n, &s, &l);
    int d;
    for(int i = 0; i < l; i ++) {
        scanf("%d ", &d);
        fgets(disk[d], maxn, stdin); // fgets才不会超时
        if(len == 0) len = strlen(disk[d]);
    }
    blkNum = len / 8;
    stpNum = blkNum / s;
    scanf("%d", &m);
    int bi, blkId, stpId, k, diskId;
    for(int i = 0; i < m; i ++) {
        scanf("%d", &bi);
        stpId = bi / s; // 所在的逻辑条带号
        k = stpId / (n - 1); // 在硬盘中的条带号（物理/行号）
        diskId = ((n - 1 - (k % n)) + (stpId % (n - 1)) + 1) % n; // 硬盘号=校准位置+相对位置+1
        // 超出总数 || 无法恢复
        if(bi >= blkNum * (n - 1) || (n - l > 1 && disk[diskId][0] == '\0')) {
            printf("-\n"); // 换行别漏
            continue;
        }
        int beginIdx = (k * s + bi % s) * 8; // 起始地址，1块=4B，1B需2个字符表示 
        if(disk[diskId][0] != '\0') { // 存在，直接输出
            for(int j = 0; j < 8; j ++) printf("%c", disk[diskId][beginIdx + j]);
        }
        else { // 丢失，异或同行的其他硬盘内容来恢复
            int ans = 0, tmp;
            char s[9];
            for(int d = 0; d < n; d ++) {
                if(disk[d][0] != '\0') {
                    for(int j = 0; j < 9; j ++) { // 提取同一行的块
                        s[j] = (j == 8) ? '\0' : disk[d][beginIdx + j];
                    }
                    sscanf(s, "%x", &tmp); // 转为10进制
                    ans ^= tmp;
                }
            }
            printf("%08X", ans); // 大写16进制输出，不足补0
        }
        printf("\n"); // 换行别漏
    }
    return 0;
}
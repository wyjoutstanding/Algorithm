/*
 * @Author: wuyangjun
 * @Date: 2019-08-26 23:25:21
 * @LastEditTime: 2019-08-27 19:39:11
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 10240010; // 最大块数
struct Pos {
    int dId; // 硬盘下标
    int sId; // 硬盘内的带号
}pos[maxn]; // 每条带对应的物理位置
char disk[1010][81200]; // 硬盘
char hashTable[maxn][9]; // 存在的直接输出
int len[1010] = {0}; // 记录硬盘长度
int n, s, l, m; // 硬盘数，条带大小，现存硬盘数，查询条数
int blkNum, stpNum; // 每个硬盘的块数，条数
char dth[20] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'}; // 10 -> 16
map<char, int> htd; // 16进制-> 10进制
void init() {
    for(int i = 0; i < 16; i ++) htd[dth[i]] = i;
    blkNum = strlen(disk[0]) / 8; // 块数
    stpNum = blkNum / s; // 条带数
}
void solve() {
    init();
    // 模拟逻辑填入条带，记录每条带的物理位置
    int diskId = n - 1; // 硬盘号
    for(int k = 0; k < stpNum; k ++) { // 行，每个硬盘的条带数
        int d = diskId; // 选中校准硬盘
        diskId --; // 递减
        if(diskId == -1) diskId = n - 1;
        for(int j = 0; j < n - 1; j ++) { // 填入n-1条带
            d = (d + 1) % n;
            int b = (n - 1) * k + j; // 带号
            pos[b].dId = d; // 硬盘号/列号
            pos[b].sId = k; // 带号/行号
        }
    }
    // 查询
    int bi, did, beginIdx;
    for(int i = 0; i < m; i ++) {
        scanf("%d", &bi);
        if(bi >= blkNum * (n - 1)) {
            printf("-\n");
            continue;
        }
        did = pos[bi / s].dId; // 块->条带->硬盘
        // 不可得的数据
        if((n - l > 1 && len[did] == 0)) { // 缺失硬盘超过1块 || 块号超出总长
            printf("-\n");
            continue;
        }
        if(strlen(hashTable[bi]) != 0) { // 哈希表存储已经访问过的块，加快速度
            printf("%s\n", hashTable[bi]);
            continue;
        }
        // 可得到数据
        beginIdx = (pos[bi / s].sId * s + bi % s) * 8; // 字节开始位置
        if(len[did] != 0) { // 无缺失，直接输出
            for(int j = 0; j < 9; j ++) {
                hashTable[bi][j] = (j == 8) ? '\0' : disk[did][beginIdx + j];
            }
            printf("%s\n", hashTable[bi]);
        }
        else { // 缺失，需计算
            char res[9] = {'0', '0', '0', '0', '0', '0', '0', '\0'};//tmp[9];
            for(int d = 0; d < n; d ++) {
                if(len[d] != 0) {
                    for(int j = 0; j < 8; j ++) {
                        res[j] = dth[htd[res[j]] ^ htd[disk[d][beginIdx + j]]];
                    }
                }
            }
            for(int j = 0; j < 9; j ++) {
                hashTable[bi][j] = (j == 8) ? '\0' : res[j];
            }
            printf("%s\n", hashTable[bi]);
        }
    }
}
void readData() {
    scanf("%d %d %d", &n, &s, &l);
    int d;
    for(int i = 0; i < l; i ++) {
        scanf("%d ", &d);
        fgets(disk[d], 81200, stdin); // 会读入空格
        len[d] = 1; // 标记，表示非空
    }
    scanf("%d", &m);
}
int main() {
    readData();
    solve();
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
map<char, int> mp{{'A',0}, {'C',1}, {'G',2}, {'T',3}}; // 便于循环处理
char itc[4] = {'A', 'C', 'G', 'T'}; // [0,4)->[A,C,G,T]
int T, m, n, num[1010][4] = {0}; // ATGC出现次数
string s;
int main() {
    scanf("%d", &T);
    while(T --) {
        scanf("%d %d", &m, &n);
        fill(num[0], num[0] + 4040, 0); // 初始化二维数组
        for (int i = 0; i < m; i ++) { // 统计每一列中每个子符出现次数
            cin >>s;
            for (int j = 0; j < n; j ++) num[j][mp[s[j]]] ++;
        }
        int errNum = 0, idx = 0, MAX = -1;
        for (int i = 0; i < n; i ++) { // 遍历每一列
            idx = 0, MAX = -1; // 初始化
            for (int j = 0; j < 4; j ++) { // ACGT
                if (MAX < num[i][j]) { // 找最大值
                    idx = j;
                    MAX = num[i][j];
                }
            }
            errNum += (m - MAX); // 不同的个数
            printf("%c", itc[idx]);
        }
        printf("\n%d\n", errNum);
    }
    return 0;
}
00251889168765743073047858942065491183879093198992
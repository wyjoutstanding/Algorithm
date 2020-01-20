/*
 * @Author: wuyangjun
 * @Date: 2019-08-07 14:30:31
 * @LastEditTime: 2019-08-07 14:49:49
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 26 * 26 * 26 * 10 + 1;
vector<int> hashTable[maxn];
int hNum = 0;
// 3个大写一个数字的字符串转换为数值
int getId(char *str) {
    int len = strlen(str);
    int id = 0;
    // 类似26进制
    for(int i = 0; i < len - 1; i ++) {
        id = id * 26 + (str[i] - 'A');
    }
    // 10进制
    id = id * 10 + (str[len - 1] - '0');
    return id;
}
// 按学生名建立到课程序列的映射
int readData() {
    int N, K;
    scanf("%d %d", &N, &K);
    int idx, n;
    for(int i = 0; i < K; i ++) {
        scanf("%d %d", &idx, &n);
        char name[30];
        for(int i = 0; i < n; i ++) {
            scanf("%s", name);
            hashTable[getId(name)].push_back(idx);
        }
    }
    return N;
}
// 根据课程号升序排列
void sortByIdx() {
    for(int i = 0; i < maxn; i ++) 
        sort(hashTable[i].begin(), hashTable[i].end());
}
// 根据姓名查询
void queryByName(int n) {
    char name[30];
    for(int i = 0; i < n; i ++) {
        scanf("%s", name);
        printf("%s", name);
        int id = getId(name);
        printf(" %d", hashTable[id].size());
        for(auto p : hashTable[id]) printf(" %d", p);
        printf("\n");
    }
}
int main() {
    int N = readData();
    sortByIdx();
    queryByName(N);
    return 0;
}
/*
 * @Author: wuyangjun
 * @Date: 2019-08-07 15:20:00
 * @LastEditTime: 2019-08-07 15:29:40
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2510;
vector<string> hashTable[maxn];
int readData() {
    int N, K;
    scanf("%d %d", &N, &K);
    char str[20];
    string name;
    int n, idx;
    for(int i = 0; i < N; i ++) {
        scanf("%s%d", str, &n);
        name = str;
        for(int i = 0; i < n; i ++) {
            scanf("%d", &idx);
            hashTable[idx].push_back(name);
        }
    }
    return K;
}
bool cmp(string a, string b) {
    return a < b;
}
void showResult(int K) {
    for(int i = 1; i <= K; i ++) {
        sort(hashTable[i].begin(), hashTable[i].end());
        int len = hashTable[i].size();
        printf("%d %d\n", i, len);
        for(int j = 0; j < len; j ++) {
            printf("%s\n", hashTable[i][j].c_str());
        }
    }
}
int main() {
    int K = readData();
    showResult(K);
    return 0;
}
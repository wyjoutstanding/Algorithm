/*
 * @Author: wuyangjun
 * @Date: 2019-07-28 15:25:38
 * @LastEditTime: 2019-07-28 15:31:03
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 128;
int main() {
    string a, b;
    getline(cin, a);
    getline(cin, b);
    int hashTable[maxn] = {0};
    for(int i = 0; i < b.size(); i++) {
        hashTable[b[i]] ++;
    }
    for(int i = 0; i < a.size(); i++) {
        if(hashTable[a[i]] == 0) printf("%c", a[i]); 
    }
    return 0;
}
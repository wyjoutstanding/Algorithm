/*
 * @Author: wuyangjun
 * @Date: 2019-07-28 09:42:11
 * @LastEditTime: 2019-07-28 09:48:41
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    string a, b;
    cin >>a >>b;
    // 哈希记录每个字符出现次数
    int hashTable[129] = {0};
    for(int i = 0; i < a.size(); i++) {
        hashTable[a[i]] ++;
    }
    int cnt = 0;
    for(int i = 0; i < b.size(); i++) {
        if(hashTable[b[i]] == 0) cnt ++; //缺失累计
        else hashTable[b[i]] --; //匹配成功
    }
    // 输出
    if(cnt == 0) printf("Yes %d", a.size() - b.size());
    else printf("No %d", cnt);
    return 0;
}
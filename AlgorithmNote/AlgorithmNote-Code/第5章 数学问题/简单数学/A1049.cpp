/*
 * @Author: wuyangjun
 * @Date: 2019-08-04 21:02:36
 * @LastEditTime: 2019-08-04 21:30:06
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int inf = (1 << 30) + 1;
struct Number {
    int val;
    int cnt;
}queryTable[1023];
void init() {
    queryTable[0].val = 1;
    queryTable[0].cnt = 1;
    int i = 1, radix = 1;
    while(i < 1023) {
        radix *= 10;
        queryTable[i].val = radix;
        queryTable[i].cnt = 1;
        int j = 0, end = i;
        i++;
        while(j < end) {
            queryTable[i].val = queryTable[end].val + queryTable[j].val;
            queryTable[i].cnt = queryTable[end].cnt + queryTable[j].cnt;
            i++;
            j++;
        }
    }
}
int main() {
    init();
    // for(int i = 0; i < 1023; i++){
    //     printf("%d %d\n", queryTable[i].val, queryTable[i].cnt);
    // }
    int n, sum = 0;
    scanf("%d", &n);
    for(int i = 0; i < 1023; i++) {
        if(queryTable[i].val <= n) {
            sum += queryTable[i].cnt;
        }
        else break;
    }
    printf("%d\n", sum);
    return 0;
}
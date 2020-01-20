/*
 * @Author: wuyangjun
 * @Date: 2019-07-30 16:42:12
 * @LastEditTime: 2019-07-30 17:39:06
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100001;
int a[maxn]; //数值 -> 位置
int main() {
    int N;
    scanf("%d", &N);
    set<int> mySet;
    for(int i = 0; i < N; i++) {
        int t;
        scanf("%d", &t);
        a[t] = i; //数值 -> 位置
        if(t != i) mySet.insert(t); //将不在正确位置的值存起来
    }
    int cnt = 0; //交换个数
    while(true) {
        // 全部归位
        if(mySet.empty()) break;
        // 0在正确位置，打乱它
        if(a[0] == 0) {
            int ret = *mySet.begin();
            swap(a[0], a[ret]);
            mySet.insert(0);
            cnt ++;
        }
        else {
            while(a[0] != 0) {
                mySet.erase(a[0]);
                swap(a[0], a[a[0]]);
                if(a[0] == 0) mySet.erase(0); //考虑依次交换，2个元素正确归位
                cnt ++;
            }
        }
    }
    printf("%d\n", cnt);
    return 0;
}
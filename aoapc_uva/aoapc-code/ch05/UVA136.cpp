#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int main() {
    LL a[3] = {2,3,5}, t, num=0;
    priority_queue<LL, vector<LL>, greater<LL> > pq; // 优先队列
    set<LL> _set; // 判重
    pq.push(1L); _set.insert(1L); // 第一轮
    while (true) {
        t = pq.top(); pq.pop(); num ++;
        if (num == 1500) break;
        for (int i = 0; i < 3; i ++) // x,2x,3x,5x构造丑数
            if (_set.find(t*a[i]) == _set.end()) {
                pq.push(t*a[i]);
                _set.insert(t*a[i]);
            }
    }
    printf("The 1500'th ugly number is %lld.\n", t);
    return 0;
}
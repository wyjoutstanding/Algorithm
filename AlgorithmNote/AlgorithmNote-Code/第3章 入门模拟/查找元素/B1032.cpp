#include <bits/stdc++.h>
using namespace std;
int main() {
    long long res[200000] = {0}; //别开太大
    int n;
    cin >>n;
    long long a, b;
    for(int i = 0; i < n; i++) {
        cin >>a >>b;
        res[a] += b;
    }
    long long maxa, maxb;
    maxa = maxb = -1;
    for(int i = 0; i < 200000; i++) {
        if(res[i] > maxb) {
            maxa = i;
            maxb = res[i];
        }
    }
    cout <<maxa <<" " <<maxb <<endl;
    return 0;
}
/*
6
3 65
2 80
1 100
2 70
3 40
3 0 */

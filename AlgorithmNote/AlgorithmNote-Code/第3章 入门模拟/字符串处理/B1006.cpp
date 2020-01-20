#include <bits/stdc++.h>
using namespace std;
int mian() {
    int n;
    cin >>n;
    // int b, s, g;
    int radix[3];
    for(int i = 0; i < 3; i++) {
        radix[i] = n % 10;
        n /= 10;
    }
    for(int i = 2; i >= 0; i--) {
        for(int j = 0; j < radix[i]; j++) {
            if(i == 2) cout <<'B';
            else if(i == 1) cout <<'S';
            else cout <<j + 1;
        }
    }
    return 0;
}
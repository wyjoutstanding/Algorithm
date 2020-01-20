#include <bits/stdc++.h>
struct Price {
    int g, s, k;
}a, b, ans;
// a<=b：return true
bool isGrater(Price a, Price b) {
    if(a.g != b.g) return a.g <= b.g;
    if(a.k != b.k) return a.k <= b.k;
    else return a.s <= b.s;
}
int main() {
    scanf("%d.%d.%d", &a.g, &a.k, &a.s);
    scanf("%d.%d.%d", &b.g, &b.k, &b.s);
    int sign = 1;
    if(!isGrater(a,b)) {    //计算正负，保证a <= b
        Price t;
        t = a;
        a = b;
        b = t;
        sign = -1;
    }
    if(b.s < a.s) { //s借位
        ans.s = b.s - a.s + 29;
        b.k -= 1;
    }
    else ans.s = b.s - a.s;

    if(b.k < a.k) { //k借位
        ans.k = b.k - a.k + 17;
        b.g -= 1;
    }
    else ans.k = b.k - a.k;
    
    ans.g = sign * (b.g - a.g);
    printf("%d.%d.%d", ans.g, ans.k, ans.s);
    return 0;
}
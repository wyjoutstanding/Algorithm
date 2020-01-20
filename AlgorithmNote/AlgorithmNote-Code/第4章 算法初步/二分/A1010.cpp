/*
 * @Author: wuyangjun
 * @Date: 2019-08-01 08:27:25
 * @LastEditTime: 2019-08-01 11:11:49
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL inf = (1LL << 63) - 1;
// LL radixes[maxRadix];
// 字符数字化：0~9 -> 0~9; a~z -> 10~35
LL change(char ch) {
    if(ch >= '0' && ch <= '9') return ch - '0';
    else return (ch - 'a') + 10;
}
// radix进制转换为10进制
LL toDecimal(string &s, LL radix) {
    LL ret = 0, base = 1;
    for(LL i = s.size() - 1; i >= 0; i--) {
        LL digit = change(s[i]);
        // prLLf("digit:%d base:%d radix:%d\n", digit, base, radix);
        ret += (LL)digit * base;
        base *= (LL)radix;
        if(ret < 0 || ret > inf) return -1;
    }
    return ret;
}
// 找到第一个满足条件的下标，即最小的radix
// LL binarySearch(LL *a, LL left, LL right, string &s, LL val) {
//     LL mid;
//     while(left < right) {
//         mid = left + (right - left) / 2;
//         cout <<mid <<endl;
//         LL ret = toDecimal(s, a[mid]);
//         if(ret == val) right = mid;
//         else if(ret > val) right = mid - 1;
//         else left = mid + 1;
//     }
//     return left;
// }
LL binarySearch(LL *a, LL left, LL right, string &s, LL val) {
    // if(val == 1 && s.size()) return 1; //N1和N2均为1，解不唯一，取最小
    LL mid;
    while(left <= right) {
        mid = left + (right - left) / 2;
        // cout <<mid <<endl;
        LL ret = toDecimal(s, mid);
        if(ret == -1) return -1;
        if(ret == val) return mid;
        else if(ret > val) right = mid - 1;
        else left = mid + 1;
    }
    return -1;
}
int main() {
    string N1, N2;
    LL tag, radix;
    cin >>N1 >>N2 >>tag >>radix;
    if(tag == 2) swap(N1, N2); //保证N1以radix为基数
    LL radixes[36];
    // 初始化基数数组[1,36]
    // for(LL i = 0; i < maxRadix; i++) radixes[i] = i + 1;
    // cout <<toDecimal(N1, radix);
    // 确定基数的下界
    if(N1 == N2 && N1.size() == 1) {
        cout <<1;
        return 0;
    }
    char minRadix = N2[0];
    for(LL i = 1; i < N2.size(); i++) {
        if(minRadix < N2[i]) minRadix = N2[i];
    }
    LL val = toDecimal(N1, radix);
    LL low = change(minRadix) + 1;
    LL high = max(low, val) + 1;
    LL ret = binarySearch(radixes, low, high, N2, val);
    // // 输出
    if(ret == -1) cout <<"Impossible";
    else cout <<ret;
    return 0;
}
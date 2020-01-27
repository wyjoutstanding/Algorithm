#include<bits/stdc++.h>
using namespace std;
string a, b;
int getMin(string a, string b) { // 获取a和b最小的组合长度
    if (a.size() > b.size()) swap(a,b); // a为短者
    int MIN = a.size() + b.size();
    for (int i = a.size(); i > 0; i --) { // a的长度；a在b左侧
        int j;
        for (j = 0; j < i; j ++) {
            if (a[a.size()-i+j] == '2' && b[j] == '2') break;
        }
        if (j == i) { // 找到第一个符合
            MIN -= i;
            break;
        }
    }
    for (int i = 0; i <= b.size()-a.size(); i ++) { // b的起始位置；a包含于b
        int j;
        for (j = 0; j < a.size(); j ++) {
            if (a[j] == '2' && b[i+j] == '2') break;
        }
        if (j == a.size()) {
            MIN = b.size();
            break;
        }
    }
    for (int i = a.size()-1; i > 0; i --) { // a的长度；a在b右侧
        int j;
        for (j = 0; j < i; j ++) {
            if (a[j] == '2' && b[b.size()-i+j] == '2') break;
        }
        if (j == i) {
            MIN = min(MIN, (int)(a.size()+b.size()-i));
            break;
        }
    }
    return MIN;
}
int main() {
    while(cin >>a >>b) {
        printf("%d\n", getMin(a,b));
    }
    return 0;
}
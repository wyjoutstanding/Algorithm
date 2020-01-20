#include <bits/stdc++.h>
using namespace std;
typedef struct {
    string name;
    int yy, mm, dd;
}Birth;
//比较大小
bool Less(Birth b1, Birth b2) {
    bool flag  = false;
    if(b1.yy < b2.yy) flag = true;
    else if(b1.yy > b2.yy) flag = false;
    else {
        if(b1.mm < b2.mm) flag = true;
        else if(b1.mm > b2.mm) flag = false;
        else {
            if(b1.dd < b2.dd) flag = true;
            else if(b1.dd > b2.dd) flag = false;
            else flag = true;//最年长和最小不同，相等返回true
        }
    }
    return flag;
}
//判断是否合法
bool isLegal(Birth b) {
    Birth bmin = {"", 1814, 9, 6}, bmax = {"", 2014, 9, 6};//起止范围
    if(Less(bmin, b) && Less(b, bmax)) return true;
    else return false;
}
int main() {
    int n;
    scanf("%d", &n);
    Birth tBirth, bmin = {"", 2014, 9, 6}, bmax = {"", 1814, 9, 6};//出生时间数字最大和最小，对应年龄最小和最大
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        cin >>tBirth.name;//string只能用cin、cout
        scanf("%d/%d/%d", &tBirth.yy, &tBirth.mm, &tBirth.dd);//分隔符[/]
        if(isLegal(tBirth)) {
            cnt++;
            if(Less(tBirth, bmin)) bmin = tBirth;
            if(Less(bmax, tBirth)) bmax = tBirth;
        }
    }
    cout <<cnt;//需考虑cnt为0，所以不输出空格
    if(cnt != 0) {
        cout <<" " <<bmin.name <<" " <<bmax.name;
    }
    return 0;
}

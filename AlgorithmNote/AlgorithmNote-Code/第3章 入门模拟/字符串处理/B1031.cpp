#include <bits/stdc++.h>
using namespace std;
int main() {
    int weight[17] = {7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
    char check_code[11] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};
    int n;
    cin >>n;
    bool isAllPassed = true;
    for(int i = 0; i < n; i++) {
        string s;
        cin >>s;
        int sum = 0;
        bool flag = true;
        for(int i = 0; i < 17; i++) {
            if(s[i] >= '0' && s[i] <= '9') {//前17位全为数字
                sum += (s[i] - '0') * weight[i]; //计算权重
            }
            else {
                flag = false;
                isAllPassed = false;
                break;
            }
        }
        if(flag) {
            if(check_code[sum % 11] != s[17]) {//校验位失效
                cout <<s <<endl;
                isAllPassed = false;
            }
        }
        else cout <<s <<endl;
    }
    if(isAllPassed) cout <<"All passed" <<endl;
    return 0;
}
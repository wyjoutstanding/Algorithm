#include <bits/stdc++.h>
using namespace std;
struct account{
    string name;
    string pass;
}res[1001], s;
int main() {
    int N, cnt = 0;
    cin >>N;
    for(int i = 0; i < N; i++) {
        cin >>s.name >>s.pass;
        bool flag = false;
        for(int j = 0; j < s.pass.size(); j++) {
            switch (s.pass[j])
            {
            case '1': 
                flag = true;
                s.pass[j] = '@';
                break;
            case 'l': 
                flag = true;
                s.pass[j] = 'L';
                break;
            case '0': 
                flag = true;
                s.pass[j] = '%';
                break;
            case 'O': 
                flag = true;
                s.pass[j] = 'o';
                break;
            default:
                break;
            }
        }
        if(flag == true) {
            res[cnt].name = s.name;
            res[cnt].pass = s.pass;
            cnt++; //res[cnt++]会出现未知错误
        }
    }
    if(cnt == 0) {
        if(N == 1) cout <<"There is " <<N <<" account and no account is modified";//陷阱，要细心
        else cout <<"There are " <<N <<" accounts and no account is modified";
    }
    else {
        cout <<cnt <<endl; //别漏了
        for(int i = 0; i < cnt; i++) {
            cout <<res[i].name <<" " <<res[i].pass <<endl;
        }
    }
    
    return 0;
}
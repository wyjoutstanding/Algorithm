#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    cin >>s;
    int N, n1 = -1, n2; //字符串总长，纵向行数, 横向行数
    N = s.length();
    // 计算出满足条件的n1,n2
    for(int i = 3; i < N; i++) {
        for(int j = i; j >= 0; j--) {
            if(i + 2 * j -2 == N) {
                if(n1 < j)  {
                    n1 = j;
                    n2 = i;
                }
            }
        }
    }
    for(int i = 0; i < n1; i++) {   //n1 rows
        for(int j = 0; j < n2; j++) {   //n2 columns
            if(i != n1 - 1) {   //last row
                if(j == 0)  cout <<s[i];    //first column
                else if(j == n2 - 1)    cout <<s[N - i - 1];    //last column
                else cout <<" ";
            }
            else {
                cout <<s[i + j];
            }
        }
        cout<<endl;
    }
    // cout <<n1 << n2;
    return 0;
}
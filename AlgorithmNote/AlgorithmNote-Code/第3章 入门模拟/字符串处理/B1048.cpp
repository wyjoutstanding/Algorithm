#include <bits/stdc++.h>
using namespace std;
int main() {
    char change[13] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'J', 'Q', 'K'};
    string a, b;
    cin >>a >>b;
    // cout <<a <<" " <<b <<endl;
    int lena = a.size();
    int lenb = b.size();
    if(lena <= lenb) {
        for(int i = 0; i < lenb; i++) {
            if(i < b.size() - a.size()) cout <<b[i];//s[i]只能改变值，不能创建值
            else {
                int j = i - (lenb - lena);
                if((i + lenb) % 2 == 0) {
                    int t = b[i] - a[j];
                    if(t < 0) cout << t + 10;
                    else cout <<t;
                }
                else {
                    int t = ((b[i] - '0') + (a[j] - '0')) % 13;
                    cout <<change[t];
                }
            }
        }
    }
    else {
        for(int i = 0; i < lena; i++) {
            int numa = a[i] - '0';
            int numb = (i < lena - lenb) ? 0 : b[i - (lena - lenb)] - '0';
            if((i + lena) % 2 == 0) {
                int t = numb -numa;
                if(t < 0) cout << t + 10;
                else cout <<t;
            }
            else {
                cout <<change[(numa + numb) % 13];
            }
        }
    }
    return 0;
}
/*

            if(i < a.size() - b.size()) {
                if((i + lena) % 2 == 0) cout << 10 - (a[i] - '0');//s[i]只能改变值，不能创建值
                else cout << change[a[i] - '0'];
            }
            else {
                int j = i - (lena - lenb);
                if((i + lena) % 2 == 0) {
                    int t = b[j] - a[i];
                    if(t < 0) cout << t + 10;
                    else cout <<t;
                }
                else {
                    int t = ((b[j] - '0') + (a[i] - '0')) % 13;
                    cout <<change[t];
                }
            
 */
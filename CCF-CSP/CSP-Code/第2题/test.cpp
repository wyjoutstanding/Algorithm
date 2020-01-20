/*
 * @Author: wuyangjun 
 * @Create time: 2019-10-09 21:14:14 
 * @Last Modified time: 2019-10-09 21:14:14 
 * @Gitub: https://github.com/wyjoutstanding 
*/
#include<bits/stdc++.h>
using namespace std;
int main() {
    // int a, b, c;
    fstream f, fout;
    f.open("test.txt", ios::in);
    fout.open("ans.txt", ios::out);
    string str;
    // fgets(str, 1000, f);
    while(getline(f, str)) {
        if(!str.empty()) {
            fout <<str <<endl;
        }
    }
    f.close();
    fout.close();
    return 0;
}
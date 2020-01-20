// #include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <map>
using namespace std;
int main() {
    int n,m;
    cin >> n;
    map<int, string> mp;
    string s, c;
    int a;
    for(int i = 0;  i < n; i++) {
        cin >>s >>a >>c;
        s = s + " " + c;
        mp[a] = s;
    }
    cin >> m;
    for(int i = 0; i < m; i++) {
        cin >> a;
        cout <<mp[a] <<endl;
    }
    return 0;
}
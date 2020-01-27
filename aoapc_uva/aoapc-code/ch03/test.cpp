#include<bits/stdc++.h>
using namespace std;
int main() {
    ifstream f;
    f.open("back.md");
    string s,s2,s3;
    while(getline(f, s)) {
        stringstream input(s);
        input >>s2;
        s3.clear();
        if (s2 == "##") {
            cout <<"| ";
            input >>s2;
            cout <<s2.substr(1)<<"|";
            input >>s2;
            cout <<s2 <<"|";
            getline(input, s2, ']');
            // while(input >>s2) {
            //     bool flag = false;
            //     cout <<"s2:"<<s2<<endl;
            //     if (s2.back() == ']') s2.erase(s2.size()-1), flag=true;
            //     s3 += s2;
            //     if (flag) break;
            // }
            printf("[%s](#%s)| | |\n", s2.c_str(), s.substr(2).c_str());
        }
    }
    return 0;
}
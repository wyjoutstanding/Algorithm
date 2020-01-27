#include<bits/stdc++.h>
using namespace std;
string toLower(string a) {
    for (auto& ch : a) {
        if (ch == ' ') ch = '-';
        else ch = tolower(ch);
    }
    return a;
}
int main() {
    ifstream f;
    f.open("tmp.md");
    ofstream outf("tout.md");
    string s,s2,s3,ans;
    int cnt = 0;
    while(getline(f, s)) {
        stringstream input(s);
        input >>s2;
        s3.clear();
        if (s2 == "##") {
            cout <<"| ";
            input >>s2; s3 += s2.substr(1);
            cout <<s2.substr(1)<<"|";
            input >>s2; s3 += "-"+toLower(s2);
            cout <<s2 <<"|";
            getline(input, s2, ']');
            // for (auto& ch : s2) ch = tolower(ch);
            s3 += toLower(s2);
            // while(input >>s2) {
            //     bool flag = false;
            //     cout <<"s2:"<<s2<<endl;
            //     if (s2.back() == ']') s2.erase(s2.size()-1), flag=true;
            //     s3 += s2;
            //     if (flag) break;
            // }
            string t = "$toc"+to_string(cnt++);
            printf("[%s](#%s)| | |\n", s2.c_str(), s3.c_str());
            // printf("[%s](#%s)| | |\n", s2.c_str(), s.substr(2).c_str());
            // s += "\n<span id=\""+t+"\"></span>\n";
            ans += "## "+s.substr(s.find('[')+1, s.find(']')-4)+"\n";
        }
        else ans += s+"\n";
        
    }
        cout <<"-==========\n\n"<<ans;
    return 0;
}
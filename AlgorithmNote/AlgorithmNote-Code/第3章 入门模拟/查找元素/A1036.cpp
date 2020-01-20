#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >>n;
    string fname, mname;    //female|man's name
    string fid, mid;    //id
    int fgrade = -1, mgrade = 110;  //grade
    string tname, tgender, tid; 
    int tgrade; 
    for(int i = 0; i < n; i++) {
        cin >>tname >>tgender >>tid >>tgrade;
        if(tgender == "F") {
            if(fgrade < tgrade) {
                fgrade = tgrade;
                fname = tname;
                fid = tid;
            }
        }
        else if(tgender == "M") {
            if(mgrade > tgrade) {
                mgrade = tgrade;
                mname = tname;
                mid = tid;
            }
        }
    }
    if(fgrade == -1) cout <<"Absent" <<endl;
    else cout <<fname <<" " <<fid <<endl;
    if(mgrade == 110) cout <<"Absent" <<endl;
    else cout <<mname <<" " <<mid <<endl;
    if(fgrade == -1 || mgrade == 110) cout <<"NA" <<endl;
    else cout <<fgrade - mgrade <<endl;
        
    return 0;
}
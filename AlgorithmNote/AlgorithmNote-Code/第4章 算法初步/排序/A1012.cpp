#include <bits/stdc++.h>
using namespace std;
struct Rank{
    string id;
    int score;
}ranks[4][2001];
struct Info {
    char type;
    int order;
};
map<string, Info>  res;
bool cmp1(Rank a, Rank b) {
    return 
}
int main() {
    int N, M;
    cin >>N >>M;
    string id;
    int t, sum=0; 
    Info info;
    for(int i = 0; i < N; i++) {
        cin >>id;
        res[id] = info;
        for(int j = 0; j < 4; j++) {
            ranks[j][i].id = id;
            if(j != 3) {
                cin >>t;
                sum += t;
                ranks[j][i].score = t;
            }
            else ranks[j][i].score = sum / 3;
        }
    }
    

    return 0;
}
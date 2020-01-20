#include <bits/stdc++.h>
using namespace std;
typedef struct {
    string name;
    string id;
    int score;
}student;
bool cmp(student s1, student s2) {//降序排列
    if(s1.score > s2.score) return true;
    else return false;
}
int main() {
    int n;
    cin >>n;
    student res[n];
    for(int i = 0; i < n; i++) {
        cin >>res[i].name >>res[i].id >> res[i].score;
    }
    sort(res, res + n, cmp);
    cout <<res[0].name <<" " <<res[0].id <<endl;
    cout <<res[n-1].name <<" " <<res[n-1].id <<endl;

    return 0;
}
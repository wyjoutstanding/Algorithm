#include <bits/stdc++.h>
using namespace std;

struct Stu {
    string id;
    int grade[4];//A, C, M, E
}stu[2004]; //存储学号和四种分数
int type; //控制课程类别 0~3
bool cmp(Stu a, Stu b) {
    return a.grade[type] > b.grade[type]; //相等无需考虑，后续会再次遍历判断排名
}
// 学号映射到四种排名：id - > score[type]
map<string, int[4]> Rank;
int main() {
    int N, M;
    cin >>N >>M;
    for(int i = 0; i < N; i++) {
        cin >>stu[i].id >>stu[i].grade[1] >>stu[i].grade[2] >>stu[i].grade[3];
        stu[i].grade[0] = stu[i].grade[1] + stu[i].grade[2] + stu[i].grade[3]; //用总分代替平均分比较
    }
    // 对四类分数分别排名，控制全局变量type
    for(type = 0; type < 4; type++) {
        sort(stu, stu + N, cmp);
        Rank[stu[0].id][type] = 1;
        // 对同一种类的分数进行排名，同分排名相同
        for(int j = 1; j < N; j++) {
            if(stu[j-1].grade[type] == stu[j].grade[type]) {
                Rank[stu[j].id][type] = Rank[stu[j-1].id][type];
            }
            else Rank[stu[j].id][type] = j + 1;
        }
    }
    // M个查询，输出相应类别最高排名和类别
    char change[4] = {'A', 'C', 'M', 'E'};//便于输出类别
    string query;//查询id
    // M条查询
    for(int i = 0; i < M; i++) {
        cin >>query;
        if(Rank.count(query) == 0) cout <<"N/A" <<endl; //不存在
        else {
            int k = 0;//同分下默认A > C > M > E
            for(int j = 1; j < 4; j++) {
                if(Rank[query][k] > Rank[query][j]) k = j;
            }
            cout <<Rank[query][k] <<" " <<change[k] <<endl; //换行别漏
        }
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
struct Record {
    string id;
    int frank, location_num, lrank, grade;
}record[30001];
// 成绩高者优先；成绩相同则账号字典序小者优先
bool cmp(Record a, Record b) {
    if(a.grade != b.grade) return a.grade > b.grade;
    else return a.id < b.id;
}
int main() {
    // 每个地点的起始位置、人数
    int idx[302] = {0}, num[302] = {0}, N, K, sum = 0;
    cin >>N;
    // N个地点
    for(int i = 0; i < N; i++) {
        cin >>K;
        sum += K;//总人数
        // 计算每个地点在一维数组的起始位置和人数
        if(i == 0) idx[i] = 0;
        else idx[i] = idx[i-1] + num[i - 1];
        num[i] = K;
        // 存储第i个地点的信息
        for(int j = idx[i]; j < idx[i] + K; j++) {
            cin >>record[j].id >>record[j].grade;
            record[j].location_num = i + 1;
        }
        // 第i个地点排序
        sort(record + idx[i], record + idx[i] + num[i], cmp);
        // 生成本地排名，分数相同名次相同
        record[idx[i]].lrank = 1;
        for(int j = idx[i] + 1; j < idx[i] + num[i]; j++) {//注意终止位置
            if(record[j - 1].grade == record[j].grade) record[j].lrank = record[j - 1].lrank;
            else record[j].lrank = j - idx[i] + 1;//注意起始点
        }
    }
    // 输出、全局排序
    cout <<sum <<endl;
    // 全局排序
    sort(record, record + sum, cmp);
    // 全局排名计算
    record[idx[0]].frank = 1;
    cout <<record[0].id; 
    printf(" %d %d %d\n", record[0].frank, record[0].location_num, record[0].lrank);
    for(int i = 1; i < sum; i++) {
        if(record[i - 1].grade == record[i].grade) record[i].frank = record[i - 1].frank;
        else record[i].frank = i + 1;
        cout <<record[i].id; 
        printf(" %d %d %d\n", record[i].frank, record[i].location_num, record[i].lrank);
    }
    return 0;
}
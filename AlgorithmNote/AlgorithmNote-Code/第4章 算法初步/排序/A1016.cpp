#include <bits/stdc++.h>
using namespace std;
struct Record {
    int time, dd, hh, mm; //总时间：分钟为单位，天，小时，分
    int type;//类型：on->1 , off->0
}t;
// 根据相对时间来排序
bool cmp(Record a, Record b) {
    return a.time < b.time;
}
int main() {
    int rate[24], N, month;
    // 每个月的收费金额,单位：cents/minutes
    for(int i = 0; i < 24; i++) {
        scanf("%d", &rate[i]);
    }
    // N个人的信息，按名字分类存储
    scanf("%d", &N);
    map<string, vector<Record> > record;
    string name, status;
    for(int i = 0; i < N; i++) {
        cin >>name;
        scanf("%d:%d:%d:%d", &month, &t.dd, &t.hh, &t.mm);//分割
        t.time = t.dd * 24 * 60 + t.hh * 60 + t.mm;//相对总分钟数
        cin >>status;//on / off
        if(status == "on-line") t.type = 1;
        else t.type = 0;
        record[name].push_back(t);
    }
    // map自动按照key字典序升序排列，遍历每一个人
    map<string, vector<Record> >::iterator it;
    for(it = record.begin(); it != record.end(); it++) {
        // 对同一个人的所有记录按time升序排列
        sort(it->second.begin(), it->second.end(), cmp);
        vector<Record> res;
        // 获取所有相邻为on和off的记录
        vector<Record>::iterator it2, it_vec = it->second.begin();
        while(it_vec != it->second.end()) {
            if((it_vec + 1) == it->second.end()) break;
            if(it_vec->type == 1 && (it_vec + 1)->type == 0) {
                res.push_back(*it_vec);
                it_vec++;
                res.push_back(*it_vec);
            }
            it_vec++;
        }
        if(res.empty()) continue; //并非每个人都有有效通讯记录，无需输出
        // 存在匹配记录，需要输出
        cout <<it->first <<" ";
        printf("%02d\n", month);
        int sum_all = 0;//此人的所有花费总和
        // 成对遍历记录
        for(it_vec = res.begin(); it_vec != res.end(); it_vec += 2) {
            int sum = 0;//当前记录对花费
            it2 = it_vec + 1;
            int total_time = it2->time - it_vec->time;//通话时间
            int hh = it_vec->hh;//起始的小时开始算
            // 同一天&&同一小时内
            if(total_time + it_vec->mm < 60) {
                sum = rate[hh] * total_time;
            }
            else {//分为头，中间，尾部分别计算
                sum = rate[hh] * (60 - it_vec->mm);//填满第一个小时
                total_time = total_time - (60 - it_vec->mm);//剩余时间
                hh = (hh + 1) % 24;
                sum += rate[(hh + total_time / 60) % 24] * (total_time % 60);//计算尾部多余时间
                // 中间整倍数时间段
                for(int i = 0; i < total_time / 60; i++) {
                    int h = (hh + i) % 24;
                    sum += rate[h] * 60;
                } 
            }
            // 输出：日期不足2位时前向补0；花费保留两位小数，不足补0
            sum_all += sum;
            printf("%02d:%02d:%02d ", it_vec->dd, it_vec->hh, it_vec->mm);
            printf("%02d:%02d:%02d %d $%.02f\n", it2->dd, it2->hh, it2->mm, it2->time - it_vec->time, (float)sum / 100);
        }
        printf("Total amount: $%.02f\n", (float)sum_all / 100);//总花费
    }
    return 0;
}
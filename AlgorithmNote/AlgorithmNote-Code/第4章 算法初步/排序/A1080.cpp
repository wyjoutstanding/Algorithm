/*
 * @Author: wuyangjun
 * @Date: 2019-07-26 17:36:49
 * @LastEditTime: 2019-07-26 19:32:59
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct Student {
    int id;//0开始
    int ge, gi, sum;//GE, GI，总分
    int rank; //排名
    int choices[5];//学校选择：0开始
}stu;
struct School {
    int max;//最多录取人数
    int lowestRank; // 最低排名
    vector<int> adList; //录取生id列表：0开始
}school;
vector<School> res(100); //初始化后可使用下标访问
vector<Student> student; //N条申请记录
// 排序使用
bool cmp(Student a, Student b) {
    if(a.sum != b.sum) return a.sum > b.sum; //总分降序
    else return a.ge > b.ge;//GE降序
}
int main() {
    int N, M, K; //申请人数，学校数，志愿数
    scanf("%d %d %d", &N, &M, &K);
    // M个学校的招收人数
    for(int i = 0; i < M; i++) {
        scanf("%d", &res[i].max);
        res[i].lowestRank = 0; //初始化最低排名为0
    }
    // N个申请
    for(int i = 0; i < N; i++) {
        scanf("%d %d", &stu.ge, &stu.gi);
        for(int j = 0; j < K; j++) scanf("%d", &stu.choices[j]);
        stu.sum = stu.ge + stu.gi; //用总和表示总分
        stu.id = i; //别漏：从0开始
        student.push_back(stu);
    }
    // 排序
    sort(student.begin(), student.end(), cmp);
    // 计算排名
    student[0].rank = 1;//vector只要初始化后，操作与普通数组一样
    for(int i = 1; i < N; i++) {
        if(student[i-1].sum == student[i].sum && student[i-1].ge == student[i].ge) student[i].rank = student[i-1].rank;
        else student[i].rank = i + 1;
    }
    // 为N个学生投递申请
    for(int i = 0; i < N; i++) {
        // 依次投递K个志愿学校
        for(int j = 0; j < K; j++) {
            int idx = student[i].choices[j]; //第j个志愿学校
            if(res[idx].lowestRank == student[i].rank) {
                res[idx].adList.push_back(student[i].id); //同排名，同学校，即使名额超限也录取
                break;//一录取立刻退出
            }
            else if(res[idx].max > res[idx].adList.size()) {
                res[idx].adList.push_back(student[i].id);//录取第i个学生，排序后i已经不是学生的考号了
                res[idx].lowestRank = student[i].rank;//记录录取的最低排名
                break;
            }
        }
    }
    // 打印M个学校录取情况
    for(int i = 0; i < M; i++) {
        if(res[i].adList.empty()) printf("\n"); //无录取打印空行
        else {
            sort(res[i].adList.begin(), res[i].adList.end()); //录取学生按编号从小到大排序
            for(int j = 0; j < res[i].adList.size(); j++) {
                if(j == 0) printf("%d", res[i].adList[j]); //这种写法可保证仅一个录取人时不会多打印空格
                else printf(" %d", res[i].adList[j]);
            }
            printf("\n");
        }
    }
    return 0;
}
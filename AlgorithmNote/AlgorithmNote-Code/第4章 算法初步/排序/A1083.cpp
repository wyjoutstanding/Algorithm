/*
 * @Author: wuyangjun
 * @Date: 2019-07-26 16:14:32
 * @LastEditTime: 2019-07-26 16:50:03
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct Student {
    char name[12], id[12];
    int grade;
};
bool cmp(Student a, Student b) {
    return a.grade > b.grade;//没有相同分数
}
int main() {
    int N;
    scanf("%d", &N);
    Student res[N]; //存放学生记录
    for(int i = 0; i < N; i++) {
        scanf("%s %s %d", res[i].name, res[i].id, &res[i].grade);
    }
    // 按成绩降序排列
    sort(res, res + N, cmp);
    int gradeL, gradeR;
    scanf("%d %d", &gradeL, &gradeR);
    // 输出指定区间的信息
    int validNum = 0;
    for(int i = 0; i < N; i++) {
        if(res[i].grade <= gradeR) {
            if(res[i].grade >= gradeL) {
                printf("%s %s\n", res[i].name, res[i].id);
                validNum ++;
            }
            else break;
        }
    }
    if(validNum == 0) printf("NONE\n");
    return 0;
}
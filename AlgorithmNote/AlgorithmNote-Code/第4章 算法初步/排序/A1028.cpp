#include <bits/stdc++.h>
using namespace std;
struct Student {
    char info[3][10];//id, name, grade;用cin/cout会超时，所以不可以用string
}student[100005];
int type;//当前选中的列，简化代码
// 三个字段均用字符串来比较，便于编程
bool cmp(Student a, Student b) {
    if(strcmp(a.info[type], b.info[type]) != 0) return strcmp(a.info[type], b.info[type]) < 0;
    else return strcmp(a.info[0], b.info[0]) < 0;//id
}
int main() {
    int N, C;
    cin >>N >>C;
    for(int i = 0; i < N; i++) {
        scanf("%s %s %s", &student[i].info[0], &student[i].info[1], &student[i].info[2]);
    }
    type = C - 1;
    sort(student, student + N, cmp);
    for(int i = 0; i < N; i++) {
        printf("%s %s %s\n", student[i].info[0], student[i].info[1], student[i].info[2]);
    }
    return 0;
}
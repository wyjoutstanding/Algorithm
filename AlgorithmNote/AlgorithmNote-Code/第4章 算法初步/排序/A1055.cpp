#include <bits/stdc++.h>
using namespace std;
const int maxn = 100001;
struct Person {
    char name[10];
    int age, net_worth;
}person[maxn], res[maxn];
// 每个年龄对应的人数
int ageNum[204] = {0};

bool cmp(Person a, Person b) {
    if(a.net_worth != b.net_worth) return a.net_worth > b.net_worth;//降序
    else if(a.age != b.age) return a.age < b.age;
    else return strcmp(a.name, b.name) < 0;
}
int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    for(int i = 0; i < N; i++) {
        scanf("%s %d %d", person[i].name, &person[i].age, &person[i].net_worth);
    }
    sort(person, person + N, cmp);
    int resNum = 0;//有效查询人数
    for(int i = 0; i < N; i++) {
        // 每个年龄阶段最多取100个人，这步预处理很关键，否则会超时
        if(ageNum[person[i].age] <= 100) {
            ageNum[person[i].age] ++;
            res[resNum] = person[i];
            resNum ++;
        }
    }
    // K次查询并输出
    int max, ageL, ageR;
    for(int i = 0; i < K; i++) {
        scanf("%d %d %d", &max, &ageL, &ageR);
        printf("Case #%d:\n", i + 1);
        int printNum = 0;//打印个数
        // 遍历查询数组
        for(int j = 0; j < resNum && printNum < max; j++) {
            if(res[j].age >= ageL && res[j].age <= ageR) {
                printf("%s %d %d\n", res[j].name, res[j].age, res[j].net_worth);
                printNum ++;
            }
        }
        if(printNum == 0) printf("None\n");
    }
    return 0;
}

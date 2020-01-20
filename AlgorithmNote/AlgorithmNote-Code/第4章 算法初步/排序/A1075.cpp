/*
 * @Author: wuyangjun
 * @Date: 2019-07-26 09:28:48
 * @LastEditTime: 2019-07-26 14:09:34
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct User {
    int id; //学号
    int sum;//总分
    int perfectNum;//全对的题数
    int score[6];//从1开始，score[i]表示第i题得分，初始化为-2，编译不通过为-1
    bool isPrint;//无通过编译的提交或无提交不需输出
}user;
// 比较规则
bool cmp(User a, User b) {
    if(a.sum != b.sum) return a.sum > b.sum; //总分降序
    else if(a.perfectNum != b.perfectNum) return a.perfectNum > b.perfectNum; //完美题解数降序
    else return a.id < b.id;//学号升序
}
int main() {
    int N, K, M;
    scanf("%d %d %d", &N, &K, &M);
    int TotalScore[6]; //每一个题的总分
    for(int i = 1; i <= K; i++) scanf("%d", &TotalScore[i]);
    // 初始化
    user.sum = user.perfectNum = 0;
    user.isPrint = false; //初始化不打印
    for(int i = 0; i < 6; i++) user.score[i] = -2; //便于判断未通过编译，未提交
    
    map<int, User> res;// id -> User
    int id, pid, score;//学号， 题号， 得分
    // M次提交
    for(int i = 0; i < M; i++) {
        scanf("%d %d %d", &id, &pid, &score);
        if(res.count(id) == 0) res[id] = user;//初始化
        if(res[id].score[pid] < score) res[id].score[pid] = score; //每一题多次提交取最高分 
        res[id].id = id; //学号
    }
    // 统计每个人的总分,满分个数，是否打印
    vector<User> ans; //最终输出排行
    map<int, User>::iterator it;
    for(it = res.begin(); it != res.end(); it++) {
        // 遍历K道题，从1开始
        for(int j = 1; j <= K; j++) {
            if(TotalScore[j] == it->second.score[j]) it->second.perfectNum ++;//满分个数
            if(it->second.score[j] >= 0) { //-1, -2均不管
                it->second.sum += it->second.score[j];//总分
                it->second.isPrint = true; //不为-1 | -2，一个满足即可打印
            }
        }
        if(it->second.isPrint) ans.push_back(it->second); //需要打印的全部保存到新线性容器，便于排序
    }
    // 按照规则排序,map无法用sort排序，只好用线性容器
    sort(ans.begin(), ans.end(), cmp);
    // 计算排名&输出
    int preRank, curRank, preScore, cnt = 0;
    for (vector<User>::iterator it2 = ans.begin(); it2 != ans.end(); it2++) {//所有人
        // 计算排名，还是在结构体添加排名项比较简单，这个类似链表写法
        if(cnt == 0) curRank = 1;
        else {
            if(it2->sum == preScore) curRank = preRank;
            else curRank = cnt + 1;
        }
        preScore = it2->sum;//注意写法，溢出
        preRank = curRank;
        cnt ++;
        // 打印
        printf("%d %05d %d", curRank, it2->id, it2->sum);
        for(int j = 1; j <= K; j++) {
            if(it2->score[j] == -2) printf(" -");//未提交
            else if(it2->score[j] == -1) printf(" 0");//未通过编译
            else printf(" %d", it2->score[j]);//得分
        }
        printf("\n");
    }
    return 0;
}
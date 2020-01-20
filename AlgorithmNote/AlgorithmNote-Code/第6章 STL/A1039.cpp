/*
 * @Author: wuyangjun
 * @Date: 2019-08-07 13:32:44
 * @LastEditTime: 2019-08-07 14:05:26
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
map<string, vector<int> > res;
// 将数据建立映射:姓名->课程号列表
int readData() {
    int N, K;
    scanf("%d %d", &N, &K);
    int idx, n;
    for(int i = 0; i < K; i ++) {
        scanf("%d %d", &idx, &n);
        char str[40];
        string name;
        for(int i = 0; i < n; i ++) {
            scanf("%s", str); //避免超时
            name = str;
            res[name].push_back(idx);
        }
    }
    return N; //查询个数
}
// 对应的课程列表升序排列
void sortByIdx() {
    for(auto& mp : res) { //auto类型推导
        sort(mp.second.begin(), mp.second.end());
    }
}
// 根据N名字查询各自的课程号
void queryByName(int N) {
    char str[30];
    string name;
    for(int i = 0; i < N; i ++) {
        scanf("%s", str); //用scanf读入，否则会超时
        printf("%s", str);
        name =str;
        if(res.count(name) == 0) printf(" 0");
        else {
            auto vec = res[name];
            printf(" %d", vec.size());
            for(auto p : vec) printf(" %d", p);
        }
        printf("\n");
    }

}
int main() {
    int N = readData();
    sortByIdx();
    queryByName(N);
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
vector<set<int> > setCache; // 哈希表：集合id->集合
map<set<int>, int> setToId; // 映射：集合->id
int T, n;
string cmd;
int getSetId(const set<int>& _set) { // 获取set对应id，不存在则新分配一个
    if (setToId.find(_set) != setToId.end()) return setToId[_set]; // 存在
    setCache.push_back(_set); // 不存在则分配
    return setToId[_set] = setCache.size() - 1; // id/位置标号
}
int main() {
    cin >>T;
    while (T --) {
        cin >>n;
        stack<int> stk; setCache.clear(); setToId.clear(); // 初始化
        while (n --) {
            cin >>cmd;
            if (cmd == "PUSH") stk.push(getSetId(set<int>())); // 空
            else if (cmd == "DUP") stk.push(stk.top()); // 重复
            else {
                set<int> t, a, b;
                a = setCache[stk.top()]; stk.pop();
                b = setCache[stk.top()]; stk.pop();
                if (cmd == "UNION") set_union(a.begin(),a.end(),b.begin(),b.end(),inserter(t,t.begin()));
                if (cmd == "INTERSECT") set_intersection(a.begin(),a.end(),b.begin(),b.end(),inserter(t,t.begin()));
                if (cmd == "ADD") t = b, t.insert(setToId[a]);
                stk.push(getSetId(t));
            }
            printf("%d\n", setCache[stk.top()].size());            
        }
        puts("***");
    }
    return 0;
}
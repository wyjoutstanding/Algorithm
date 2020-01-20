/*
 * @Author: wuyangjun
 * @Date: 2019-08-29 09:49:20
 * @LastEditTime: 2019-08-29 23:05:29
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 105;
struct STNode {
    string element, id; // 元素，id
    int layer; // 层号
    vector<int> child; // 子结点列表
}stree[maxn];
struct Query { // 查询
    string content; // 查询内容
    int type; // 类型：元素：0；id：1
}tqy;
vector<Query> query; // 存储一条的查询路径
vector<int> ans; // 存放答案
int N, M; // 结点总个数；查询条数
// 读取每一行，处理字符串，存入结点
void getNode(int root) {
    char str[90];
    fgets(str, 90, stdin);
    string s = str;
    stree[root].layer = s.find_first_not_of('.') / 2; // 层号：.的个数除以2
    s = s.substr(stree[root].layer * 2, s.size() - stree[root].layer * 2 - 1); // 去除.. 和尾部换行
    auto p = s.find('#'); 
    auto& e = stree[root].element; // 便于使用
    if(p != string::npos) { // 存在id
        e = s.substr(0, p - 1); // 排除空格
        stree[root].id = s.substr(p + 1, s.size() - p - 1); // 排除# 
    }
    else e = s; // 只有元素
    transform(e.begin(), e.end(), e.begin(), ::tolower); // 元素全转为小写，大小写不敏感
}
// 栈模拟前序建树
void createStree(int root) {
    stack<int> stk;
    stk.push(root); // 根结点入栈
    int i = root + 1; 
    while(i <= N) { 
        while(stree[i].layer <= stree[stk.top()].layer) stk.pop(); // 保证top是i的父结点
        stree[stk.top()].child.push_back(i); // 将i添加为top的孩子结点
        stk.push(i); // i入栈，作为当前的父结点
        i ++;
    }
}
// 分割查询的路径
void getQuery() {
    char str[90];
    fgets(str, 90, stdin);
    string s = str, tmp;
    stringstream input(s.substr(0, s.size() - 1)); // 去换行
    while(getline(input, tmp, ' ')) { // 空行分割
        if(tmp[0] == '#') { // id
            tqy.content = tmp.substr(1);
            tqy.type = 1;
        }
        else { // 元素
            transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower); // 转为小写
            tqy.content = tmp;
            tqy.type = 0;
        }
        query.push_back(tqy);
    }
}
// 判断root结点与查询条件query[num]是否相等
bool isEqual(int root, int num) {
    auto& q = query[num];
    auto& t = stree[root];
    return q.type == 0 && q.content == t.element || q.type == 1 && q.content == t.id;
}
// 前序遍历以root为根，所有子结点中等于query[num]的结点（排除root)
void preOrder(int root, int num) {
    if(root <= N) {
        for(auto p : stree[root].child) {
            if(isEqual(p, num)) ans.push_back(p); // 符合则记录
            preOrder(p, num);
        }        
    }
}
// 遍历满足前query.size()-1个的结点root，查询root的子树中满足最后一个条件的结点
void dfs(int root, int num) {
    if(query.size() == 1) { // 单个查询特判
        if(isEqual(root, num)) ans.push_back(root);
        preOrder(root, num);
        return;
    }
    if(isEqual(root, num)) { // 多级查询
        num ++;
        if(num == query.size() - 1) {
            preOrder(root, num); // 获取所有符合条件的结点
            return;
        }
    }
    for(auto p : stree[root].child) { // 遍历所有子结点
        dfs(p, num);
    }
}
int main() {
    scanf("%d %d", &N, &M);
    getchar();
    for(int i = 1; i <= N; i ++) getNode(i);
    createStree(1); // 建树
    for(int i = 0; i < M; i ++) {
        query.clear(); // 记得清空
        getQuery(); // 获取查询路径
        ans.clear(); // 结果清空
        dfs(1, 0); // 搜索答案
        // 输出
        if(ans.empty()) printf("0\n");
        else {
            printf("%d ", ans.size());
            for(int i = 0; i < ans.size(); i ++) {
                printf("%d%s", ans[i], i == ans.size() - 1 ? "\n" : " ");
            }
        }
    }
    return 0;
}
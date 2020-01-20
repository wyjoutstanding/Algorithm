/*
 * @Author: wuyangjun
 * @Date: 2019-09-01 09:44:12
 * @LastEditTime: 2019-09-03 07:20:04
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct Node { // 静态树结点
    string key, value; // 键，值
    vector<int> child; // 孩子序列
};
vector<Node> tree(10000); // 静态树
int n, m, tNum = 1; // 行数、查询行数、树结点编号，从1开始，0默认为根
string json; // 存储去除空格和换行后的json字符串
void readData() { // 读入数据，去除空格，拼接保存为json
    scanf("%d %d", &n, &m);
    getchar(); // 吸收多余换行
    string s;
    for(int i = 0; i < n; i ++) {
        getline(cin, s);
        for(auto c : s) if(c != ' ') json += c; // 去空格
    }
}
void createTree() { // 分割key，value，栈模拟建立树
    stack<int> stk;
    stk.push(0); // 0作为root
    int i = 1; // json下标，去头{
    do {
        string key, value;
        while(json[i] != ':') { // 获取key
            if(json[i] == '\\') { // 转义符无条件保留它后面一位
                key += json[i + 1];
                i ++;
            }
            else if(json[i] != '"') key += json[i]; // 其余不是引号都保存
            i ++;
        }
        if(json[i] == ':') { // 获取value
            ++ i;
            if(json[i] == '{') { // value为对象OBJECT
                tree[tNum].key = key;
                tree[tNum].value = "OBJECT";
                tree[stk.top()].child.push_back(tNum); 
                stk.push(tNum); // 遇{入栈
                ++ tNum;
                ++ i;
            }
            else { // value为对象STRING
                while(json[i] != ',' && json[i] != '}') { // 提取value，和提取key过程一样
                    if(json[i] == '\\') { // 转义符无条件保留它后面一位
                        value += json[i + 1];
                        i ++;
                    }
                    else if(json[i] != '"') value += json[i]; // 其余不是引号都保存
                    i ++;
                }
                tree[tNum].key = key;
                tree[tNum].value = value;
                tree[stk.top()].child.push_back(tNum);
                if(json[i] == '}') stk.pop(); // 遇}出栈
                tNum ++;
                i ++;
                while(i < json.size() && (json[i] == ',' || json[i] == '}')) { // 碰到逗号,直接跳过，碰到}出栈
                    if(json[i] == '}') stk.pop();
                    i ++;
                }
            }
        }
    }while(i < json.size());
}
void query(string s) { // 对s进行查询
    stringstream input(s);
    vector<string> q;
    string tmp;
    while(getline(input, tmp, '.')) { // 按.分割查询
        q.push_back(tmp);
    }
    int root = 0; // root
    string ans;
    for(auto key : q) { // 根的孩子开始查找
        bool isFind = false;
        for(auto i : tree[root].child) { // 遍历孩子
            if(key == tree[i].key) { // 找到
                root = i;
                ans = tree[i].value;
                isFind = true;
                break;
            }
        }
        if(!isFind) { // 不存在
            printf("NOTEXIST\n");
            return;
        }
    }
    if(ans == "OBJECT") printf("OBJECT\n");
    else printf("STRING %s\n", ans.c_str());
}
int main() {
    readData();
    createTree();
    for(int i = 0; i < m; i ++) {
        string s;
        getline(cin, s);
        query(s);
    }
    return 0;
}
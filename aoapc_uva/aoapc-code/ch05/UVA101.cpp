#include<bits/stdc++.h>
using namespace std;
string op1, op2;
vector<int> blocks[30]; // 二维数组存储方块编号
map<int, pair<int,int> > pos; // 存储每个编号对应位置
int n, a, b;
void showResult() { // 打印结果
    for (int i = 0; i < n; i ++) {
        printf("%d:", i); // 这里别打印空格
        for (auto p : blocks[i]) printf(" %d", p);
        puts("");
    }
}
void clear(int a) { // 将a上面的都归位（不包含a）
    int ia = pos[a].first, j = pos[a].second + 1;
    for (; j < blocks[ia].size(); j ++) { // 考虑插入当前行
        int k = blocks[ia][j]; // 要删除的值
        blocks[k].push_back(k); // 归位
        pos[k].first = k; pos[k].second = blocks[k].size()-1; // 更新位置
    }
    blocks[ia].erase(blocks[ia].begin()+pos[a].second+1, blocks[ia].end()); // 最后一块删除
}
void move(int a, int b) { // 将a和它上面的方块全移到含有b的柱子上
    int ia = pos[a].first, left = pos[a].second, ib = pos[b].first;
    for (int j = left; j < blocks[ia].size(); j ++) { // 开始移入
        blocks[ib].push_back(blocks[ia][j]); // 移入b所在数组尾部
        pos[blocks[ia][j]].first = ib; // 位置更新
        pos[blocks[ia][j]].second = blocks[ib].size()-1;
    }
    blocks[ia].erase(blocks[ia].begin()+left, blocks[ia].end()); // 一块删除
}
int main() {
    cin >>n;
    for (int i = 0; i < n; i ++) {
        blocks[i].push_back(i);
        pos[i] = {i,0}; // 行列值位置
    }
    while (cin >>op1 && op1 != "quit") {
        cin >>a >>op2 >>b;
        if (pos[a].first == pos[b].first) continue; // 同一叠位置
        if (op1 == "move") clear(a);
        if (op2 == "onto") clear(b);
        move(a,b);
    }
    showResult();
    return 0;
}
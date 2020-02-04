#include<bits/stdc++.h>
using namespace std;
typedef struct Pos{
    int x, y;
    Pos(int _x=0, int _y=0): x(_x), y(_y){} // 默认值表示默认构造函数
    // bool operator < (const Pos& b) const { // map需要排序，必须加const，否则编译报错
    //     if (x == b.x) return y < b.y;
    //     else return x < b.x;
    // }
    friend bool operator < (const Pos& a, const Pos& b) { // map需要排序
        if (a.x == b.x) return a.y < b.y;
        else return a.x < b.x;
    }
} Pos;
map<Pos,Pos> mp1, mp2, mp3; // 当前位置->原始位置，操作模拟的中间变量，原始位置->最终位置
int r, c, op, n, t, num = 0;
string s;
vector<int> cnt(60);
int main() {
    while(scanf("%d %d", &r, &c) == 2 && (r != 0 && c != 0)) {
        scanf("%d", &op);
        if (num != 0) puts("");
        printf("Spreadsheet #%d\n", ++num);
        mp1.clear(); // 清空
        for (int i = 1; i <= r; i ++) { // 初始化：当前位置->原始位置
            for (int j = 1; j <= c; j ++) {
                mp1.insert({Pos{i,j}, Pos{i,j}});
            }
        }
        while(op --) { // 操作
            cin >>s;
            if (s != "EX") { // 不为Exchange
                cin >>n;
                fill(cnt.begin(), cnt.end(), 0); // 初始化
                set<int> rcset; // 要删除/插入的行列集合
                while(n --) {
                    cin >>t; rcset.insert(t);
                    cnt[t] ++; // 统计每个序号出现次数
                }
                for (int i = 1; i < cnt.size(); i ++) cnt[i] += cnt[i-1]; // cnt[i]表示小于等于i的个数，用于计算最终行列号
                for (auto p = mp1.begin(); p != mp1.end(); p ++) { // 遍历每个cell
                    if (s == "DR") { // 删除行
                        if (rcset.find(p->first.x) == rcset.end()) // 未找到，不被删除
                            mp2.insert({{p->first.x - cnt[p->first.x-1],p->first.y}, p->second}); // 插入记录
                    }
                    else if (s == "DC") { // 删除列
                        if (rcset.find(p->first.y) == rcset.end()) // 不被删除
                            mp2.insert({{p->first.x, p->first.y-cnt[p->first.y-1]}, p->second});
                    }
                    else if (s == "IR") { // 插入行
                        mp2.insert({{p->first.x+cnt[p->first.x], p->first.y}, p->second}); // 更新位置
                    }
                    else if (s == "IC") {
                        mp2.insert({{p->first.x,p->first.y+cnt[p->first.y]}, p->second}); // 更新位置
                    }
                }
                mp1 = mp2; mp2.clear(); // 更新当前位置关系
            }
            else {
                int r1,c1,r2,c2;
                cin >>r1 >>c1 >>r2 >>c2;
                swap(mp1[{r1,c1}], mp1[{r2,c2}]); // 交换单元格，考虑交换单元格包含刚插入的
            }
        }
        mp3.clear();
        for (auto p : mp1) mp3.insert({p.second, p.first}); // 逆置：原始位置->最终位置
        cin >>n;
        int x, y;
        while (n --) { // 处理查询
            cin >>x >>y;
            if (mp3.find({x,y}) == mp3.end()) printf("Cell data in (%d,%d) GONE\n", x, y);
            else printf("Cell data in (%d,%d) moved to (%d,%d)\n", x, y, mp3[{x,y}].x, mp3[{x,y}].y);
        }
    }
    return 0;
}
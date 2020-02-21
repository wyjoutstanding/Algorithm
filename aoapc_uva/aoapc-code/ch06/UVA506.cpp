#include<bits/stdc++.h>
using namespace std;
const int maxn=10010; // 最大点数
map<string, int> idMp; // 名字->id
vector<string> name; // 组件名字缓存
map<int,vector<int> > before, after; // 依赖的项目，被项目依赖
vector<int> installed; // 已安装列表
int status[maxn]={0}; // 0：未安装；1：已显示安装；2：隐式安装
int getId(string s) { // 手动分配id
    if (idMp.find(s) == idMp.end()) { // 不存在，手动分配
        idMp[s] = name.size();
        name.push_back(s);
    }
    return idMp[s]; // 已存在，直接返回
}
void List() { // 按安装顺序打印已安装列表
    for (auto s : installed) printf("   %s\n", name[s].c_str());
}
void Install(int i, bool isTop) { // 递归安装
    if (status[i] != 0 && isTop) printf("   %s is already installed.\n", name[i].c_str()); // 已安装
    if (status[i] == 0) { // 未安装
        for (int j : before[i]) Install(j, false); // 递归安装前置依赖
        printf("   Installing %s\n", name[i].c_str());
        status[i] = (isTop ? 1 : 2); // 顶部为显示依赖，其余为隐式依赖
        installed.push_back(i); // 存于安装列表
    } 
}
bool isNeed(int i) { // 判断i是否被依赖
    for (int j : after[i]) if (status[j] != 0) return true; // 遍历后置节点
    return false;
}
void Remove(int r, bool isTop) { // 递归移除
    if (status[r] == 0 && isTop) printf("   %s is not installed.\n", name[r].c_str()); // 未安装
    if (status[r] != 0 && isTop && isNeed(r)) printf("   %s is still needed.\n", name[r].c_str()); // 存在依赖
    if (status[r] != 0 && !isNeed(r)) { // 不被需要
        printf("   Removing %s\n", name[r].c_str());
        status[r] = 0; // 状态置0，未安装
        installed.erase(find(installed.begin(), installed.end(), r)); // 删除安装列表中相应信息
        for (int j : before[r]) if (status[j] == 2) Remove(j, false); // 仅删除隐式依赖
    }
}
int main() {
    string line, cmd, sa, sb;
    while (getline(cin, line)) {
        cout <<line <<endl; // 输出原命令
        if (line[0] == 'E') { // 初始化数据结构
            idMp.clear(); name.clear(); before.clear(); after.clear(); installed.clear();
            memset(status, 0, sizeof(status));
            continue; // 进入下一组数据输入
        }
        stringstream input(line); // 流分割
        input >>cmd; // 命令
        if (cmd[0] == 'L') List(); // 显示已安装列表
        else {
            input >>sa;
            if (cmd[0] == 'D') { // 增加依赖
                while (input >>sb) {
                    before[getId(sa)].push_back(getId(sb)); // sa依赖于sb
                    after[getId(sb)].push_back(getId(sa)); // sb被sa依赖
                }
            }
            else if (cmd[0] == 'I') Install(getId(sa), true); // 安装
            else if (cmd[0] == 'R') Remove(getId(sa), true); // 删除
        }
    }
    return 0;
}
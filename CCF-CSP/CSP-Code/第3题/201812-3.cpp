/*
 * @Author: wuyangjun
 * @Date: 2019-08-28 09:17:24
 * @LastEditTime: 2019-08-28 23:11:20
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct PrefIP {
    unsigned a[4]; // 依次表示a[0]~a[4]
    unsigned len; // 前缀长度
    unsigned left, right; // 匹配ip的左右区间[left,right]
    unsigned val; // IP的低32-len均为0的10进制值
    PrefIP() {
        fill(a, a + 4, 0);
        len = left = right = 0;
        val = 0;
    }
    // friend bool operator < (PrefIP& a, PrefIP& b) { //和优先队列使用方式一样
    //     return (a.val != b.val) ? a.val < b.val : a.len < b.len;
    // }
};
list<PrefIP> _list; // 双向链表表示前缀列表
// 分割IP
int splitIP(const string& s, PrefIP& prefIP) {
    stringstream input(s);
    string tmp;
    int j = 0; // IP分割
    while(getline(input, tmp, '.')) {
        sscanf(tmp.c_str(), "%u", &prefIP.a[j++]); // 转为无符号整数
    }
    return j;
}
void printIP(PrefIP& p) {
    for(int i = 0; i < 4; i ++) {
        printf("%d%s", p.a[i], i == 3 ? "/" : ".");
    }
    printf("%d\n", p.len);
    // printf("%08x %08x %08x\n", p.val, p.left, p.right);
}
// 前缀IP的匹配集区间计算
void matchSet(PrefIP& p) {
    for(int i = 0; i < 4; i ++) { // IP转为10进制
        p.val = p.val * 256 + p.a[i];
    }
    p.left = p.val; // 左区间
    p.right = (p.len == 32) ? p.val : p.val + (0xffffffffu >> p.len); // 右区间 巨坑！！！
}
// 算法模拟
void solve() {
    // 排序，IP值为第一标尺，前缀长度为第二标尺，均从小到大
    _list.sort([](PrefIP& a, PrefIP& b) {return (a.val != b.val) ? a.val < b.val : a.len < b.len;});
    // 从小到大合并
    auto pa = _list.begin(), pb = pa;
    pb ++; // 只能用自增符号
    while(pb != _list.end()) { // 从头开始遍历
        if(pa->left <= pb->left && pa->right >= pb->right) { // b的匹配集包含于a的匹配集
            pb = _list.erase(pb); // 删除pb结点，返回其下一个结点
        }
        else { // 向后移动
            pa = pb;
            pb ++;
        }
    }
    // 同级合并
    pa = pb = _list.begin();
    pb ++;
    while(pb != _list.end()) {
        if(pa->len == pb->len) { // 前缀长度相等
            // a的匹配集合法，低32-len均为0，pa的第32-len位为0即可，&的优先级低于判断==
            if(((pa->val >> (32 - pa->len)) & 1u) == 0) { 
                PrefIP a = *pa; // a的IP与pa相同
                a.len = pa->len - 1; // 前缀长度小1
                matchSet(a); // 重新计算区间
                if(a.left == min(pa->left, pb->left) && a.right == max(pa->right, pb->right)) { // a匹配集等于pa并pb
                    _list.erase(pa); // 删除pa，pb
                    auto it = _list.erase(pb); 
                    pa = pb = _list.insert(it, a); // 在pb后一个结点前插入a
                    if(pa != _list.begin()) -- pa; // a的前面有元素，从前一个开始
                    else ++ pb; // 前面无结点，从当前开始
                    continue;
                }
            }
        }
        // 不同时满足以上3个条件，向后走
        pa = pb;
        ++ pb;
    }
}
int main() {
    int n;
    scanf("%d", &n); 
    getchar(); // 吸收多余换行
    char str[25];
    string s;
    for(int i = 0; i < n; i ++) {
        fgets(str, 25, stdin); // 速度快
        s = str;
        PrefIP prefIP; // 不要定义为全局变量，导致交叉感染
        auto p = s.find('/'); // 找 / 的位置
        if(p == string::npos) { // 不存在/，省略长度型
            prefIP.len = 8 * splitIP(s, prefIP); // 分割IP并计算长度：8的整倍数
        }
        else { // 标准型或省略后缀型
            sscanf(s.c_str() + p + 1, "%u", &prefIP.len); // 长度
            splitIP(s.substr(0, p), prefIP); // 分割IP
        }
        matchSet(prefIP); // 计算匹配集
        _list.push_back(prefIP);
    }
    solve(); // 模拟算法
    // 输出
    for(auto p : _list) {
        printIP(p);
    }
    return 0;
}
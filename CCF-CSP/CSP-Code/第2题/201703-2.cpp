/*
 * @Author: wuyangjun 
 * @Create time: 2019-09-27 23:30:07 
 * @Last Modified time: 2019-09-27 23:30:07 
 * @Gitub: https://github.com/wyjoutstanding 
*/
#include<bits/stdc++.h>
using namespace std;
vector<int> a(1010);
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    a[0]= 0;
    for(int i = 1; i <= n; i ++) a[i] = i;
    int id, disp;
    for(int i = 0; i < m; i ++) {
        scanf("%d %d", &id, &disp);
        auto p = find(a.begin(), a.end(), id);
        p = a.erase(p); // 删除会改变之后的迭代器值
        auto ip = p + disp;
        if(ip >= a.end()) a.push_back(id); // 处理尾部
        else a.insert(ip, id);
    }
    for(int i = 1; i <= n; i ++) printf("%d ", a[i]);
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
typedef long long LL; // 避免移位溢出
typedef struct KAB {
    LL K, A, B;
    KAB(LL _k, LL _A, LL _B) : K(_k), A(_A), B(_B){} // 默认构造
}KAB;
bool cmp(const KAB& a, const KAB& b) { // 按KAB顺序取字典序小者
    if (a.K != b.K) return a.K < b.K; // 取K小
    else if (a.A != b.A) return a.A < b.A; // 取A小
    else return a.B < b.B; // 取B小
}
LL n, Sp, Sq;
int main() {
    while (cin >>n >>Sp >>Sq) {
        vector<KAB> kab; // 存储所有可能值
        for (int i = 0; i < 32; i ++) { // A
            for (int j = 0; j < 32; j ++) { // B
                if ((Sp + (Sp << i)) >= (Sq << j)) { // 公差大于Sq
                    kab.push_back({((Sp*(n-1)+((Sp*(n-1))<<i))>>j)+Sq, i, j}); // 移位优先级低于=-*/
                }
            }
        }
        sort(kab.begin(), kab.end(), cmp); // 排序
        printf("%lld %lld %lld\n", kab[0].K, kab[0].A, kab[0].B); // 第一个即符合条件
    }
    return 0;
}
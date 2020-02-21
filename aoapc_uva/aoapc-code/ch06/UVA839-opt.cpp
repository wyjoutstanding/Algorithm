#include<bits/stdc++.h>
using namespace std;
int T, W;
bool isEqu(int& w) { // 先序读入（隐式建树）；后序判断是否平衡
    int wl, dl, wr, dr;
    scanf("%d %d %d %d", &wl, &dl, &wr, &dr);
    bool b1=true, b2=true; // 判断左右子树是否平衡
    if (wl == 0) b1 = isEqu(wl); // 左子树递归判断
    if (wr == 0) b2 = isEqu(wr); // 右子树递归判断
    w = wl + wr; // 重量为引用，累加影响上一层结果
    return b1 && b2 && (wl * dl == wr * dr); // 左右子树和当前节点均平衡
}
int main() {
    scanf("%d", &T);
    for (int i = 0; i < T; i ++) {
        printf("%s%s", isEqu(W) ? "YES":"NO", i == T-1 ? "\n":"\n\n");
    }
    return 0;
}
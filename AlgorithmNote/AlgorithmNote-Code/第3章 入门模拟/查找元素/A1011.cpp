#include <bits/stdc++.h>
using namespace std;
int main() {
    int res[3] = {-1};
    char name[3] = {'W', 'T', 'L'};
    double tmax, tmp, ans = 1.0;
    for(int i = 0; i < 3; i++) {//3组数据
        tmax = -1;
        for(int j = 0; j < 3; j++) {//选最大
            scanf("%lf", &tmp);
            if(tmp > tmax) {
                tmax = tmp;
                res[i] = j;//下标记录，表示W,T,L
            }
        }
        ans *= tmax;
    }
    ans = (ans * 0.65 - 1) * 2;//最大利润计算公式
//    ans = (double)((int)(ans * 100 + 0.5)) / 100;//四舍五入，保留2位小数
    for(int i = 0; i < 3; i++) {
        printf("%c ", name[res[i]]);
    }
    printf("%.2lf", ans);//四舍五入，保留2位小数
    return 0;
}
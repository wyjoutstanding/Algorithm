#include <cstdio>
int main() {
    int n1;
    scanf("%d", &n1);
    double res[3000] = {0}, ploy1[3000] = {0}, coff;//结果；系数
    int exp;//幂
    for(int i = 0; i < n1; i++) {//多项式1读入保存于ploy1
        scanf("%d %lf", &exp, &coff);
        ploy1[exp] = coff;
    }
    int n2;
    scanf("%d", &n2);
    for(int i = 0; i < n2; i++) {//对于多项式2中的每一项，乘以1中的每一项
        scanf("%d %lf", &exp, &coff);
        for(int j = 0; j < 2001; j++) {//N<=1000，乘法运算相等于幂加法，所以N' <= 2000
            if(ploy1[j] != 0) {
                res[exp + j] += coff * ploy1[j];//幂相加，系数相乘                                
            }
        }
    }

    int cnt = 0;//最保险的计算非零项数
    for(int i = 0; i < 2001; i++) {
        if(res[i] != 0)cnt++;
    }
    printf("%d", cnt);//可能全部抵消
    for(int i = 2001; i >= 0; i--) {//幂次逆序输出
        if(res[i] != 0) printf(" %d %.1lf", i, res[i]);
    }
    return 0;
}
#include <cstdio>
int main() {
	int n, cnt = 0;
	float res[2000] = {0.0};
	scanf("%d", &n);//第一组 
	int exp;//指数 
	float cet;//coefficient：系数 
	for(int i = 0; i < n; i++) {
		scanf("%d %f", &exp, &cet);
		if(res[exp] == 0.0) cnt++;
		res[exp] += cet;
	}
	scanf("%d", &n);//第二组 
	for(int i = 0; i < n; i++) {
		scanf("%d %f", &exp, &cet);
		if(res[exp] == 0.0) cnt++;
		res[exp] += cet;
		if(res[exp] == 0.0) cnt--;//考虑到和第一个多项式相同指数对应的系数正负相消 
	}
	//输出 
	printf("%d", cnt);//相加后的多项式项数，可能相加后为0项，所以不能输出空格 
	for(int i = 1000; i >= 0; i--) {//N <= 1000 && 指数降序输出 
		if(res[i] != 0.0) printf(" %d %.1f", i, res[i]);//保留一位小数 
	}
	return 0;
} 

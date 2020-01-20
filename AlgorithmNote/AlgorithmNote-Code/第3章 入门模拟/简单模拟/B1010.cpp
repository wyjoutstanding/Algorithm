#include <cstdio>
int main() {
	int a, b;
	int res[2003], exp[2003], cnt = 0;
	while(scanf("%d %d", &a, &b) != EOF) {
		if(b == 0)continue;//常数不保存 
		else {
			res[cnt] = a * b;//系数 
			exp[cnt] = b - 1;//指数 
			cnt++;//非零项个数 
		}
	}
	if(cnt == 0)printf("0 0\n");//无非零项输出 0 0 
	for(int i = 0; i < cnt; i++) {
		if(i != cnt - 1) printf("%d %d ", res[i], exp[i]);
		else printf("%d %d\n", res[i], exp[i]);//一行末尾无需多余空格 
	}
	return 0;
}

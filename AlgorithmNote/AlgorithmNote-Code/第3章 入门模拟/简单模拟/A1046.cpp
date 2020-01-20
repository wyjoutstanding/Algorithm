#include <cstdio>
int main() {
	int n;
	scanf("%d", &n);
	int a[n];//存放n个出口距离 
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	int m;
	scanf("%d", &m);//m个测试样例
	int ans[m];
	for(int i = 0; i < m; i++) {
		int e1, e2;
		scanf("%d %d", &e1, &e2);
		int d1 = 0, d2 = 0;//出口组成一个闭环，计算两个方向的距离 
		if(e1 != e2) {//同一个位置为0 
			int j = e1 - 1;
			do {
				d1 += a[j];
				j++;
				j %= n;
			}while(j != e2 - 1);
			
			j = e2 - 1;
			do {
				d2 += a[j];
				j++;
				j %= n;
			}while(j != e1 - 1);
		} 
		ans[i] = (d1 < d2) ? d1 : d2;//取较短 
		printf("%d\n", ans[i]); 
	} 
	return 0;
} 

#include <cstdio>
int main() {
	int n;
	scanf("%d", &n);
	int a[n+2];//存放n个出口距离 
	int dis[n+2] = {0}, sum = 0;//dis[i]：exit1到 i的顺时针下一个exit的距离 
	for(int i = 1; i <= n; i++) {//从1号开始存，后续查询方便 
		scanf("%d", &a[i]);
		sum += a[i];
		dis[i] += sum; 
	}
	int m;
	scanf("%d", &m);//m个测试样例
	int ans[m];
	for(int i = 0; i < m; i++) {
		int e1, e2;
		scanf("%d %d", &e1, &e2);
		int d1 = 0, d2 = 0;//出口组成一个闭环，计算两个方向的距离 
		if(e1 > e2){//保证e1 <= e2 
			int t = e1;
			e1 = e2;
			e2 = t;
		}
		d1 = dis[e2 - 1] - dis[e1 - 1];//顺时针距离 
		d2 = sum - d1; //逆向距离 
		ans[i] = (d1 < d2) ? d1 : d2;//取较短 
		printf("%d\n", ans[i]); 
	} 
	return 0;
} 

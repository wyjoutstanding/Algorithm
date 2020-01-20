#include <cstdio> 
int main() {
	int N, n, m;
	scanf("%d %d", &n, &m);
	N = n;//输出使用 
	int a[n];
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	m %= n; //需考虑n < m
	if(m != 0) {//m==0，必须判断，否则浮点数报错 
		if(n % m != 0) {//非整除:  
		int i = 0, k, pre, pcur = a[0];
			while(N--) {
				k = (i + m) % n;//i最终位置的下标 
				pre = pcur;
				pcur = a[k];
				a[k] = pre;
				i = k; 
			}
		}
		else {//整除 
			for(int i = 0; i < m; i++) {//m组轮换 
				int w = n / m;//每组内的元素个数 
				int pre, pcur = a[i];
				int j = i, k;
				while(w--) {
					k = (j + m) % n;
					pre = pcur;
					pcur = a[k];
					a[k] = pre;
					j = k;
				}
			}
		}
	}


	for(int i = 0; i < n - 1; i++) {
		printf("%d ", a[i]);
	}
	printf("%d", a[n-1]);
	
	return 0;
} 

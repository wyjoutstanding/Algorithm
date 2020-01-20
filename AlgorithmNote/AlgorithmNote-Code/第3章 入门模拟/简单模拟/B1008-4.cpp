#include <cstdio> 
//最大公约数 
int gcd(int a, int b) {
	if(b == 0) return a;
	else return gcd(b, a % b);
}
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
        int d = gcd(n, m);
		for(int i = 0; i < d; i++) {//至少需要遍历的数目
			int w = n / d;//每组内的元素个数 
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
	for(int i = 0; i < n - 1; i++) {
		printf("%d ", a[i]);
	}
	printf("%d", a[n-1]);
	
	return 0;
} 

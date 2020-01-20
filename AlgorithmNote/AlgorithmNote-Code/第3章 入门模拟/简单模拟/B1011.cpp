#include <cstdio> 
int main() {
	int n, cnt = 0;
	long long a, b, c;
	scanf("%d",&n);
	while(n > 0) {
		n--;
		cnt++;//计数 
		scanf("%lld %lld %lld", &a, &b, &c);//long long 格式为 %lld 
		if(a + b > c) printf("Case #%d: true\n", cnt);
		else printf("Case #%d: false\n", cnt);
	}
	return 0;
} 

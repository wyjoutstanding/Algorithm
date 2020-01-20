#include <cstdio> 
int main() {
	int n, cnt = 0;
	scanf("%d",&n);
	while(n > 1) {
		cnt++;
		if(n % 2 == 0)	n /= 2;
		else n = (3*n + 1) / 2;
	}
	printf("%d", cnt);
	return 0;
} 

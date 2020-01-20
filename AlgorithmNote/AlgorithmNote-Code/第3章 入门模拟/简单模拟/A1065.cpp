#include <cstdio>
int main() {
	int T, cnt = 0;
	scanf("%d", &T);
	while(T--) {
		long long a, b, c, tmp;
		scanf("%lld %lld %lld", &a, &b, &c);
		tmp = a + b;//必须强转 
		bool flag = false;
		if(a > 0 && b > 0 && tmp < 0) flag = true;//正上溢 
		else if(a < 0 && b < 0 && tmp >= 0) flag = false;//负下溢 
		else if(tmp > c) flag = true;//正常 
		else flag = false; 
		
		if(flag == true) printf("Case #%d: true\n", ++cnt);
		else printf("Case #%d: false\n", ++cnt); 
	}
	return 0;
} 

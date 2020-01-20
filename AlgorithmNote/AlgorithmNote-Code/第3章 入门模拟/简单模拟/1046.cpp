#include <cstdio> 
int main() {
	int n, cnta = 0, cntb = 0;
	scanf("%d",&n);
	int a1, a2, b1, b2;
	while(n--) {
		scanf("%d %d %d %d", &a1, &a2, &b1, &b2);
		if(a2 == b2) continue;//Í¬ÊäÓ® 
		else {
			if(a2 == a1 + b1) cntb++;//¼×Ó® 
			else if(b2 == a1 + b1) cnta++;//ÒÒÓ® 
		}
	}
	printf("%d %d\n", cnta, cntb); 
	return 0;
} 

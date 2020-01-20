#include <cstdio>
#include <algorithm> 
using namespace std;
int main() {
	int n, a;
	scanf("%d", &n);
	int cnt[5] = {0};//计算A1~A5各类的个数 
	int ans[5] = {0};//答案放置 
	ans[4] = -1;//便于计算最大值 
	for(int i = 0; i < n; i++) {
		scanf("%d", &a);
		switch(a % 5) {//根据模5余数分为5类 
			case 0: 
				if(a % 2 == 0){
					ans[0] += a;
					cnt[0]++;
				}
				break;
			case 1:
				cnt[1]++;
				if(cnt[1] % 2 == 0)a = -a;//交错求和 
				ans[1] += a;
				break;
			case 2:
				cnt[2]++;
				break;
			case 3:
				cnt[3]++;
				ans[3] += a;
				break;
			case 4:
				cnt[4]++;
				ans[4] = max(ans[4], a);//最大值 
				break;	
		}
	}
	ans[2] = cnt[2];//存储答案 
	//输出 
	for(int i = 0; i < 4; i++){
		if(cnt[i] == 0)	printf("N ");//无满足的项输出N 
		else {
			if(i == 3) printf("%.1f ", (float)ans[i] / cnt[i]);//平均数保留一位小数 
			else printf("%d ", ans[i]);
		}
	}
	if(cnt[4] == 0)printf("N");//最后一位后无空格 
	else printf("%d", ans[4]);
	
	return 0;
} 

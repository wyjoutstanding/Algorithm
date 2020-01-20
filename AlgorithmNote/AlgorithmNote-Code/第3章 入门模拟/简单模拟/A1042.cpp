#include <cstdio>
int main() {
	int T;//洗牌次数 
	scanf("%d", &T);
	int a[54],ans[54];
	for(int i = 0; i < 54; i++) {
		scanf("%d", &a[i]);//存放洗牌顺序规则，从0开始 
	}
	//洗牌 
	for(int i = 0; i < 54; i++) {//54张牌 
		int k = i;
		for(int j = 0; j < T; j++) {//对第i张牌洗T次 
			k = a[k] - 1;//最终位置下标，数组从0开始，需减一 
		}
		ans[k] = i;//第i张填入结果数组 
	}
	for(int i = 0; i < 54; i++) {
		char tc;
		switch(ans[i] / 13) {
			case 0: tc = 'S'; break;
			case 1: tc = 'H'; break;
			case 2: tc = 'C'; break;
			case 3: tc = 'D'; break;
			case 4: tc = 'J'; break;//大小王别漏 
		}
		if(i != 53)	printf("%c%d ", tc, ans[i] % 13 + 1);//一行的末尾不能带多余空格 
		else printf("%c%d", tc, ans[i] % 13 + 1);//数组从0开始，需加1 
	} 
	return 0;
} 

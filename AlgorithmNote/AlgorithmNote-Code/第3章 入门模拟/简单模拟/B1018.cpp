#include <cstdio>
#include <map>
using namespace std;
int main() {
	int n;
	scanf("%d", &n);
	char ca, cb;//甲乙手势 
	int win, draw, fail;//甲的胜平负次数 
	win = draw = fail = 0; 
	map<char, int> mp[2];//记录甲乙胜利的手势策略 
	for(int i = 0; i < 2; i++) {
		mp[i]['J'] = 0;
		mp[i]['C'] = 0;
		mp[i]['B'] = 0;
	}
	for(int i = 0; i < n; i++) {
		getchar();//吸收回车,否则scanf会接受回车 
		scanf("%c %c", &ca, &cb);
		if(ca == cb)	draw++;//平局 
		else {//胜负局 
			switch(ca){//甲手势 
				case 'J'://剪刀 
					if(cb == 'B') {//甲赢 
						win++;
						mp[0]['J']++;
					}
					else {//甲输 
						fail++;
						mp[1]['C']++;
					}
					break;
				case 'C'://锤子 
					if(cb == 'J') {
						win++;
						mp[0]['C']++;
					}
					else {
						fail++;
						mp[1]['B']++;
					}
					break;
				case 'B'://布 
					if(cb == 'C') {
						win++;
						mp[0]['B']++;
					}
					else {
						fail++;
						mp[1]['J']++;
					}
					break;
			}
		} 
	}
	
	//输出胜出次数最多的手势，存在多个则输出字典序最小 
	ca = 'B';
	if(mp[0][ca] < mp[0]['C']) ca = 'C';
	if(mp[0][ca] < mp[0]['J']) ca = 'J';
	
	cb = 'B';
	if(mp[1][cb] < mp[1]['C']) cb = 'C';
	if(mp[1][cb] < mp[1]['J']) cb = 'J';
	
	printf("%d %d %d\n", win, draw, fail);
	printf("%d %d %d\n", fail, draw, win);
	printf("%c %c\n", ca, cb); 
	return 0;
} 

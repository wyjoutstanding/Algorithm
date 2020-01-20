/*
 * @Author: wuyangjun 
 * @Create time: 2019-12-15 01:04:39 
 * @Last Modified time: 2019-12-15 01:04:39 
 * @Gitub: https://github.com/wyjoutstanding 
*/
#include <bits/stdc++.h>
using namespace std;
struct pixel { // 像素点
	int r, g, b;
};
vector<vector<pixel>> img, imgavr; // 原图像；小块平均值
int m, n, p, q;
string backColor = "\x1b[48;2;R;G;Bm", defaultColor = "\x1b[0m"; // 背景色；默认色
// 打印转义序列，打印默认序列时可传递任意rgb值
void output(string str, pixel p) {
	for (auto c : str) {
		int val = -1;
		char rgb[20]; string tmp;
		switch (c) {
			case 'R': val = p.r; break;
			case 'G': val = p.g; break;
			case 'B': val = p.b; break;
			default: printf("\\x%02X", c);
		}
		if (val != -1) { // 背景色序列
			sprintf(rgb, "%d", val); // 直接转为10进制字符串 !!!!不需要转为16进制再输出字符串！！！
			tmp = rgb;
			for (auto v : tmp) { // 逐个打印
				printf("\\x%02X", v);
			}
		}
	}
}
int main() {
	scanf("%d %d %d %d", &m, &n, &p, &q);
	swap(m,n); swap(p,q); // m是宽，n是高，分别对应(列，行)；因此这里做个转换
	char c_rgb[1000];
	string rgb;
	pixel tmp;
	// 1.读入并处理字符串为整型
	for (int i = 0; i < m; i ++) {
		vector<pixel> a; img.push_back(a); // 初始化
		for (int j = 0; j < n; j ++) {
			scanf("%s", c_rgb);
			rgb = c_rgb;
			if (rgb.size() == 2) rgb += string(5, rgb.back()); // #a -> #aaaaaa
			else if (rgb.size() == 4) { // #abc -> #aabbcc
				rgb = "#" + string(2, rgb[1]) + string(2, rgb[2]) + string(2, rgb[3]);
			}
			// 16进制字符串转换为10进制数值
			tmp.r = stoi(rgb.substr(1,2), 0, 16);
			tmp.g = stoi(rgb.substr(3,2), 0, 16);
			tmp.b = stoi(rgb.substr(5,2), 0, 16);
			img[i].push_back(tmp);
		}
	}
	int m1 = m / p, n1 = n / q;
	// 2.分块遍历（每块大小：p*q)，计算每小块的平均值
	for (int i = 0; i < m1; i ++) {
		vector<pixel> a;
		imgavr.push_back(a);
		for (int j = 0; j < n1; j ++) {
			// 块内遍历（每块大小：p*q)
			tmp = {0,0,0};
			for (int i2 = 0;  i2 < p; i2 ++) {
				for (int j2 = 0; j2 < q; j2 ++) {
					int x = i * p + i2; // 平移
					int y = j * q + j2;
					// 计算块内总和
					tmp.r += img[x][y].r;
					tmp.g += img[x][y].g;
					tmp.b += img[x][y].b;
				}
			}
			tmp.r /= p*q; // 平均值
			tmp.g /= p*q;
			tmp.b /= p*q;
			imgavr[i].push_back(tmp);
		}
	}
    // 3.主控程序，遍历每小块并按要求输出
	pixel pre = {0,0,0}; // 前一次的背景色
	for (auto imgVec : imgavr) { // 每行
		for (auto block : imgVec) { // 每列
			if (block.r != pre.r || block.g != pre.g || block.b != pre.b) { // 与之前背景色不同
				if (block.r == 0 && block.g == 0 && block.b == 0) { // 是默认背景色
					output(defaultColor, pixel{0,0,0});
				}
				else output(backColor, block);
			}
			pre = block; // 更新背景色
			printf("\\x20"); // 空格
		}
		if (pre.r != 0 || pre.g != 0 || pre.b != 0) {
			pre = {0,0,0}; // 更新背景色
			output(defaultColor, pixel{0,0,0}); // 一行结尾非默认背景色
		}
		printf("\\x0A"); // 换行
		
	}
	return 0;
}
/*
=======
2 3
2 1
#101010
#010101
#0
#0
#1
#1
输出：
\x1B\x5B\x34\x38\x3B\x32\x3B\x38\x3B\x38\x3B\x38\x6D\x20\x1B\x5B\x30\x6D\x0A\x20\x0A\x1B\x5B\x34\x38\x3B\x32\x3B\x31\x37\x3B\x31\x37\x3B\x31\x37\x6D\x20\x1B\x5B\x30\x6D\x0A
========
2 2
1 1
#010101
#0
#010101
#010101
输出：
\x1B\x5B\x34\x38\x3B\x32\x3B\x31\x3B\x31\x3B\x31\x6D\x20\x1B\x5B\x30\x6D\x20\x0A\x1B\x5B\x34\x38\x3B\x32\x3B\x31\x3B\x31\x3B\x31\x6D\x20\x20\x1B\x5B\x30\x6D\x0A
=======
2 2
2 1
#111111
#0
#000000
#111
输出：
\x1B\x5B\x34\x38\x3B\x32\x3B\x38\x3B\x38\x3B\x38\x6D\x20\x1B\x5B\x30\x6D\x0A\x1B\x5B\x34\x38\x3B\x32\x3B\x38\x3B\x38\x3B\x38\x6D\x20\x1B\x5B\x30\x6D\x0A
*/
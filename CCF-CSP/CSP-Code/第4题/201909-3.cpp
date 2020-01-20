#include <bits/stdc++.h>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
//#include <stringstream>
using namespace std;
struct pixel
{ // 像素点
	int r, g, b;
	//	pixel(int _r, int _g, int _b): r(_r), g(_g), b(_b){} // 构造函数
	// 可以使用默认构造函数
};
vector<vector<pixel>> img, imgavr; // 图像
int m = 10, n = 10, p = 1, q = 1;
string backColor = "\x1b[48;2;R;G;Bm", defaultColor = "\x1b[0m";
void output(string str, pixel p)
{
	for (auto c : str) {
		int val = -1;
		char rgb[20];
		string tmp;
		switch (c) {
			case 'R':
				val = p.r; break;
			case 'G':
				val = p.g; break;
			case 'B':
				val = p.b; break;
			default:
				printf("\\x%02X", c);
		}
		if (val != -1) {
			sprintf(rgb, "%d", val); // 转为10进制字符串
			// printf("\n==%d %s\n", val, rgb);
			tmp = rgb;
			for (auto v : tmp)
			{
				printf("\\x%02X", v);
			}
		}
	}
}
int main()
{
	scanf("%d %d %d %d", &m, &n, &p, &q);
	swap(m,n); swap(p,q);
	// getchar();
	char c_rgb[1000];
	string rgb;
	pixel tmp;
	// 读入并处理为整型
	for (int i = 0; i < m; i ++) {
		vector<pixel> a; // 初始化
		img.push_back(a);
		for (int j = 0; j < n; j ++) {
			scanf("%s", c_rgb);
			rgb = c_rgb;
			// printf("rgb:%s size:%d\n", rgb.c_str(), rgb.size());
			if (rgb.size() == 2) rgb += string(5, rgb.back()); // #a -> #aaaaaa
			else if (rgb.size() == 4) { // #abc -> #aabbcc
				string rgbTmp = "#";
				rgbTmp += string(2, rgb[1]) + string(2, rgb[2]) + string(2, rgb[3]);
				rgb = rgbTmp;
			}
			// printf("2--rgb:%s size:%d\n", rgb.c_str(), rgb.size());
			// 16进制字符串转换为10进制数值
			tmp.r = stoi(rgb.substr(1,2), 0, 16);
			tmp.g = stoi(rgb.substr(3,2), 0, 16);
			tmp.b = stoi(rgb.substr(5,2), 0, 16);
			img[i].push_back(tmp);
			// printf("r:%d g:%d b:%d\n", tmp.r, tmp.g, tmp.b);
		}
		// for (int j = 0; j < img.back().size(); j ++) {
		// 	printf("%d %d %d\n", img[i][j].r, img[i][j].g, img[i][j].b);
		// }
		// printf("\n");
	}
	int m1 = m / p, n1 = n / q;
	// 分块遍历（每块大小：p*q)
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
		// for (int j = 0; j < imgavr.back().size(); j ++) {
		// 	printf("avr:%d %d %d\n", imgavr[i][j].r, imgavr[i][j].g, imgavr[i][j].b);
		// }
		// printf("\n");
	}

	pixel pre = {0,0,0};
	for (auto imgVec : imgavr) { // 每行
		for (auto block : imgVec) { // 每列
			if (block.r != pre.r || block.g != pre.g || block.b != pre.b) { // 与之前背景色不同
				if (block.r == 0 && block.g == 0 && block.b == 0) { // 是默认背景色
					output(defaultColor, pixel{0,0,0});
				}
				else output(backColor, block);
			}
			pre = block;
			printf("\\x20"); // 空格
		}
		if (pre.r != 0 || pre.g != 0 || pre.b != 0) {
			pre = {0,0,0};
			output(defaultColor, pixel{0,0,0}); // 一行结尾非默认背景色
		}
		printf("\\x0A"); // 换行
		
	}
	return 0;
}
/*
2 1
1 1
#101010
#010101
=======
2 3
2 1
#101010
#010101
#0
#0
#1
#1
========
2 2
1 1
#010101
#0
#010101
#010101
=======
1 1
1 1
#010203
=======
2 2
1 2
#111111
#0
#000000
#111
=======
2 2
2 1
#111111
#0
#000000
#111
*/
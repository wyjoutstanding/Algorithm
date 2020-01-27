| 例题3-1|UVA272|[ Tex Quotes](#例题3-1-uva272-tex-quotes)|  | |
| 例题3-2|UVA10082|[ WERTYU](#例题3-2-uva10082-wertyu)| | |
| 例题3-3|UVA401|[ Palindromes](#例题3-3-uva401-palindromes)| | |
| 例题3-4|UVA340|[ Master-Mind Hints ](#例题3-4-uva340-master-mind-hints-)| | |
| 例题3-5|UVA1583|[ Digit Generator](#例题3-5-uva1583-digit-generator)| | |
| 例题3-6|UVA1584|[ Circular Sequence](#例题3-6-uva1584-circular-sequence)| | |
| 习题3-1|UVA1585|[ Score](#习题3-1-uva1585-score)| | |
| 习题3-2|UVA1586|[ Molar mass](#习题3-2-uva1586-molar-mass)| | |
| 习题3-3|UVA1225|[ Digit Counting](#习题3-3-uva1225-digit-counting)| | |
| 习题3-4|UVA455|[ Periodic Strings](#习题3-4-uva455-periodic-strings)| | |
| 习题3-5|UVA227|[ Puzzle](#习题3-5-uva227-puzzle)| | |
| 习题3-6|UVA232|[ Crossword Answers](#习题3-6-uva232-crossword-answers)| | |
| 习题3-7|UVA1368|[ DNA Consensus String](#习题3-7-uva1368-dna-consensus-string)| | |
| 习题3-8|UVA202|[ Repeating Decimals](#习题3-8-uva202-repeating-decimals)| | |
| 习题3-9|UVA10340|[ All in All](#习题3-9-uva10340-all-in-all)| | |
| 习题3-10|UVA1587|[ Box](#习题3-10-uva1587-box)| | |
| 习题3-11|UVA1588|[ Kickdown](#习题3-11-uva1588-kickdown)| | |
| 习题3-12|UVA11809|[ Floating-Point Numbers](#习题3-12-uva11809-floating-point-numbers)| | |
-==========

# 《算法竞赛入门经典第2版》题解系列 第三章 数组和字符串

## 例题3-1 UVA272 Tex Quotes

### 题目大意

将成对的左右引号转换为指定类型。

### 思路分析

使用一个布尔或整型变量cnt标记当前引号为左或右引号

由于使用EOF作为结束标记，两种技巧：

+ `scanf("%c",&ch)!=EOF`
+ `(ch=getchar())!=EOF`

### AC代码（C++11）

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    char ch;
    int cnt = 0; // 控制左右括号 (:0  ):1
    while(scanf("%c", &ch) != EOF) { // 两种输入均可
    // while((ch = getchar()) != EOF) {
        if (ch == '"') {
            if (cnt == 0) {
                printf("``");
                cnt = 1;
            }
            else {
                printf("''");
                cnt = 0;
            }
        } 
        else printf("%c", ch);
    }
    return 0;
}
```

### AC代码（C++11，优化版）

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    char ch;
    int cnt = 0;
    while(scanf("%c", &ch) != EOF) { // EOF = -1，不等于0
        if (ch == '"') {
            printf("%s", (cnt == 0) ? "``" : "''"); // ?:简洁代码
            cnt = !cnt; // 完成0和1转换
        }
        else printf("%c", ch);
    }
    return 0;
}
```



## 例题3-2 UVA10082 WERTYU

### 思路分析

根据题意可不考虑`QAZ`和无法显示的字符（TAB，Enter等），用string存放键盘键位，使用getline按行读入，非空则遍历该行字符串，若遇到空格，直接输出，否则，在string中查找相应键位，输出前一位字符。

+ 注意使用getline需要额外输出换行符
+ 若用getchar按字符读入则无需多余输出换行符

### AC代码（C++11）

```cpp
#include<bits/stdc++.h>
using namespace std;
string keyboard = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./", s;
int main() {
    while(getline(cin, s) && !s.empty()) {
        for (char ch : s) {
            if (ch == ' ') printf(" ");
            else printf("%c", keyboard[keyboard.find(ch)-1]);
        }
        printf("\n"); // 换行记录
    }
    return 0;
}
```

## 例题3-3 UVA401 Palindromes

### 思路分析

判断是否为回文串和镜像串，根据二者组合输出相应提示信息。

+ 回文串：从正反读相同，如`ABCBA`
+ 镜像串：将源串S的每个字符转为相应镜像字符后得到新字符串Srev，若Srev和原串S互为回文串，则S为镜像串（注意：若某个字符的镜像字符为空，则肯定不满足条件）
+ 可用哈希数组存储字符映射关系

+ 每一行输出需要两个换行符

### AC代码（C++11）

```cpp
#include<bits/stdc++.h>
using namespace std;
string rev = "A   3  HIL JM O   2TUVWXY51SE Z  8 ", s; // 镜像哈希串
char *msg[] = {" -- is not a palindrome.", " -- is a regular palindrome.", " -- is a mirrored string.", " -- is a mirrored palindrome."};
char toRev(char ch) {
    if (isalpha(ch)) return rev[ch - 'A'];
    else return rev[ch - '1' + 26];
}
int main() {
    int p, m;
    while(getline(cin, s) && !s.empty()) {
        p = 1; m = 1; // 分别表示回文和镜像串
        for (int i = 0; i <= s.size() / 2; i ++) {
            if (s[i] != s[s.size() - i - 1]) p = 0; // 回文判断
            if (toRev(s[i]) != s[s.size() - i -1]) m = 0; // 镜像为空直接不符合！！！
        }
        printf("%s%s\n\n", s.c_str(), msg[m*2+p]); // 多一个空行！！！
    }
    return 0;
}
```

## 例题3-4 UVA340 Master-Mind Hints 

### 题目分析

英文题面又臭又长，难以读懂，重新叙述下题意：

给定原答案序列l1和猜测序列l2，输出（A,B）

+ A：l1和l2中满足同一位置上数字相同的**总对数**，如`12334、21334`有3个位置满足，即`334`
+ B：l1和l2中均存在，但位置不同的**总对数**，如上面例子，有2个位置满足，即`12 与 21`

明确问题域后，解题变得水到渠成，注意是计算对数，即**避免重复计算**。

在一次遍历中，可轻易计算出A，对于B，可用哈希表记录两个序列中不符合A条件的元素出现次数，最后再取两个序列中出现次数少者作为B的贡献值，累加即可。

### AC代码（C++11，阅读理解）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, cnta = 0, cntb = 0, num = 0;
vector<int> l1(1010), l2(1010), vl1(10), vl2(10);
int main() {
    while(scanf("%d", &n) == 1 && n != 0) {
        for (int i = 0; i < n; i ++) scanf("%d", &l1[i]); // 原答案序列
        printf("Game %d:\n", ++num);
        while (true) {
            for (int i = 0; i < n; i ++) scanf("%d", &l2[i]); // 猜测序列
            if (l2[0] == 0) break; // 读到0开头结束
            cnta = cntb = 0; // 初始化
            fill(vl1.begin(), vl1.end(), 0);
            fill(vl2.begin(), vl2.end(), 0);
            for (int i = 0; i < n; i ++) { // 第一次扫描
                if (l1[i] == l2[i]) cnta ++; // 统计同位置个数
                else { // 非同位置出现次数，哈希表实现
                    vl1[l1[i]] ++;
                    vl2[l2[i]] ++;
                }
            }
            for (int i = 0; i < 10; i ++) { // 非同位置取小者
                cntb += min(vl1[i], vl2[i]);
            }
            printf("    (%d,%d)\n", cnta, cntb); // 4个空格/Tab
        }
    }
    return 0;
}
```

## 例题3-5 UVA1583 Digit Generator

### 思路分析

给定整数N，求N的最小生成元M，不存在则输出0。

+ 最小生成元：M的各数位之和+自身值=N，比如M=123=》1+2+3+123=129=N

若能找到逆向求解的规律自然是好，找不到就从1-100000暴力枚举，但效率太低，有两种优化方式

+ 缩小范围：因为N最大不超过100000，每个数位最大为9，因此，各数位之和不超过54，因此可从[N-54,N]枚举，或者再精细化，可从[N-9*len(N)，N]枚举。
+ 哈希表：将1-100000的所有生成元计算出来，存于表中，到时候直接查询即可，适用于查询条数大的情况

### AC代码（C++11，范围缩小/逆向构建哈希表）

```cpp
#include<bits/stdc++.h>
using namespace std;
int T, n, len, sum = 0;
string s;
int main() {
    scanf("%d", &T);
    for (int i = 0; i < T; i ++) {
        scanf("%d", &n);
        len = to_string(n).size(); // n的位数，数位之和最大为9*len(n)
        for (int j = n - len*9; j <= n; j ++) { // 确定枚举范围[n-len*9, n]
            sum = j;
            s = to_string(j);
            for (auto ch : s) sum += (ch - '0'); // 数位之和累加
            if (sum == n) {
                printf("%d\n", j);
                break;
            }
            if (j == n) printf("0\n");
        }
    }
    return 0;
}
```

## 例题3-6 UVA1584 Circular Sequence

### 思路分析

给定一个环状的字符串序列，求字典序最小的线性序列。具体思路如下：

枚举给定序列的每个字符i，利用string类拼接得到以i开头的新字符串s，每次取较小者（类似于给定一个序列求最小值）

### AC代码（C++11，string)

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    string str, ans, s;
    int n;
    cin >>n;
    while(n --) {
        cin >>str;
        ans = str;
        for (int i = 1; i < str.size(); i ++) { // 遍历每一种情况，i表示开始下标
            s = str.substr(i) + str.substr(0, i); // 拼接循环字符串
            ans = min(ans, s); // 取小，string类对<重载
        }
        cout <<ans <<endl;
    }
    return 0;
}
```

## 习题3-1 UVA1585 Score

### 思路分析

遍历输入字符串，用cnt记录已连续的O个数，ans记录总和，若当前字符为X，cnt=0；否则ans+=cnt

### AC代码（C++11）

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int n, ans, cnt;
    string s;
    scanf("%d", &n);
    while(n --) {
        cin >>s;
        ans = cnt = 0;
        for (auto ch : s) {
            if (ch == 'X') cnt = 0;
            else {
                cnt ++;
                ans += cnt;
            }
        }
        printf("%d\n", ans);
        
    }
    return 0;
}
```

## 习题3-2 UVA1586 Molar mass

### 思路分析

给定化学式字符串，统计每个分子的个数，乘以对应摩尔质量，累加即可，输出精确到3位小数，无四舍五入要求。

### AC代码（C++11，字符串处理）

```cpp
#include<bits/stdc++.h>
using namespace std;
map<char, int> mp{{'C',0}, {'H',1}, {'O',2}, {'N',3}}; // 便于循环处理
double mass[4] = {12.01, 1.008, 16.00, 14.01}, ans = 0;
int n, num[4] = {0}; // 统计个数
string str, s;
char pre; // 记录有明确数量的前置符号
int main() {
    scanf("%d", &n);
    while(n --) {
        cin >>str;
        fill(num, num+4, 0); // 初始化
        pre = str[0]; // 记录前一个元素
        int i = 0;
        while(i < str.size()) {
            s.clear();
            while (i < str.size() && isdigit(str[i])) s += str[i++]; // 计算数值
            if (!s.empty()) {
                num[mp[pre]] += stoi(s);
                i --; // 数值计算多后移一位
            }
            else {
                if (i + 1 == str.size() || !isdigit(str[i+1])) { // 符号后无明确数值
                    num[mp[str[i]]] += 1;
                }
                else pre = str[i];
            }
            i ++; // 移动标签
        }
        ans = 0;
        for (int i = 0; i < 4; i ++) { // 计算结果
            ans += (double)num[i] * mass[i];
        }
        printf("%.3lf\n", ans);
    }
    return 0;
}
```

## 习题3-3 UVA1225 Digit Counting

### 思路分析

给定正整数N，将[1,N]的数字顺序拼接为新字符串s，统计s中0-9出现的次数。

哈希表计数即可

+ 注意每行最后不允许有多余空格

### AC代码（C++11，打表）

```cpp
#include<bits/stdc++.h>
using namespace std;
int num[10] = {0};
int main() {
    int T, n;
    string s;
    scanf("%d", &T);
    while(T --) {
        scanf("%d", &n);
        fill(num, num + 10, 0);
        for (int i = 1; i <= n; i ++) {
            s = to_string(i);
            for (auto ch : s) num[ch - '0'] ++;
        }
        for (int i = 0; i < 10; i ++) {
            printf("%d%s", num[i], (i == 9) ? "\n" : " ");
        }
    }
    return 0;
}
```

## 习题3-4 UVA455 Periodic Strings

### 思路分析

给定一个字符串s，求最小的周期串长度。

周期串长度i一定位于[1,len(s)/2]中，且len(s)能够整除i，因此，从1开始枚举判断即可。

### 注意点

+ 输入若用scanf，需getchar吸收多余字符
+ 输出时两行结果间需打印空行，而最后一行只需一个换行即可，无需多余空行

### AC代码（C++11，周期串）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, ans;
bool flag = true, flag2 = false;
string s;
int main() {
    scanf("%d", &n);
    getchar();
    while(n --) {
        cin >>s;
        ans = s.size(); // 默认结果
        flag2 = false;
        for (int i = 1; i <= s.size() / 2; i ++) { // 枚举所有可能长度 
            if (s.size() % i == 0) {
                flag = true;
                for (int j = i; j <= s.size() - i; j += i) { // 比较长度为i的所有子串是否相同
                    if (s.substr(0, i) != s.substr(j, i)) {
                        flag = false;
                        break;
                    }
                }
                if (flag) { // 找到符合的周期串长度
                    ans = i;
                    flag2 = true;
                }
            }
            if (flag2) break;
        }
        printf("%d%s", ans, (n == 0) ? "\n" : "\n\n"); // 相邻两个输出间需输出空行，最后一行不用
    }
    return 0;
}
```

## 习题3-5 UVA227 Puzzle

### 思路分析

给定一个5*5的字母拼图（A-X），包含一个空格，再给定移动序列，以0表示结束，求最终的拼图，若非法则输出相应提示信息。

读入拼图后，先找出空格位置，再根据移动序列移动即可。

### 注意点

+ 输入时getline可读入换行并丢弃它，cin遇到换行立即停止，不会丢弃，即下一个读取依旧是换行
+ 输出时两个puzzle间需有空行，最后一个puzzle不需要
+ 输入样例测试时，直接复制测试样例会导致第五列空格缺失，需自己补上

### AC代码（C++11，简单模拟，复杂输入输出）

```cpp
#include<bits/stdc++.h>
using namespace std;
string puzzle[5], s;
int cnt = 0, x, y, x2, y2, dict[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}}; // 上下左右偏移
map<char, int> mp{{'A',0}, {'B',1}, {'L',2}, {'R',3}}; // 字符映射到数字
bool isLegal = true, isOver = false; // 当前拼图是否有合法结果，是否结束
int main() {
    while(getline(cin,puzzle[0])) {
        if (puzzle[0][0] == 'Z') break;
        for (int i = 1; i < 5; i ++) getline(cin,puzzle[i]); // getline可读入空格
        for (int i = 0; i < 5; i ++) { // 找空格位置
            for (int j = 0; j < 5; j ++) { // 寻找空格坐标
                if(puzzle[i][j] == ' ') {
                    x = i; y = j;
                    break;
                }
            }
        }
        isOver = false; isLegal = true; // 初始化
        while(true) {
            cin >>s; getchar(); // 注意吸收换行
            for (auto ch : s) {
                if (ch == '0') { // 当前拼图结束
                    isOver = true; // 标记结束
                    if (cnt >= 1) printf("\n"); // 两个输出之间需有空行 
                    printf("Puzzle #%d:\n", ++cnt);
                    if (isLegal) { // 合法输出
                        for (int i = 0; i < 5; i ++) {
                            for (int j = 0; j < 5; j ++) {
                                printf("%c%c", puzzle[i][j], (j == 4) ? '\n' : ' ');
                            }
                        }
                    }
                    else printf("This puzzle has no final configuration.\n");
                }
                else {
                    x2 = x + dict[mp[ch]][0];
                    y2 = y + dict[mp[ch]][1];
                    if (x2 >= 0 && x2 < 5 && y2 >= 0 && y2 < 5) { // 是否合法
                        swap(puzzle[x][y], puzzle[x2][y2]); // 交换
                        x = x2; y = y2; // 更新x，y
                    }
                    else isLegal = false; // 非法
                }
            }
            if (isOver) break; // 跳出循环
        }
    }
    return 0;
}
```

## 习题3-6 UVA232 Crossword Answers

### 思路分析

给定N*M的网格，有黑白两种格子，从上到下，从左到右依次对左侧和上侧没有白格子的白格子进行标号，具体如下：

+ 第一行和第一列的白格子均编号
+ 其余行列，若一个白格子的左侧或上侧存在黑格子，则对其进行编号

编号完成后，分别按行和按列输出相应子串，子串以有编号的白格子开始，遇见黑格子或行列则结束。

因此，可用`string数组`存放网格，一遍扫描后计算出存在编号的白格子

+ 按行遍历输出即可完成按行输出子串
+ 按列遍历则需将子串先存放与哈希数组，最后再按顺序输出

### 注意点

+ 输出标号格式：右对齐，宽度为3，即`printf("%3d",..)`
+ 两个相邻puzzle间需多输出一个空行，最后一个puzzle不需要
+ 当puzzle的行或列为空时，一样得输出`Across Down`

### AC代码（C++11，字符串处理，坑人输出）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 11
string puzzle[MAXN];
int n, m, cnt = 0, num = 0, now, id[MAXN][MAXN] = {0}; // 编号
int main() {
    while(scanf("%d", &n) == 1 && n != 0) {
        scanf("%d", &m);
        if (num != 0) printf("\n"); // 仅两个puzzle间需空行
        printf("puzzle #%d:\n", ++num); // puzzle标号
        cnt = 0; // 统计每个有编号的格子
        printf("Across\n"); // 横向输出
        for (int i = 0; i < n; i ++) {
            cin >>puzzle[i];
            for (int j = 0; j < m; j ++) { // 标记有编号的格子
                if ((i == 0 || j == 0) && puzzle[i][j] != '*') id[i][j] = ++cnt; // 第一行/列全部编号
                else { // 当前白格子上方或左方存在黑格子
                    if (puzzle[i][j] != '*' 
                    && (puzzle[i][j-1] == '*' || puzzle[i-1][j] == '*')) id[i][j] = ++cnt;
                }
            }
            for (int j = 0; j < m; ) { // 横向输出
                if (puzzle[i][j] == '*') j++;
                else {
                    printf("%3d.", id[i][j]); // 宽度3，右对齐！！！
                    while(j < m && puzzle[i][j] != '*') printf("%c", puzzle[i][j++]);
                    printf("\n");
                }
            }
        }
        printf("Down\n"); // 纵向输出
        string ans[101]; // 保存每个标号对应结果
        for (int j = 0; j < m; j ++) { // 存放与ans中
            for (int i = 0; i < n; ) {
                if (puzzle[i][j] == '*') i ++;
                else {
                    now = id[i][j];
                    while(i < n && puzzle[i][j] != '*') ans[now] += puzzle[i++][j];// printf("%c", puzzle[i++][j]);
                }
            }
        }
        for (int i = 1; i < 101; i ++) { // 将ans中记录的值顺序输出
            if (!ans[i].empty()) {
                printf("%3d.%s\n", i, ans[i].c_str()); // 宽度3，右对齐！！！
            }
        }
    }
    return 0;
}
```

## 习题3-7 UVA1368 DNA Consensus String

### 题目大意

给定若干个DNA序列，仅由ACGT四个字符构成，求解Hamming距离最小的字符串并输出错误数。

Hamming距离：字符不同的位置个数总和

```
原串1：ATCG
原串2：CTAG
共识串：ATAG
错误数：2 （第一个位置和第三个位置）
```

若有多个合法字符，则选择字典序最小的，再如上例，第一和第三个位置中AC个数相同，均选择字典序小者A

### 思路分析

按行读入字符串s，遍历s，按列统计ACTG出现次数，遍历完毕后，按列找出最大值MAX，输出相应字符，m-MAX作为总错误数的贡献，需累加。

可用哈希表完成0-3到ACGT之间双射，这里按字典序排列，保证存在多解时找到的都是字典序最小串

### AC代码（C++11，简单模拟，打表）

```cpp
#include<bits/stdc++.h>
using namespace std;
map<char, int> mp{{'A',0}, {'C',1}, {'G',2}, {'T',3}}; // 便于循环处理
char itc[4] = {'A', 'C', 'G', 'T'}; // [0,4)->[A,C,G,T]
int T, m, n, num[1010][4] = {0}; // ATGC出现次数
string s;
int main() {
    scanf("%d", &T);
    while(T --) {
        scanf("%d %d", &m, &n);
        fill(num[0], num[0] + 4040, 0); // 初始化二维数组
        for (int i = 0; i < m; i ++) { // 统计每一列中每个子符出现次数
            cin >>s;
            for (int j = 0; j < n; j ++) num[j][mp[s[j]]] ++;
        }
        int errNum = 0, idx = 0, MAX = -1;
        for (int i = 0; i < n; i ++) { // 遍历每一列
            idx = 0, MAX = -1; // 初始化
            for (int j = 0; j < 4; j ++) { // ACGT
                if (MAX < num[i][j]) { // 找最大值
                    idx = j;
                    MAX = num[i][j];
                }
            }
            errNum += (m - MAX); // 不同的个数
            printf("%c", itc[idx]);
        }
        printf("\n%d\n", errNum);
    }
    return 0;
}
```

## 习题3-8 UVA202 Repeating Decimals

### 思路分析

直接求解太难，可利用数学规律，模拟除法，商作为小数结果，余数作为下一次运算的被除数，一旦出现重复的余数，说明找到循环节。

### 注意点

+ 第一位必须舍弃
+ 输出字符最多50个，不包含括号
+ 每组输出必须有两个换行！！！

### AC代码（C++11，除法模拟，循环节）

```cpp
#include<bits/stdc++.h>
using namespace std;
int a, b, begIdx=-1;
string si, sd;
int main() {
    while(cin >>a >>b) {
        vector<pair<int,int>> d;
        si = to_string(a / b);
        printf("%d/%d = %s.", a, b, si.c_str());
        a = (a % b)*10; // 第一个必须舍弃
        begIdx = -1;
        while(begIdx == -1) { // 除法模拟
            d.push_back({a, a/b});
            a = (a%b)*10;
            for (int i = 0; i < d.size(); i ++) {
                if (d[i].first == a) {
                    begIdx = i; // 循环节开始
                    break;
                }
            }
        }
        for (int i = 0; i < begIdx; i ++) printf("%d", d[i].second);
        printf("(");
        for (int i = begIdx; i < ((d.size() > 50) ? 50 : d.size()); i ++) printf("%d", d[i].second);
        printf("%s", d.size() > 50 ? "...)" : ")");
        printf("\n   %d = number of digits in repeating cycle\n\n", d.size()-begIdx); // 诡异输出，每个输出后均两个换行
    }
    return 0;
}
```

## 习题3-9 UVA10340 All in All

### 思路分析

给定字符串s，t，判断s是否为t的子序列。子序列不同于子串

+ 子串：必须相邻，比如`s=ab, t=cabafb`，t中第2，3位置为连续ab（下标从1开始），即子串s

+ 子序列：可不相邻，再如上例，下标为`[2,3]、[3,6]、[2,6]`表示的子序列均为s

#### 双指针

本题仅为判定问题，最简单可直接使用双指针，但也有两种思路：

+ 以s为参照：以i，j分别指向s，t开始，枚举s的每个元素ch，若在tj之后找到ch，i,j同时后移，否则说明不存在子序列

+ 以t为参照（最简单）：枚举t，以i指向s开始，若当前t元素ch==s[i]，则共同后移，否则仅t后移

#### 子序列dp

判定问题转为子序列计数问题，若个数为0，说明不存在，因此可用dp解决。具体思路如下：

使用`map<char,vector<int>>mp`建立字符ch到**ch在字符串s中出现位置集合**的映射，此处使用set或vector均可，因此后期用滚动数组优化，需要逆序遍历出现位置，因此注意遍历顺序。

初始化`dp[0]=1`，为第一个字符做准备，其余字符转移函数为`dp[k]=dp[k]+(ch=='s[k]')*dp[k-1]`

### AC代码（C++11）

#### 双指针（以s为参照，21行）

```cpp
#include<bits/stdc++.h>
using namespace std;
string s, t;
int main() {
    while(cin >>s && cin >>t) {
        bool isSub = false; // 记录是否为子序列
        int i = 0, j = 0; // 双指针
        while (i < s.size() && j < t.size()) { // 以s为参照，遍历s，t
            if (s[i] == t[j]) { // 找到相等
                if (i == s.size() - 1) {
                    isSub = true;
                    break;
                }
                i ++; j ++;
            }
            while (j < t.size() && s[i] != t[j]) j ++;
        }
        printf("%s\n", isSub ? "Yes" : "No");
    }
    return 0;
}
```

#### 双指针（以t为参照，13行）

```cpp
#include<bits/stdc++.h>
using namespace std;
string s, t;
int main() {
    while(cin >>s >>t) {
        int i = 0;
        for (auto ch : t) { // 以t为参照，依次比较
            if (ch == s[i]) i ++;
        }
        printf("%s\n", (i == s.size()) ? "Yes" : "No");
    }
    return 0;
}
```

#### 子序列dp计数（通用模板，25行）

```cpp
#include<bits/stdc++.h>
using namespace std;
map<char, vector<int>> mp; // 存储每个字符所在位置
string s,t;
int main() {
    while(cin>>s && cin >>t) {
        mp.clear(); // 初始化
        int dp[s.size()+1] = {1,0}; // dp计数
        for (int i = 0; i < s.size(); i ++) { // 统计每个字符所在位置，从1开始算
            if (mp.find(s[i]) == mp.end()) { // 未存在
                mp.insert({s[i], {i+1}});
            }
            else mp[s[i]].push_back(i+1); // 已存在，存入
        }
        for (int i = 0; i < t.size(); i++) { // 遍历字符串t
            if (mp.find(t[i]) != mp.end()) { // 字符出现在s中
                for (int k = mp[t[i]].size() - 1; k >= 0; k --) { // 逆序遍历字符所在s中位置，滚动数组优化
                    dp[mp[t[i]][k]] += dp[mp[t[i]][k]-1]; // dp[j]=dp[j]+dp[j-1]
                }
            }
        }
        printf("%s\n", dp[s.size()] == 0 ? "No" : "Yes"); // 最后一个为总序列个数
    }
    return 0;
}
```

### 小结

虽然很简单的一道题，但从不同角度分析可得到许多有趣的结果。

以不同的字符串作为参照，代码量和思维量相差巨大（双指针，以s、t为参照）

将判定性问题转为计数问题，也是解决问题的一种思路（dp）

## 习题3-10 UVA1587 Box

### 思路分析

给定6个已知长宽的矩形，判断是否能构成长方体。判定的等价条件如下：

+ 6个面，分三组，因此可用`map<set<int>,int>`记录每个面出现次数，由于存在正方体（6），两个正方形面（2,4），三个长方形（2,2,2），因此，每个面出现次数为`2/4/6`，即2的倍数。
+ 12条边，分三组，因此可用`map<int,int>`记录每条边长出现次数，遇上同理，存在`4/8/12`三种情况，即4的倍数。

### STL使用技巧

+ map初始化：对于不存在的key，使用mp[k]时自动初始化value，比如以下实例：

```
map<int,int>mpInt;
cout <<mpInt[1]; // 输出0
map<int,set<int>> mpSet;
cout <<mpSet[1].size(); // 输出0
map<int,vector<int>> mpVec;
cout <<mpVec[1].size(); // 输出0
```

### AC代码（C++11，长方体判定条件，STL）

```cpp
#include<bits/stdc++.h>
using namespace std;
map<set<int>, int> box;
map<int, int> edge;
int a, b;
int main() {
    while(cin >>a >> b) {
        bool isBox = false, flag = true, flag2 = true;
        box.clear(); edge.clear();
        for (int i = 0; i < 6; i ++) {
            if (i != 0) cin >>a >>b;
            box[{a,b}] ++;
            edge[a] ++;
            edge[b] ++;
        }
        for (auto p : box) { // 每个面出现次数为2,4,6
            if (p.second % 2 != 0) {
                flag = false; break;
            }
        }    
        for (auto p : edge) { // 每条边出现次数为4,8,12
            if (p.second % 4 != 0) {
                flag2 = false; break;
            }
        }
        if (flag && flag2) isBox = true; // 满足两个条件可构造长方体
        printf("%s\n", isBox ? "POSSIBLE" : "IMPOSSIBLE");
    }
    return 0;
}
```

## 习题3-11 UVA1588 Kickdown

### 思路分析

给定两个数字串，仅由1、2组成，当相应位置不同时为2时，说明两个位置匹配，这题本质就是找最长匹配长度max，两个数字串长度总和-max即为结果。

假设数字串a,b，且a长度小于b，且固定b，向右移动a，考虑三种位置情况：

+ a在b左侧
+ a在b内部
+ a在b右侧

简单遍历，每次取最小即可

### 注意点

+ a在b的左侧容易遗忘
+ 题目明确要求无需考虑反转，若反转，有些结果会变小，比如`12,12`会变成2，正确应是3

+ 可通过增加线段起点，统一3中情况，优化代码，[参考博文](https://blog.csdn.net/richenyunqi/article/details/82432889)

### AC代码（C++11，双串匹配）

```cpp
#include<bits/stdc++.h>
using namespace std;
string a, b;
int getMin(string a, string b) { // 获取a和b最小的组合长度
    if (a.size() > b.size()) swap(a,b); // a为短者
    int MIN = a.size() + b.size();
    for (int i = a.size(); i > 0; i --) { // a的长度；a在b左侧
        int j;
        for (j = 0; j < i; j ++) {
            if (a[a.size()-i+j] == '2' && b[j] == '2') break;
        }
        if (j == i) { // 找到第一个符合
            MIN -= i;
            break;
        }
    }
    for (int i = 0; i <= b.size()-a.size(); i ++) { // b的起始位置；a包含于b
        int j;
        for (j = 0; j < a.size(); j ++) {
            if (a[j] == '2' && b[i+j] == '2') break;
        }
        if (j == a.size()) {
            MIN = b.size();
            break;
        }
    }
    for (int i = a.size()-1; i > 0; i --) { // a的长度；a在b右侧
        int j;
        for (j = 0; j < i; j ++) {
            if (a[j] == '2' && b[b.size()-i+j] == '2') break;
        }
        if (j == i) {
            MIN = min(MIN, (int)(a.size()+b.size()-i));
            break;
        }
    }
    return MIN;
}
int main() {
    while(cin >>a >>b) {
        printf("%d\n", getMin(a,b));
    }
    return 0;
}
```

## 习题3-12 UVA11809 Floating-Point Numbers

### 思路分析

给定浮点数最大值的十进制表示，求解尾数和指数的位数（注意**尾数计算时需多算一位，因为尾数第一位默认为1**）

这题只能用暴力求解，但有几个求解和优化技巧：

+ 打表：枚举所有的M,E，记录结果，到时候直接比较结果即可
+ 对数降解：根据题意容易得到一个等式，但直接计算一定溢出，无法存储和计算，因此，可在等式两侧同时取log10，瞬间降低运算值。

+ A，B计算：假设AeB是**科学计数法**形式，则1<A<10，0<lgA<1
+ 精度选取：`1e-5,1e-6`均可，过高则会WA，因为double保存有效数位有限
+ 公式推导如下：

$$
原式：(1-2^{-(M+1)})*2^{2^E-1}=A*10^B\\
两边取对数：t=lg(1-2^{-(M+1)})+Elg2=lgA+B\\
B=int(t)\\
A=10^{t-B}
$$

其中M,E分别表示尾数和指数的位数，且AeB是**科学计数法**形式，即1<A<10，0<lgA<1，是小数部分，B为整数部分。

### AC代码（C++11，打表+对数降维+公式推导+精度选择）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define epison 1e-5 // 精度设置,1e-6也行
#define log10_2 log10(2)
double A, AP[11][31]; // A实际值，预测值
long long  B, BP[11][31]; // B实际值，预测值
string s;
void init() { // 打表，将所有可能的值记录下来
    for (int i = 0; i < 10; i ++) {
        for (int j = 1; j < 31; j ++) {
            double t = log10(1-pow(2,-i-1)) + (pow(2,j)-1)*log10_2; // 等式左侧：lg(1-(1/2)^(M+1)) + lg(2^(2^E-1))
            BP[i][j] = t; // 取整数部分，也就是B的值
            AP[i][j] = pow(10, t-BP[i][j]); // A = 10^(t-B)
        }
    }
}
int main() {
    init();
    while(cin >>s && s != "0e0") {
        s[s.find('e')] = ' '; // e替换为空格
        stringstream input(s);
        input >>A >>B;
        while(A < 1) A *= 10, B --; // 转换为科学计数法
        for (int i = 0; i < 10; i ++) { // 查表
            for (int j = 1; j < 31; j ++) {
                if (B == BP[i][j] && fabs(AP[i][j]-A) < epison) {
                    printf("%d %d\n", i, j);
                }
            }
        }
    }
    return 0;
}
```


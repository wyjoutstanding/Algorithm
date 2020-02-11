# 《算法竞赛入门经典第2版》题解系列 第四章 函数和递归

## 题解分类索引

**[OJ网址点这里](https://vjudge.net/problem)**

紫书刷题进行中，[题解系列点这里](https://github.com/wyjoutstanding/Algorithm/tree/master/aoapc_uva)

本章题目多为模拟思维题，建议都独立完成一遍，对编程能力提升有很大帮助

| 书中编号 | 题目编号 | 标题（题解链接）                                             | 分类     | 备注                                                         |
| -------- | -------- | ------------------------------------------------------------ | -------- | ------------------------------------------------------------ |
| 例题4-1  | UVA1339  | [Ancient   Cipher](#例题4-1-uva1339-ancient-cipher)          | 思维题   | 条件转换，sort，位置顺序不重要                               |
| 例题4-2  | UVA489   | [Hangman   Judge](#例题4-2-uva489-hangman-judge)             | 简单模拟 | set去重                                                      |
| 例题4-3  | UVA133   | [The   Dole Queue](#例题4-3-uva133-the-dole-queue)           | 简单模拟 | 约瑟夫环变种，模运算                                         |
| 例题4-4  | UVA213   | [Message   Decoding](#例题4-4-uva213-message-decoding)       | 解码模拟 | 字符串处理，进制转换                                         |
| 例题4-5  | UVA512   | [Spreadsheet   Tracking](#例题4-5-uva512-spreadsheet-tracking) | 复杂模拟 | 整体/单个模拟；**结构体作Map的key**；处理多行/列时，先处理大者 |
| 例题4-6  | UVA12412 | [师兄帮帮忙](#例题4-6-uva12412-师兄帮帮忙)                   | 复杂模拟 | 数据结构设计，输出格式细心；查询优化                         |
| 习题4-1  | UVA1589  | [Xiangqi](#习题4-1-uva1589-xiangqi)                          | 复杂模拟 | 象棋方向向量，马脚处理，将军吃红子                           |
| 习题4-2  | UVA201   | [Squares](#习题4-2-uva201-squares)                           | 中级模拟 | 最长距离优化/类似前缀和                                      |
| 习题4-3  | UVA220   | [Othello](#习题4-3-uva220-othello)                           | 中级模拟 | 棋盘方向模拟，直线判断                                       |
| 习题4-4  | UVA253   | [Cube   painting](#习题4-4-uva253-cube-painting)             | 中级模拟 | 推导思考，判定条件，轮换/基向量（顺序无关）                  |
| 习题4-5  | UVA1590  | [IP   Networks](#习题4-5-uva1590-ip-networks)                | 中级模拟 | 位运算，bitset，进制转换，字符串处理                         |
| 习题4-6  | UVA508   | [Morse   Mismatches](#习题4-6-uva508-morse-mismatches)       | 解密模拟 | **逆向思维**，题意不明，map                                  |
| 习题4-7  | UVA509   | [RAID](#习题4-7-uva509-raid)                                 | 数组模拟 | RAID，进制转换，bitset，分块处理（cache）                    |
| 习题4-8  | UVA12108 | [Extraordinarily   Tired Student](#习题4-8-uva12108-extraordinarily-tired-student) | 状态模拟 | **循环节**判断（死循环处理）                                 |
| 习题4-9  | UVA1591  | [Data   Mining](#习题4-9-uva1591-data-mining)                | 简单模拟 | 公式推导，等差数列，移位溢出处理                             |
| 习题4-10 | UVA815   | [Flooded](#习题4-10-uva815-flooded)                          | 简单模拟 | sort，**补面积做差**，**浮点误差**（少用除法）               |

## 例题4-1 UVA1339 Ancient Cipher

### 思路分析

给定两个等长字符串sa，sb（仅包含26个大写字母），是否存在如下关系：

> sa --排序--> sa' --双射--> sb

若直接暴力枚举，排序和双射构造均存在n!中情况，不现实。

但本题仅仅为判定性问题，只要能判断是否存在相应关系即可，无需找出哪种排序和双射形式，因此，可以取巧。

排序时任意排列（置换），因此字母顺序不重要，又要求一一对应的映射，同时等长，那必定是26字母间的双射，因此可先统计两个字符串中每个字母出现次数，若每种次数的个数一致，说明可构造双射。

所以，先统计两个字符串中每个字符出现次数，再对次数进行升序排列，若排列后的两个序列一致，说明存在以上关系，否则不存在。

### AC代码（C++11，思维题，条件转换）

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    string sa, sb;
    vector<int> cnta(26), cntb(26); // 统计个数
    while(cin >>sa >>sb) {
        fill(cnta.begin(), cnta.end(), 0); // 初始化
        fill(cntb.begin(), cntb.end(), 0);
        for (auto ch : sa) cnta[ch-'A'] ++; // 统计字符出现次数
        for (auto ch : sb) cntb[ch-'A'] ++;
        sort(cnta.begin(), cnta.end()); // 排序
        sort(cntb.begin(), cntb.end());
        printf("%s\n", (cnta == cntb) ? "YES" : "NO");
    }
    return 0;
}
```

## 例题4-2 UVA489 Hangman Judge

### 题目大意

刽子手游戏模拟，给定**答案序列a**和**猜测序列b**（仅由小写字母构成），执行以下规则：

+ 对b中的每个字母ch，若ch存在于a，则将a中所有ch标记为已访问；否则累加错误次数
+ 若错误次数**大于等于7**，输出`You lose.`
+ 若错误次数小于7且a中完全被标记，输出`You win.`
+ 若错误次数小于7且a未完全被标记，输出`You chickened out.`

### 算法设计

定义`set<char>ans,hit`分别存储去重后的答案序列和命中序列，cnt记录错误次数。

枚举猜测序列b每个元素ch，若ch存在于ans，则将ch将入hit，否则cnt++，记录错误数，直至cnt=7或hit大小等于ans时结束循环。

### 注意点

+ 猜测序列存在**重复**字母，也需累计错误次数

### AC代码（C++11，简单模拟，set）

```cpp
#include<bits/stdc++.h>
using namespace std;
set<char> ans, hit; // 答案序列，命中序列
string a,b;
int id, cnt; // round，错误次数
int main() {
    while (scanf("%d", &id) && id != -1) {
        cin >>a >>b;
        ans.clear(); hit.clear(); cnt = 0; // 初始化
        for (auto ch : a) ans.insert(ch);
        for (auto ch : b) { // 遍历猜测序列
            if (cnt == 7 || ans.size() == hit.size()) break; // 错误7次|完全猜中
            if (ans.find(ch) != ans.end()) hit.insert(ch); // 猜中
            else cnt ++; // 未猜中
        }
        printf("Round %d\n", id);
        if (cnt == 7) printf("You lose.\n");
        else if (ans.size() == hit.size()) printf("You win.\n");
        else printf("You chickened out.\n");
    }
    return 0;
}
```

## 例题4-3 UVA133 The Dole Queue

### 题目大意

假定N个人从1-N逆时针编号，Rk从1开始逆时针数k个人，Rm从n开始顺时针数m个人，淘汰被选中的人，依次类推，直至最后无人存活

### 算法设计

用数组a存放N个人，其中a[i]=0表示存活，a[i]=-1表示死亡。

用ki和mi分别表示被Rk和Rm选中的人

+ 逆时针每次加1取模：ki=(ki+1)%n
+ 顺时针每次加n-1取模：mi=(mi+n-1)%n

### 注意点

+ 注意每一轮中逆时针选中的人，在顺时针依旧可以被选！
+ 输出是数字宽度占**3列**，用%3d控制即可
+ 最后不要输出多余逗号

### AC代码（C++11，约瑟夫环变种，模运算）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k, m;
int main() {
    while(scanf("%d %d %d", &n, &k, &m) == 3 && n != 0) {
        vector<int> a(n);
        int ki=0, mi = n-1, cnt = 0, cntk=0, cntm=0;
        while(cnt < n) {
            while (true) { 
                if (a[ki] != -1) cntk ++; // 统计数过的人
                if (cntk == k) break;
                ki = (ki+1) % n; // 逆时针
            }
            while (true) {
                if (a[mi] != -1) cntm ++;
                if (cntm == m) break;
                mi = (mi+(n-1)) % n; // 顺时针，用加替代减
            }
            if (ki == mi) { // 指向同一个人
                a[ki] = -1;
                cnt ++; // 计算死亡人数，控制循环和末尾,
                printf("%3d%s", ki+1, cnt == n ? "" : ","); // 对齐宽度3！！！
            }
            else { // 指向不同人
                a[ki] = -1; a[mi] = -1;
                cnt += 2;
                printf("%3d%3d%s", ki+1, mi+1, cnt == n ? "" : ",");
            }
            cntk = cntm = 0;
        }
        printf("\n"); // 别漏
    }
    return 0;
}
```

## 例题4-4 UVA213 Message Decoding

### 题目大意

给定编码头和编码后的信息文本，要求解密。

以下阐述编码策略，首先看以下01序列，每一行长度依次递增，每一行内从左到右从0开始依次递增，以此类推

> 0
>
> 00 01 10
>
> 000 001 010 011 100 101 110
>
> 0000 0001.....

这个序列和编码头一一顺序对应，比如编码头为`$#**\`，其对应关系如下（这个表简称**解码表**）：

| $    | #    | *    | *    | \    |
| ---- | ---- | ---- | ---- | ---- |
| 0    | 00   | 01   | 10   | 000  |

现再给定编码后的01序列，对它的**解码规则**如下：

+ 头三个01串的值表示key长度len，若遇到三个0，则表示结束
+ 往后读取len个01字符，根据解码表得到相应字符，直至遇到len个全1字符，结束当前小节

比如编码后的序列为`0100000101101100011100101000`，结合以上解码表有如下解码过程：

> 010（len=2，小节1开始）
>
> 00（解码表#）00（#）10（*）
>
> 11（len个1，结束小节1）
>
> 
>
> 011（key长度3，小节2开始）
>
> 000（\）
>
> 111（结束小节2）
>
> 
>
> 001（key长度1，小节3开始）
>
> 0（$）
>
> 1（结束小节3）
>
> 
>
> 000（结束整个解码过程）

因此，解码的最终结果为`##*\$`

### 算法设计

明白题意后问题变得简单，只需两步：

+ **构造01序列**，接着构造解码表（01序列和编码头字符的顺序对应关系)
+ 用循环实现解码规则

其中01序列构造为核心，有两种方式实现：

+ 直接构造字符串：转换时设置宽度（前置补0）
+ 用二进制字符串的长度和值（len,value)存储

### AC代码（C++11，解码模拟，字符串处理）

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<string> bsv; // 存放二进制key
map<string, char> mp; // 构造key到字母映射
string decToBin(int val, int width) { // 10进制数值转为2进制字符串，并指定宽度
    string ret;
    do {
        ret.push_back((val % 2)+'0');
        val /= 2;
    } while(val != 0);
    reverse(ret.begin(), ret.end()); // 反转
    ret = string(width-ret.size(), '0') + ret; // 前置0
    return ret;
}
int binToDec(string s) { // 2进制字符串转为10进制数值
    int ret = 0;
    for (auto ch : s) ret = ret * 2 + (ch - '0');
    return ret;
}
void init() { // 构造0~1111111的二进制key
    string s; char str[1000];
    for (int l = 1; l < 8; l ++) { // key长度[1,7]
        for (int j = 0; j < (1<<l)-1; j ++) { // [0,1<<l-1)
            bsv.push_back(decToBin(j, l)); // 保存
        }
    }
}
int main() {
    init();
    string head, mess, s, t;
    getline(cin, head); // 头部
    while(true) {
        while(getline(cin, s) && (s[0] == '0' || s[0] == '1')) mess += s; // 消息拼接
        if (mess.empty()) break; // 控制结束
        for (int i = 0; i < head.size(); i ++) mp.insert({bsv[i], head[i]}); // 构造映射
        int i = 0;
        while(i < mess.size()) { // 遍历信息串，解码规则实现
            t = mess.substr(i, 3); i += 3;// 开始3个字符
            if (t == "000") break;
            else {
                int l = binToDec(t); // 读取长度
                while (i < mess.size()) {
                    t = mess.substr(i, l); i += l;
                    if (t == string(l, '1')) break; // l个1，section结束
                    printf("%c", mp[t]); // 输出映射结果
                }
            }
        }
        puts(""); // 换行
        head = s; mess.clear(); mp.clear();// 下一个头部，清空
    }
    return 0;
}
```

## 例题4-5 UVA512 Spreadsheet Tracking

### 题目大意

给定一个r*c的表格，模拟五种操作，现给出原始单元格坐标，输出最终的单元格坐标，五种操作如下：

+ 删除多行/列
+ 插入多行/列
+ 交换两个单元格

### 思路分析

有两种思路解决：

+ 整体模拟：直接模拟整个表格的变化，得到最终表格，然后直接查询相应单元格
+ 单个模拟：将命令序列储存起来，对每一个查询的单元格，模拟执行所有命令，输出结果

前者比较直观，符合思维习惯；后者代码量小，在当前数据规模下效率较高

但二者对于操作的模拟逻辑是一致的，假设当前单元格坐标（x,y），当前操作为op，当前操作对应的行列号为i，伪代码如下：

```python
if op == "DR": 
	if x == i: 
		删除(x,y)
    else if x > i: 
		x ++
else if op == "DC":
	if y == i:
		删除(x,y)
    else if y > i:
        y ++
else if op == "IR" && x >= i:
	x ++
else if op == "IC" && y >= i:
    y ++
else if op == "EX":
    if (x,y)属于交换单元格中的一个：
    	x = r
        y = c
```

### 算法设计

以下详细阐述整体模拟和单个模拟的算法设计思路。

#### 整体模拟

定义Pos结构体，表示单元格坐标，为了在Map中使用Pos做键值，必须重载`<`，作为map排序规则

```cpp
typedef struct Pos{
    int x, y;
    Pos(int _x=0, int _y=0): x(_x), y(_y){} // 默认值表示默认构造函数
    // bool operator < (const Pos& b) const { // map需要排序，必须加const，否则编译报错
    //     if (x == b.x) return y < b.y;
    //     else return x < b.x;
    // }
    friend bool operator < (const Pos& a, const Pos& b) { // 友元函数,map需要排序
        if (a.x == b.x) return a.y < b.y;
        else return a.x < b.x;
    }
} Pos;
```

定义`Map<Pos,Pos>mp1,mp2,mp3`，三者表示含义如下：

+ mp1：当前位置->原始位置（始终表示当前表格状态)
+ mp2：操作模拟的中间变量（存储表格中间态）
+ mp3：原始位置->最终位置（逆置mp1的键值对，便于查询)

为了解决插入或删除多行/列时，行列号小者先执行会影响行列号大的问题，有两种思路：

+ 重载<：在结构体中重载运算符<时，定义坐标大者在前，可避免该问题
+ 计数：定义`vector<int>cnt(60)`，cnt[i]表示**小于等于i**的个数。比如当前命令为插入第五行，那么仅需令`x+=cnt[5]`，若是删除第五行，仅需令`x-=cnt[4]`（删除是严格大于i）

计数实现也简单，分两步：

+ 哈希计数：统计当前命令序列每个数字出现的次数，即若当前数字为i，则`cnt[i]++`
+ 一遍累加：`cnt[i]+=cnt[i-1],i从1开始，cnt[0]=0`

#### 单个模拟

定义`vector<pair<string,vector<int> > > cmd`，存储当前表格的所有操作命令序列，其中string表示五种操作，`vector<int>`表示操作命令对应的行列集合。

在遍历插入/删除集合前，对其进行降序排列，避免小者对大者产生影响

此处实现思路与**思路分析**中的伪代码一致，不再赘述。

### 注意点

+ 输出时两个表格间需要一个空行，最后一个表格无需多余空行
+ 使用结构体做Map的key时，必须重载<，否则无法通过编译，重载可用成员函数/友元函数方式
+ 插入或删除多行/列，注意处理行列号的顺序，大者先执行

### AC代码（C++11）

#### 整体模拟（Map）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef struct Pos{
    int x, y;
    Pos(int _x=0, int _y=0): x(_x), y(_y){} // 默认值表示默认构造函数
    // bool operator < (const Pos& b) const { // map需要排序，必须加const，否则编译报错
    //     if (x == b.x) return y < b.y;
    //     else return x < b.x;
    // }
    friend bool operator < (const Pos& a, const Pos& b) { // map需要排序
        if (a.x == b.x) return a.y < b.y;
        else return a.x < b.x;
    }
} Pos;
map<Pos,Pos> mp1, mp2, mp3; // 当前位置->原始位置，操作模拟的中间变量，原始位置->最终位置
int r, c, op, n, t, num = 0;
string s;
vector<int> cnt(60);
int main() {
    while(scanf("%d %d", &r, &c) == 2 && (r != 0 && c != 0)) {
        scanf("%d", &op);
        if (num != 0) puts("");
        printf("Spreadsheet #%d\n", ++num);
        mp1.clear(); // 清空
        for (int i = 1; i <= r; i ++) { // 初始化：当前位置->原始位置
            for (int j = 1; j <= c; j ++) {
                mp1.insert({Pos{i,j}, Pos{i,j}});
            }
        }
        while(op --) { // 操作
            cin >>s;
            if (s != "EX") { // 不为Exchange
                cin >>n;
                fill(cnt.begin(), cnt.end(), 0); // 初始化
                set<int> rcset; // 要删除/插入的行列集合
                while(n --) {
                    cin >>t; rcset.insert(t);
                    cnt[t] ++; // 统计每个序号出现次数
                }
                for (int i = 1; i < cnt.size(); i ++) cnt[i] += cnt[i-1]; // cnt[i]表示小于等于i的个数，用于计算最终行列号
                for (auto p = mp1.begin(); p != mp1.end(); p ++) { // 遍历每个cell
                    if (s == "DR") { // 删除行
                        if (rcset.find(p->first.x) == rcset.end()) // 未找到，不被删除
                            mp2.insert({{p->first.x - cnt[p->first.x-1],p->first.y}, p->second}); // 插入记录
                    }
                    else if (s == "DC") { // 删除列
                        if (rcset.find(p->first.y) == rcset.end()) // 不被删除
                            mp2.insert({{p->first.x, p->first.y-cnt[p->first.y-1]}, p->second});
                    }
                    else if (s == "IR") { // 插入行
                        mp2.insert({{p->first.x+cnt[p->first.x], p->first.y}, p->second}); // 更新位置
                    }
                    else if (s == "IC") {
                        mp2.insert({{p->first.x,p->first.y+cnt[p->first.y]}, p->second}); // 更新位置
                    }
                }
                mp1 = mp2; mp2.clear(); // 更新当前位置关系
            }
            else {
                int r1,c1,r2,c2;
                cin >>r1 >>c1 >>r2 >>c2;
                swap(mp1[{r1,c1}], mp1[{r2,c2}]); // 交换单元格，考虑交换单元格包含刚插入的
            }
        }
        mp3.clear();
        for (auto p : mp1) mp3.insert({p.second, p.first}); // 逆置：原始位置->最终位置
        cin >>n;
        int x, y;
        while (n --) { // 处理查询
            cin >>x >>y;
            if (mp3.find({x,y}) == mp3.end()) printf("Cell data in (%d,%d) GONE\n", x, y);
            else printf("Cell data in (%d,%d) moved to (%d,%d)\n", x, y, mp3[{x,y}].x, mp3[{x,y}].y);
        }
    }
    return 0;
}
```

#### 单个模拟

```cpp
#include<bits/stdc++.h>
using namespace std;
int r, c, op, cnt = 0;
string s;
int main() {
    while (scanf("%d %d", &r, &c) == 2 && (r != 0 && c != 0)) {
        scanf("%d", &op); // 操作个数
        printf("%sSpreadsheet #%d\n", cnt != 1 ? "\n":"", ++cnt); // ++优先级高，控制空行
        vector<pair<string,vector<int> > > cmd; // 存储命令和对应的行列集合
        while (op --) { // 存储输入命令
            cin >>s;
            cmd.push_back({s, vector<int>()}); // 初始化
            int n, t;
            if (s == "EX") n = 4;
            else scanf("%d", &n);
            while (n --) {
                scanf("%d", &t);
                cmd.back().second.push_back(t);
            }
        }
        int n, x, y, ansX, ansY;
        scanf("%d", &n);
        while (n --) { // n个查询
            scanf("%d %d", &x, &y);
            ansX = x; ansY = y; // 最终结果初始化
            for (auto p : cmd) { // 遍历所有命令
                if (p.first != "EX") { // 插入/删除
                    sort(p.second.begin(), p.second.end(), [](int& a, int &b) {return a > b;}); // 降序排列
                    for (auto i : p.second) { // 遍历删除或插入的行/列号（从大到小，否则前面会影响后面）
                        if (p.first == "DR") { // 删除行
                            if (i == ansX) ansX = -1; // -1标记删除
                            else if (ansX > i) ansX --; // 行号大于i才改变
                        }
                        else if (p.first == "DC") { // 删除列，与删除行类似
                            if (i == ansY) ansY = -1;
                            else if (ansY > i) ansY --;
                        }
                        else if (p.first == "IR" && ansX >= i) ansX ++; // 插入行，>=i就会改变
                        else if (p.first == "IC" && ansY >= i) ansY ++; // 插入列，>=i就会改变
                        if (ansX == -1 || ansY == -1) break; // 发现删除，直接结束
                    }
                }
                else { // 交换单元格
                    if (ansX == p.second[0] && ansY == p.second[1]) ansX = p.second[2], ansY = p.second[3];
                    else if (ansX == p.second[2] && ansY == p.second[3]) ansX = p.second[0], ansY = p.second[1];
                }
            }
            if (ansX == -1 || ansY == -1) printf("Cell data in (%d,%d) GONE\n", x, y);
            else printf("Cell data in (%d,%d) moved to (%d,%d)\n", x, y, ansX, ansY);
        }
    }
    return 0;
}
```

## 例题4-6 UVA12412 师兄帮帮忙

### 思路分析

只需按部就班实现各个功能，虽然繁琐，但无难点。深入思考有助于提高编程能力。

虽实现容易，但新手和老手在效率和代码长度会存在很大差异，以下对比三份代码实现思路：

| 比较项目 | 我的代码                                         | [日沉云起](https://blog.csdn.net/richenyunqi/article/details/82948682) | [刘汝佳](https://github.com/aoapc-book/aoapc-bac2nd/blob/master/ch4/UVa12412.cpp) |
| -------- | ------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 存储     | vector<Student>stu                               | vector<Student>stu                                           | 拆分为多个属性数组                                           |
| 插入     | 维护sidMap，查询是否已存在                       | 线性查找stu（find_if）                                       | 线性查找                                                     |
| 删除     | 维护sidMap，nameMap                              | vector直接erase                                              | 维护removed数组                                              |
| 查询     | 查询sidMap/nameMap，仅有插入删除时才重新整体计算 | 线性查找                                                     | 线性查找                                                     |
| 排名     | cnt[i]统计每个出现总分i出现次数，逆向累加计数    | 结构体<总分,id>降序排列，一次遍历计算每个排名                | 每次仅计算要输出的学生排名（一次遍历）                       |
| 统计     | 当有插入/删除时，才重新计算整个统计数据          | 每次只计算要输出的统计数据                                   | 每次只计算要输出的统计数据                                   |

+ 从效率上来说，使用一个Map或数组维护被删除的学生下标效率较高，因为线性表删除复杂度O(N)；同时，也可以极大提高查询效率，Map查询和删除只需O(logn)
+ 对于排名和统计数据，若查询多于插入删除，则每次计算出整体，当有插入删除操作时才重新更新效率高；若插入删除较频繁，则适合每次仅计算要查询部分的信息

+ 空间换时间：可通过数组降低代码复杂度，类似哈希思想，本题有许多字符串输出，就可以使用此技巧

### 注意点

+ 出题者没说明除数为0时的输出结果，好像测试用例并没此边界条件
+ 平均分无论是否有四舍五入都能过？
+ 计算平均分要加上损失精度1e-5

### AC代码（C++11，复杂模拟)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mainMenu "Welcome to Student Performance Management System (SPMS).\n\n1 - Add\n2 - Remove\n3 - Query\n4 - Show ranking\n5 - Show Statistics\n0 - Exit\n\n"
string tips[6] = {"","Please enter the SID, CID, name and four scores. Enter 0 to finish.",
                "Please enter SID or name. Enter 0 to finish.","Please enter SID or name. Enter 0 to finish.",
                "Showing the ranklist hurts students' self-esteem. Don't do that.", "Please enter class ID, 0 for the whole statistics."};
string courses[4] = {"Chinese", "Mathematics", "English", "Programming"};
string stamess[5] = {"failed all", "passed 1 or more", "passed 2 or more", "passed 3 or more", "passed all"}; // 统计提示信息
typedef struct Student {
    string sid, name;
    int cid, score[4], tot;
}Student;
Student stu;
vector<Student> stuVec; // 数据库
int opt, num = 0, ranks[410]; // 当前选项
bool isChangeRank = true, isChangeSta = true; // 记录是否有插入或删除操作，便于计算总分排名
map<string, int> sidMp; // sid -> student存放位置
map<string, set<int> > nameMp; // name -> student存放位置
typedef struct Statistics { // 资料统计
    int totScore[4], num, pass[4], overall[5]; // 总分，总人数，每科通过人数，汇总数据
}Statistics;
vector<Statistics> info;
void add() { // 插入学生
    while(cin >>stu.sid && stu.sid != "0") {
        cin >>stu.cid >>stu.name; stu.tot = 0;
        for (int i = 0; i < 4; i ++) {
            scanf("%d", &stu.score[i]);
             stu.tot += stu.score[i]; // 计算总分
        }
        if (sidMp.find(stu.sid) == sidMp.end()) { // sid不存在
            isChangeRank = isChangeSta = true; // 标记被改变
            stuVec.push_back(stu); // 保存
            sidMp.insert({stu.sid, num});
            nameMp[stu.name].insert(num++);
        }
        else cout <<"Duplicated SID." <<endl; // sid已存在
        cout <<tips[opt] <<endl; // 提示输入语句
    }
}
void remove() { // 删除学生
    string s; 
    while (cin >>s && s != "0") {
        int cnt = 0;
        if (isdigit(s[0])) { // sid
            if (sidMp.find(s) != sidMp.end()) { // 存在此sid学生
                isChangeRank = isChangeSta = true; cnt = 1; // 删除人数
                nameMp[stuVec[sidMp[s]].name].erase(sidMp[s]); // 维护nameMp
                sidMp.erase(s); // 维护sidMp
            }
        }
        else { // name
            if (nameMp.find(s) != nameMp.end()) { // 存在此名字学生
                isChangeRank = isChangeSta = true; cnt = nameMp[s].size(); // 删除人数
                for (auto i : nameMp[s]) sidMp.erase(stuVec[i].sid); // 维护sidMp
                nameMp.erase(s); // 维护nameMp
            }
        }
        printf("%d student(s) removed.\n", cnt); // 对齐2个宽度，没对齐
        cout <<tips[opt] <<endl; // 提示信息
    }
}
void calRanks() { // 计算总分排名（所有班级）
    int cnt[410] = {0}; // 每个总分出现次数
    for (auto p : sidMp) cnt[stuVec[p.second].tot] ++; // 所有班级的学生
    bool isFirst = true; 
    fill(ranks, ranks+410, 0); // 初始化
    for (int i = 400; i >= 0; i --) { // 计算每个总分对应的排名
        if (isFirst && cnt[i] != 0) ranks[i] = 1, isFirst = false; // 第一个不为0的是rank-1
        else ranks[i] = ranks[i+1] + cnt[i+1];
    }
    isChangeRank = false; // 标记已更新
}
void query() { // 根据sid/name查询学生
    string s;
    while (cin >>s && s != "0") {
        set<int> query; // 存放要输出的学生标号(stuVec下标)，自动有序，按输入顺序排列
        if (isdigit(s[0])) { // sid
            if (sidMp.find(s) != sidMp.end()) query.insert(sidMp[s]);
        }
        else { // name
            if (nameMp.find(s) != nameMp.end()) query = nameMp[s];
        }
        if (isChangeRank) calRanks(); // 有插入或删除需重新计算排名，这里只是为了提高效率
        for (auto i : query) { // 按输入顺序输出结果
            auto p = stuVec[i];
            printf("%d %s %d %s", ranks[p.tot], p.sid.c_str(), p.cid, p.name.c_str());
            for (int j = 0; j < 4; j ++) printf(" %d", p.score[j]);
            printf(" %d %.2lf\n", p.tot, (double)p.tot / 4.0);
        }
        cout <<tips[opt] <<endl; // 提示语句
    }
}
void calStatistics() { // 计算统计结果
    vector<Statistics> vec(25);
    set<int> classes; // 存在的班级
    vec[0].num = sidMp.size(); // 综合统计（所有班级）,所有班级总人数
    for (auto kv : sidMp) { // 遍历所有学生
        auto p = stuVec[kv.second]; // 学生
        vec[p.cid].num ++; // 班级cid的总人数
        classes.insert(p.cid); // 记录存在的班级
        int cnt = 0; // 统计此人通过的数量(>=60)
        for (int i = 0; i < 4; i ++) {
            vec[p.cid].totScore[i] += p.score[i];
            vec[0].totScore[i] += p.score[i]; // 综合统计（所有班级）
            if (p.score[i] >= 60) {
                vec[p.cid].pass[i] ++; // 班级cid中i学科通过人数
                vec[0].pass[i] ++; // 综合统计（所有班级）,通过该课人数
                cnt ++; // 未挂科数量
            }
        }
        vec[p.cid].overall[cnt] ++; // 计算通过i科的人数
        vec[0].overall[cnt] ++; // 综合统计（所有班级）,通过i科人数
    }
    classes.insert(0); // 综合统计
    for (auto c : classes) { // 计算overall
        for (int i = 3; i >= 1; i --) vec[c].overall[i] += vec[c].overall[i+1];
    }
    info = vec; // 保存结果
}
void showStatistics() { // 显示统计数据
    int cid; cin >>cid;
    if (isChangeSta) calStatistics(); // 被改变，需先更新统计数据
    auto p = info[cid];
    for (int i = 0; i < 4; i ++) {
        cout <<courses[i] <<endl;
        double f;
        if (p.num == 0) f = 0.00; // 分母为0！！！
        else {
            f = (double)p.totScore[i] / p.num + 1e-5; // 加上损失精度
            f = floor(f*100 + 0.5) / 100; // 四舍五入，精确到百分位
        }
        printf("Average Score: %.2lf\n", f);
        printf("Number of passed students: %d\nNumber of failed students: %d\n\n", p.pass[i], p.num - p.pass[i]);
    }
    printf("Overall:\n");
    for (int i = 4; i >= 0; i --) {
        printf("Number of students who %s subjects: %d\n", stamess[i].c_str(), p.overall[i]);
    }
    puts(""); // 空行
}
int main() {
    do {
        printf(mainMenu); // 主界面
        scanf("%d", &opt);
        if (opt != 0) cout <<tips[opt] <<endl; // 提示信息
        switch (opt) {
            case 0: opt = -1; break;        // 结束
            case 1: add(); break;           // 增加
            case 2: remove(); break;        // 移除
            case 3: query(); break;         // 查询
            case 4: break;   // 显示排名
            case 5: showStatistics(); break; // 显示统计结果
        }
    } while (opt != -1);
    return 0;
}
```

## 习题4-1 UVA1589 Xiangqi

### 题目大意

给定[2,7]个红子，1个黑子将军，问黑子移动一步后，红子能否将军。

其中红子包括4类棋子：

+ 帅：红方格内水平/垂直移动一格或飞将（与将在同一列，且中间没有其它棋子阻隔）
+ 车：水平或垂直移动任意格
+ 炮：水平或垂直移动任意格，炮A若想吃棋子B，当且仅当二者之间仅有一个棋子
+ 马：走日字格8个方向，当存在马脚时对应两个方向无法跳转

### 思路分析

对于黑子将军，遍历四个可能的方向，在每个方向遍历所有红子的攻击，若存在某个方向所有红子均无法攻击到黑子将军，说明黑子将军不会被将，否则，会被将军。

+ 方向向量：为了便于模拟黑子将军的4个方向和马的8个方向，同时便于处理**马脚问题**（假设马遍历到第j个向量，那么j/2就是马脚向量），定义方向向量如下（注意二者对应关系）

```cpp
int gdict[4][2] = {{0,1},{0,-1},{1,0},{-1,0}}; // 将军4个方向
int hdict[8][2] = {{-1,2},{1,2}, {1,-2},{-1,-2}, {2,1},{2,-1}, {-2,-1},{-2,1}}; // 马8个方向
```

+ 同时定义`isCheck`标记黑子是否会被将军；定义`board[11][10]`，其中`board[i][j]=false`表示坐标`(i,j)`上不存在子。

```cpp
bool isCheck = false, board[11][10] = {false}; // 标记点是否有子
```

+ 定义`vector<Pos> red` ，存储红子坐标及类型信息，便于后续遍历

帅，车，炮模拟的关键在于判断到达将军位置的过程中经过多少颗棋子，因此设置水平和垂直计算函数，其中，调用函数前需保证将军和相应棋子在同一水平/垂直线上；具体实现时还需考虑黑子吃红子情况，由于默认黑子将军不记录board，因此对返回值多一步处理：

+ 水平间隔棋子计数：

```cpp
int hpos(int px, int py, int y) { // 水平方向：判断将军和当前棋子相差个数
    int ans = 0, l = min(py, y), r = max(py, y);
    for (int j = l; j <= r; j ++) if (board[px][j]) ans ++;
    return ans - board[px][py]; // 考虑吃红子情况
}
```

+ 垂直间隔棋子计数：

```cpp
int vpos(int px, int py, int x) { // 垂直方向：判断将军和当前棋子相差个数
    int ans = 0, l = min(px, x), r = max(px, x);
    for (int i = l; i <= r; i ++) if (board[i][py]) ans ++;
    return ans - board[px][py]; // 考虑吃红子情况
}
```

### 注意点

+ 测试用例不存在开局黑子将军可飞将红子帅的情况
+ 黑子将军可以吃红子！！！
+ 注意马脚判断和落子位置有效性判断

### AC代码（C++11，复杂模拟，象棋）

```cpp
#include<bits/stdc++.h>
using namespace std;
int gdict[4][2] = {{0,1},{0,-1},{1,0},{-1,0}}; // 将军4个方向
int hdict[8][2] = {{-1,2},{1,2}, {1,-2},{-1,-2}, {2,1},{2,-1}, {-2,-1},{-2,1}}; // 马8个方向
bool isCheck = false, board[11][10] = {false}; // 标记点是否有子
typedef struct Pos {
    char type; // 类型
    int x, y; // 坐标
    Pos(char _type=0, int _x=0, int _y=0) :  type(_type), x(_x), y(_y) {} // 构造函数
}Pos;
bool isLegal(int x, int y, int isG) { // 判断位置是否合法
    if (isG) return (x >= 1 && x <= 3) && (y >=4 && y <= 6); // 将军，可以吃红子
    else return (x >= 1 && x <= 10) && (y >= 1 && y <= 9); // 普通棋子
}
int hpos(int px, int py, int y) { // 水平方向：判断将军和当前棋子相差个数
    int ans = 0, l = min(py, y), r = max(py, y);
    for (int j = l; j <= r; j ++) if (board[px][j]) ans ++;
    return ans - board[px][py]; // 考虑吃红子情况
}
int vpos(int px, int py, int x) { // 垂直方向：判断将军和当前棋子相差个数
    int ans = 0, l = min(px, x), r = max(px, x);
    for (int i = l; i <= r; i ++) if (board[i][py]) ans ++;
    return ans - board[px][py]; // 考虑吃红子情况
}
int main() {
    int n,  x, y, tx, ty;
    char type;
    while (scanf("%d %d %d", &n, &x, &y) == 3 && n != 0) {
        vector<Pos> red; // 存储红子坐标信息
        fill(board[0], board[0]+110, 0); // 棋盘初始化，仅记录是否有子
        while (n --) {
            cin >>type >>tx >>ty;
            board[tx][ty] = true; // 标记
            red.push_back(Pos{type, tx, ty}); // 存储
        }
        int px = x, py = y; // 将军移动可能达到的位置
        for (int i = 0; i < 4; i ++) { // 黑子将军4个方向
            px = x + gdict[i][0]; py = y + gdict[i][1]; // 黑方将军移动后的位置
            if (isLegal(px, py, 1)) { // 将军位置合法
                isCheck = false; // 初始化
                for (auto& p : red) { // 遍历所有红子
                    if (p.type == 'G' && py == p.y && vpos(px, py, p.x) == 1) isCheck = true; // 可杀死
                    else if (p.type == 'R' && (py == p.y && vpos(px, py, p.x) == 1 || px == p.x && hpos(px, py, p.y) == 1)) isCheck = true;
                    else if (p.type == 'C' && (py == p.y && vpos(px, py, p.x) == 2 || px == p.x && hpos(px, py, p.y) == 2)) isCheck = true;
                    else if (p.type == 'H') {
                        for (int j = 0; j < 8 && !isCheck; j ++) { // 马8个方向
                            int hx = p.x + hdict[j][0], hy = p.y + hdict[j][1]; // 日字格
                            int gx = p.x + gdict[j/2][0], gy = p.y + gdict[j/2][1]; // 马脚
                            if ((hx == px && hy == py) && isLegal(gx, gy, 0) && !board[gx][gy]) isCheck = true;
                        }
                    }
                    if (isCheck) break; // 一发现可以杀死立刻退出，进入下一个方向
                }
                if (!isCheck) break; // 可以不死，找到存活机会
            }
        }
        printf("%s\n", isCheck ? "YES" : "NO");
    }
    return 0;
}
```

## 习题4-2 UVA201 Squares

### 题目大意

给定n*n个点和m条边构成的图形，问该图形中含各类长度的正方形个数。

### 思路分析

最朴素的思想，枚举所有可能的正方形长度l，再枚举所有可能的正方形左上角坐标，依次判断，时间复杂度为O(n^3），伪代码如下：

```python
for l~[1,n]: // 正方形边长[1,n]
	for i~[1,n-l]: // 正方形左上角坐标范围
		for j~[1,n-l]:
			判断左上角(i,j)能否构成正方形
```

已知左上角便可轻易推出其余三角，因此如何根据已知4顶点判断能否构成正方形成为关键，两种思路：

+ 暴力遍历：每次都遍历4顶点构成的4条边，查看是否两两间连通，显然效率太低
+ 最长距离：计算每个点向右/下可达到的最长距离。但左上角为(i,j)时，仅需判断左上角的向右和向下，右上角向下，左下角向右的最长距离是否大于等于l即可。时间复杂度O(n^2)，查询O(1)。

### 算法设计

+ 定义二维数组`int h[10][10]={0}, v[10][10]={0}` ，分别存储水平和垂直连线关系
+ 定义二维数组`int right[10][10]={0}, down[10][10]={0} `分别存储当前点向右和向下所能到达最远距离
+ 定义一维数组`int num[10]={0}` 记录每种长度正方形个数，其中`num[0]=0`表示无符合的正方形
+ 其中向右和向下所能到达最远距离，可如下计算

对于每一行，从右数第二个点向左遍历，若当前点到右侧点无连线，当前点置0；否则为右侧点个数+1

对于每一列，从下数第二个点向上遍历，若当前点到下侧点无连线，当前点置0,；否则为下侧点个数+1

```cpp
for (int i = 1; i <= n; i ++) { // 每一行列
    for (int j = n-1; j >= 1; j --) { // 从右侧/下侧数第二个开始
        right[i][j] = (h[i][j] == j+1) ? right[i][j+1]+1 : 0; // 行：左->右
        down[j][i] = (v[j][i] == j+1) ? down[j+1][i]+1 : 0; // 列：上->下
    }
}
```

### AC代码（C++11，最长距离/前缀和）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, cnt = 0, a, b;
char ch;
int main() {
    while (cin >>n >>m) {
        int h[10][10]={0}, v[10][10]={0}; // 存储水平和垂直连线
        while (m --) { // 输入
            cin >>ch >>a >>b;
            if (ch == 'H') h[a][b] = b+1;
            else v[b][a] = b+1; // 注意顺序
        }
        int right[10][10]={0}, down[10][10]={0}, num[10]={0}; // 向右/下最远可达距离，每种长度正方形计数
        for (int i = 1; i <= n; i ++) { // 每一行列
            for (int j = n-1; j >= 1; j --) {
                right[i][j] = (h[i][j] == j+1) ? right[i][j+1]+1 : 0; // 行：左->右
                down[j][i] = (v[j][i] == j+1) ? down[j+1][i]+1 : 0; // 列：上->下
            }
        }
        for (int l = 1; l <= n; l ++) { // 遍历每个正方形长度：l:[1,n]
            for (int i = 1; i <= n - l; i ++) { // x:[1,n-l]
                for (int j = 1; j <= n - l; j ++) { // y:[1,n-l]
                    if (right[i][j] >= l && down[i][j] >= l && down[i][j+l] >= l && right[i+l][j] >= l) num[l] ++, num[0] = 1; // num[0]标记存在解
                }
            }
        }
        if (cnt != 0) printf("\n**********************************\n\n"); // 以下为输出
        printf("Problem #%d\n\n", ++cnt);
        for (int i = 1; i <= n; i ++) 
            if (num[i] != 0) printf("%d square (s) of size %d\n", num[i], i);
        if (num[0] == 0) printf("No completed squares can be found.\n");
    }
    return 0;
}
```

## 习题4-3 UVA220 Othello

### 题目大意

给定黑白子的棋盘，根据顺序的操作输出结果，假设当前下棋方为Now，对手为rival，其中操作包含三类：

+ L：从左到右，从上到下打印所有合法位置

所谓合法位置，比如点A，若放A点为黑子，以A为中心，8个方向只要存在一个方向的尾部为黑子B（注意该方向必须有连续的棋子）

+ Mxy：若Now方存在合法位置，放置(x,y)为Now，并将其夹住的棋子改为它的颜色（注意只改变它影响的）；否则下棋者转为rival，继续执行Mxy。最后都对换下棋者为另一方
+ Q：打印棋盘，退出

### 算法设计

直接模拟，关键在于如何判断一个点的8个方向是否能夹子，因此定义方向向量如下：

```cpp
int dict[8][2] = {{0,1},{1,0},{-1,0},{0,-1},{-1,1},{1,-1},{1,1},{-1,-1}}; // 8个方向
```

定义如下函数，模拟单个点8个方向的移动，其中isMoved控制是否要改变被夹住的棋子颜色，返回值为1表示该位置合法。

```cpp
int simulate(int x, int y, int isMoved)  // 模拟单个点8个方向的移动，isMoved控制是否改变值
```

### 注意点

+ 输出黑白棋子个数时，注意对齐宽度为2
+ 两组输出间需空行，最后一行后不需要

### AC代码（C++，棋盘模拟）

```cpp
#include<bits/stdc++.h>
using namespace std;
int dict[8][2] = {{0,1},{1,0},{-1,0},{0,-1},{-1,1},{1,-1},{1,1},{-1,-1}}; // 8个方向
int n;
char now, rival; // 当前下棋者，对手
string board[9], s; // 棋盘，从1开始
void showResult() { // 打印棋盘
    for (int i = 1; i <= 8; i ++) cout <<board[i].substr(1) <<endl;
}
bool isLegal(int x, int y) { // 判断位置是否合法
    return (x >= 1 && x <= 8) && (y >= 1 && y <= 8);
}
int simulate(int x, int y, int isMoved) { // 模拟单个点8个方向的移动，isMoved控制是否改变值
    int ret = 0, legal=0,  px, py, cntb = 0, cntw = 0;
    for (int i = 0; i < 8; i ++) { // 8个方向
        vector<pair<int,int> > pos; ret = 0; // 存储经过的位置
        px = x + dict[i][0]; py = y + dict[i][1]; // 移动后位置
        if (isLegal(px, py) && board[px][py] == rival) { // 对应方向存在对手棋子
            while (isLegal(px, py)) { // 在此方向尽头是否存在now子
                pos.push_back({px,py}); // 保存路径
                px = px + dict[i][0]; py = py + dict[i][1];
                if (isLegal(px, py) && board[px][py] != rival) { // 发现非对手棋子
                    if (board[px][py] == now) { // 
                        ret = legal = 1; // 用于返回
                        if (isMoved == 1) { // 移动命令，标记点
                            for (auto p : pos) board[p.first][p.second] = now;
                            board[x][y] = now; // 新加入选择的点
                        }
                        break;
                    }
                    else break;
                }
            }
            if (isMoved == 0 && legal == 1) break;
        }
    }
    for (int i = 1; i <= 8 && isMoved == 1; i ++) { // 统计个数 
        for (int j = 1; j <= 8; j ++) {
            if (board[i][j] == 'B') cntb ++;
            else if (board[i][j] == 'W') cntw ++;
        }
    }
    if (isMoved == 1) printf("Black - %2d White - %2d\n", cntb, cntw); // 对齐：2个宽度
    return legal;
}
int move(int isList) { // 模拟遍历移动，isList控制是否打印合法位置信息
    int cnt = 0;
    for (int i = 1; i <= 8; i ++) {
        for (int j = 1; j <= 8; j ++) {
            if (board[i][j] == '-' && simulate(i, j, 0) == 1) { // 该点合法
                if (isList == 1) { // 控制输出
                    if (cnt != 0) printf(" ");
                    printf("(%d,%d)", i, j); 
                }
                cnt ++;
            }
        }
    }
    if (cnt != 0 && isList == 1) puts("");
    if (cnt == 0 && isList == 1) printf("No legal move.\n"); // 无合法移动
    return cnt; // 合法点数量
}
int main() {
    cin >>n; getchar(); // 吸收空行!!
    for (int k = 0; k < n; k ++) {
        if (k != 0) puts(""); // 两组输出间空行
        for (int i = 1; i <= 8; i ++) getline(cin, s), board[i] = "-"+s; // 从1开始
        cin >>now; // 当前玩家
        rival = (now == 'W') ? 'B' : 'W'; // 对手
        while (cin >>s && s[0] != 'Q') {
            if (s[0] == 'L') move(1);
            else if (s[0] == 'M') {
                if (move(0) == 0) { // 无合法位置
                    swap(now, rival); // 当前没有合法移动
                }
                simulate(s[1]-'0', s[2]-'0', 1);
                swap(now, rival); // 交换下棋者
            }
        }
        showResult(); getchar(); // 吸收空行
    }
    return 0;
}
```

## 习题4-4 UVA253 Cube painting

### 题目大意

现有固定编号（1~6）的立方体，给定两个上色序列A，B（仅由红蓝绿三种颜色构成），问A能否通过x,y,z三个旋转轴旋转得到B（不考虑镜像，即轴对称）

### 思路分析

有很多人通过**两个正方体的3组对立面是否一致**来判断结果，其实有bug，可如下**构造反例**：

+ 构造A：rbg各出现两次，且对立面均不同色
+ 构造B：选择一个对立面交换颜色

```cpp
grbrgbggbrrb // false, 仅判断3组对立面相等的反例
```

因此，可通过暴力枚举，解决问题，但还需多一些思考和推导，可得到结论1：

> 结论1：若正方体A，B上色方案相同，那么A必定可在3次旋转得到B

+ 旋转轴共3个（x,y,z），每个轴共有4个旋转角度（0,90,180,270）

可将三个旋转轴看成空间基向量，任意的向量均可由基向量构造出来，其中旋转角度就是基向量前的常数

> 结论2：B=d1\*x+d2\*y+d3*z // 类似这种表达，(d1,d2,d3)表示绕每个轴旋转角度

根据结论1可知，旋转组合顺序与结果无关，4\*4*4=64种情况必定包含了所有的旋转结果，因此，对于每个判断，仅需枚举64种旋转即可。

### 算法设计

对于旋转，可用一个轮换来模拟（类似约瑟夫环过程），以下分别表示绕3个轴转动时会轮换改变的序列

```cpp
int a[3][4] = {{2,4,5,3}, {2,6,5,1}, {1,4,6,3}}; // 3个旋转轴对应改变的轮换序列
```

用string存储上色序列，定义旋转函数`rotate`，表示正方体绕i轴旋转j*90度。

```cpp
void rotate(string& sr, int i, int j) { // sr绕i轴旋转j*90度
    string s = sr;
    for (int k = 0; k <= 3; k ++) { // 轮换：模拟旋转
        sr[a[i][k]-1] = s[a[i][(j+k)%4]-1]; // 从0开始存储,正方体标号从1开始
    }
}
```

### 测试用例设计

```cpp
rbgggrrggbgr // True, 1轴旋转
rrrbbbrrbbbr // false
rbgrbgrrrrrg // false
rbgggrrgggbr // true，全等2
rggbgrrgggbr // true，
gggggggggggg // true，全等1
rggbgrggrrgb // True，2轴旋转
rggbgrggrrbg // True，3轴旋转
ggrrgbggrrbg // True, 1轴旋转
rbgggrgrbgrg // True, 3轴4次旋转
rbgggrgbrrgg // True, 3轴4次旋转
grbrgbggbrrb // false, 仅判断3组对立面相等的反例
```

### AC代码（C++11，判定条件，中级模拟，推导思考，轮换）

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[3][4] = {{2,4,5,3}, {2,6,5,1}, {1,4,6,3}}; // 3个旋转轴对应改变的轮换序列
string sa, sb, st;
void rotate(string& sr, int i, int j) { // sr绕i轴旋转j*90度
    string s = sr;
    for (int k = 0; k <= 3; k ++) { // 轮换：模拟旋转
        sr[a[i][k]-1] = s[a[i][(j+k)%4]-1]; // 从0开始存储,正方体标号从1开始
    }
}
int main() {
    while (cin >>st) {
        sa = st.substr(0,6); sb = st.substr(6);
        bool isSame = false; // 判断是否存在一样的情况
        for (int i = 0; i < 4 && !isSame; i ++) { // x轴4种转动角度
            for (int j = 0; j < 4 && !isSame; j ++) { // y轴
                for (int k = 0; k < 4 && !isSame; k ++) { // z轴
                    st = sb; // 更新
                    rotate(st, 0, i); // x轴转i*90角度
                    rotate(st, 1, j); // y轴转j*90角度
                    rotate(st, 2, k); // z轴转k*90角度
                    if (st == sa) isSame = true;
                }
            }
        }
        printf("%s\n", isSame ? "TRUE" : "FALSE");
    }
    return 0;
}
```

## 习题4-5 UVA1590 IP Networks

### 题目大意

给定若干个IP地址，求包含所有IP的最小IP网络。

+ IP地址：4个字节，每个字节用十进制表示，并用点分割，形如`xxx.xxx.xxx.xxx`，无前导0，每个十进制在[0,255]
+ IP网络：由子网地址和子网掩码构成，二者形式和IP地址一样，二者存在制约关系，假设有n（处于[0,32])，那么在二者的二进制表示中
  + 子网掩码的前n位为1，后32-n位为0
  + 子网地址的前n位任意，后32-n位为0
+ 假设n=24，子网地址假设为`198.123.123.0`，子网掩码`255.255.255.0`，那么`198.123.123.0~198.123.123.255`均属于该IP网络

### 思路分析

可先找出所有IP地址中最大和最小值，再计算最大小值的二进制形式的最长公共子串长度len（**从头开始**），接着将最小值二进制低32-n置0，构造前n位为1，后32-n位为0的子网掩码。

+ 比较大小：可用stringstream分割IP地址，并计算出32位的数字，从而得到最大和最小值
+ 位处理：可用`bitset`完成二进制字符串和数值间相互转化，每个位的0/1设置

### AC代码（C++11，bitset，位运算）

```cpp
#include<bits/stdc++.h>
using namespace std;
void binstrToIP(string s) { // 二进制字符串转为IP形式
    for (int i = 0; i < 4; i ++) {
        bitset<8> bt(s.substr(i*8,8));
        printf("%u%s", bt.to_ulong(), i == 3 ? "\n" : ".");
    }
}
int main() {
    int n;
    while (cin >>n) {
        string smax, smin, smask, s, st;
        unsigned umin=UINT32_MAX, umax = 0;
        while (n --) {
            cin >>s;
            stringstream input(s);
            unsigned uint = 0;
            while (getline(input, st, '.')) { // 分割每个部分
                uint = (uint << 8) + (unsigned)stoi(st); // 256进制
            }
            if (umin >= uint) umin = uint, smin = s; // 最小值
            if (umax <= uint) umax = uint, smax = s; // 最大值
        }
        bitset<32> bmin(umin), bmax(umax), bmask(0xffffffffu);
        smin = bmin.to_string(); smax = bmax.to_string(); // 转为2进制字符串
        int cnt = 0;
        for (int i = 0; i < 32; i ++) { // 统计从头开始的公共子串长度
            if (smin[i] == smax[i]) cnt ++;
            else break;
        }
        for (int i = 0; i < 32-cnt; i ++) { // 设置IP地址和掩码低32-cnt位为0
            bmin.reset(i); bmask.reset(i); // 注意bitset逆序存储
        }
        binstrToIP(bmin.to_string()); binstrToIP(bmask.to_string());
    }
    return 0;
}
```

## 习题4-6 UVA508 Morse Mismatches

### 思路分析

已知字符编码表，接受的单词表（context），现给出摩尔斯电码，根据规则解码。规则如下：

+ 1个精确匹配：直接输出
+ 多个精确匹配：输出**字典序最小/context中最前面的**都对（原题描述有些歧义fewest character长度最短？）
+ 0个精确匹配：找出**最小模糊匹配**，即两个字符串存在这样的关系：`a是b的子串/b是a的子串`，且二者长度相差最小（若有多个满足，输出任意单词即可）

### 算法设计

+ **惯性思维**：想直接从摩尔斯密码来解码，那么必须dfs许多情况，过于复杂。

+ **逆向思维**：根据给定的字符编码表和context，可以计算出每个单词的摩尔斯编码，到时直接进行匹配即可

因此，定义`string codetbl[200]`存储字符编码表，其中`code[ch]`表示字符ch对应的编码串。

定义`map<string, vector<string> > ctxt;`，其中`ctxt[s]`表示摩尔斯编码串s对应的可能单词，单词在vector中按输入顺序存放，若改为set，则按字典序排列

接着依次输入摩尔斯密码，根据解码规则处理即可。

### 注意点

+ 题意不明，经测试，多个精确匹配可输出**字典序最小/context中最前面的**
+ 模糊匹配一定存在，因为题目仅考虑在字符串末尾增加或减少若干个字符

### AC代码（C++11，解密模拟，逆向思维，map）

```cpp
#include<bits/stdc++.h>
using namespace std;
string codetbl[200], code, s;
char ch;
// map<string, set<string> > ctxt; // 上下文，字典序排列
map<string, vector<string> > ctxt; // 上下文，输入顺序排列
int main() {
    while (cin >>ch && ch != '*') {
        cin >>code; codetbl[ch] = code;
    }
    while (cin >>s && s != "*") {
        string st;
        for (auto c : s) st += codetbl[c];
        // ctxt[st].insert(s); // 字典序排列
        ctxt[st].push_back(s);
    }
    while (cin >>s && s != "*") {
        if (ctxt.find(s) != ctxt.end()) { // 存在
            cout <<*ctxt[s].begin();
            if (ctxt[s].size() > 1) cout <<"!";
        }
        else { // 不存在
            int minlen = 0x3ffff; string ans;
            for (auto p : ctxt) {
                if (s == p.first.substr(0,s.size()) || p.first == s.substr(0,p.first.size())) { // 前缀
                    int i = abs((long)p.first.size()-(long)s.size()); 
                    if (minlen >= i) {
                        minlen = i;
                        ans = *p.second.begin();
                    }
                }
            }
            cout <<ans<<"?";
        }
        puts("");
    }
    return 0;
}
```

## 习题4-7 UVA509 RAID

### 题目大意

给定d个硬盘的位数据，每个硬盘有b块，每块有s位，因此一个硬盘有s*b位01x数据，其中x表示缺失位。在给定奇偶校验位p。

奇偶校验位：若将每个硬盘数据竖直存放，那么p=所有硬盘处于同一行的每一位的异或结果

先在问给定的硬盘是否有效，有效还需输出表示信息。

+ 无效
  + 缺失过多：同一行中缺失1位以上（>1)
  + 校验位错误：同一列未缺失，但异或值不等于p
+ 其余均为有效，可在数据末尾补0凑齐4整倍数，输出16进制字符串

### 算法设计

定义`string disks[10]`,其中` disks[i]`表示第i块硬盘，按列遍历每一行的bit，记录x个数并计算异或值，根据无效判断处理。

+ 异或计算：令ex=p，将ex与遍历过程中每个非x异或，若不存在x，那么ex==0表示合法；若存在一个x，ex即为x的值；否则非法

+ 判断奇偶校验块：假设行列值`(i,j)`，若`i==j%d`，说明当前块为奇偶检验块

### 注意点

+ 输出数据时是在2进制字符串**末尾补0**
+ 可用bitset实现二进制字符串和十进制数值转换

### 补充测试用例

**输入**

```cpp
6 2 5
E
0001011111
0110111011
1011011111
1110101100
0010010111
0000000000

3 2 5
E
0001111111
0111111011
xx11011111

3 5 1
O
11000
11xxx
x1111

3 5 1
O
11000
11xxx
x1x11

3 5 1
E
11111
11xxx
x1111

0
```

**输出**

```cpp
Disk set 1 is valid, contents are: 6C1E8793B4FC0
Disk set 2 is invalid.
Disk set 3 is valid, contents are: C7C
Disk set 4 is invalid.
Disk set 5 is invalid.
```

### AC代码（C++11，数组模拟，进制转换，bitset）

```cpp
#include<bits/stdc++.h>
using namespace std;
char parity, trans[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
int d, s, b, num = 0;
string disks[10]; // disks[i]表示第i块硬盘
bool isValid() { // 判断是否有效并计算缺失位
    bool ret = true;
    for (int j = 0; j < disks[0].size() && ret; j ++) { // j列
        int idx=-1, cnt=0, ex=(parity == 'E') ? 0 : 1; // x的下标，当前列x个数，列异或值
        for (int i = 0; i < d; i ++) { // i行
            if (disks[i][j] == 'x') idx = i, cnt ++; // 当前bit是x
            else ex ^= disks[i][j] - '0'; // 非x，计算异或值
        }
        if (cnt == 1) disks[idx][j] = ex + '0'; // 仅1个x，可计算恢复
        if (cnt >= 2 || (cnt == 0 && ex != 0)) ret = false; // 大于1个x||当前列和校验位异或值不为0
    }
    return ret; // 返回结果
}
void showContent() { // 显示恢复结果
    string ans;
    for (int j = 0; j < b; j ++) { // 第j列
        for (int i = 0; i < d; i ++) { // 第i行
            if (i != j % d) ans += disks[i].substr(j*s, s); // j%d==i判断是否为校验位
        }
    }
    ans += string((ans.size() % 4 == 0) ? 0 : (4-(ans.size()%4)), '0'); // 末尾补0凑成4整倍数
    for (int i = 0; i < ans.size() / 4; i ++) { // 转为16进制输出
        bitset<4> bt(ans.substr(i*4,4)); // bitset完成2进制字符串转换10进制
        cout <<trans[bt.to_ulong()];
    }
    cout <<endl;
}
int main() {
    while (cin >>d && d != 0) {
        cin >>s >>b >>parity;
        for (int i = 0; i < d; i ++) cin >>disks[i];
        bool valid = isValid();
        if (valid) {
            printf("Disk set %d is valid, contents are: ", ++num);
            showContent();
        }
        else printf("Disk set %d is invalid.\n", ++num);
    }
    return 0;
}
```

## 习题4-8 UVA12108 Extraordinarily Tired Student

### 题目大意

给定若干个学生初始状态，根据规则计算他们全部清醒的时刻，若不存在，输出-1，规则如下：

+  三元组（a，b，c）分别表示一个学生的**清醒持续时间**，**睡眠持续时间**，**初始时刻**
+ 睡眠时刻结束后立刻进入清醒时刻，而清醒时刻即将结束时，若当前睡觉人数**严格大于**清醒人数，则进入睡觉时刻，否则继续清醒时刻

### 算法设计

定义`vector<int> stat, tmp, as, bs; `分别存储当前状态，中间变量，清醒持续时间，睡眠持续时间。假设当前为第i个人，可如下判定状态

+ 清醒状态：`1<=stat[i]<=as[i]`
+ 睡眠状态：`as[i]<stat[i]<=as[i]+bs[i]`

为了**处理死循环**，即所有人永远无法同时清醒，可用`set<vector<int> > _set;`存储每个时刻状态序列，当出现重复，即找到循环节，输出-1

核心算法伪代码描述如下：

```cpp
for 每个时刻t:
	for 每个学生:
		用以上判定方法统计清醒人数wknum
	if wknum == n: // 全部清醒
		输出结果t
	else: // 未全部清醒
		for 每个学生：
			if stat[i]==as[i]: // 清醒结束时刻，需判断下一个时刻是清醒还是睡眠
				if wknum*2<n:
					stat[i] = as[i]+1; // 睡觉，睡觉人数大于清醒
				else：
					stat[i] = 1; // 继续清醒
			else:
				if stat[i]==as[i]+bs[i]: // 周期结束，回头
					stat[i]=1
				else:
					stat[i]++ // 往后走即可
		
```

### AC代码（C++11，循环节，序列模拟）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a, b, c, num=0;
int main() {
    while (cin >>n && n != 0) {
        set<vector<int> > _set; // 死循环判重
        vector<int> stat, tmp, as, bs; // 当前状态，中间变量，清醒持续时间，睡眠持续时间
        for (int i = 0; i < n; i ++) {
            cin >>a >>b >>c;
            as.push_back(a); bs.push_back(b); // 存储左右区间
            stat.push_back(c); // 第一轮状态
            _set.insert(stat); // 保存状态序列
        }
        int cnt = 1, ans = -1;
        while (true) {
            int wknum = 0; // 清醒人数
            for (int i = 0; i < n; i ++) { // 计算清醒人数
                if (1 <= stat[i] && stat[i] <= as[i]) wknum ++;
            }
            if (wknum == n) { // 全部清醒
                ans = cnt;
                break; // 直接结束
            }
            cnt ++;
            tmp = stat; // 开始模拟
            for (int i = 0; i < n; i ++) { // n个人
                if (tmp[i] == as[i]) { // 准备睡觉
                    if (wknum * 2 < n) stat[i] = as[i]+1; // 睡觉人数大于清醒
                    else stat[i] = 1; // 继续清醒
                }
                else stat[i] = (stat[i] == as[i]+bs[i]) ? 1 : stat[i]+1; // 下一个状态 
            }
            if (_set.find(stat) == _set.end()) _set.insert(stat); 
            else break; // 出现重复，死循环
        }
        printf("Case %d: %d\n", ++num, ans);
    }
    return 0;
}
```

## 习题4-9 UVA1591 Data Mining

### 思路分析

>  纸老虎题目，看着很难，其实读懂题目后很简单

题目背景就是为了提高访问数组内容的**时间和空间**效率，只需找到使K最小的A和B，若存在多解，则按KAB顺序取字典序最小者。

#### 时间优化（乘除变加减）

假设有P和Q两个结构体数组，各自记录的大小分别为Sp和Sq。通常访问第i个元素是通过如下乘法实现，但在计算机中加减法效率比乘除法高许多，因此可将其转换为加减法运算来访问

```cpp
P[i]=Sp*i // 乘法
Q[i]=Sq*i // 乘法

P[i]=P[i-1]+Sp // 加法
P[i]=P[i+1]-Sp // 减法
```

然而Q转换稍微复杂些，需按如下公式计算，同样达到时间效率提高的目的

```cpp
Q(i) = (P(i) + P(i) << A) >> B //公式(1)
```

#### 空间优化

假设确定A和B，数组有N个元素（0~N-1），那么数组所需空间：

```
K=Q(n-1)+Sq // 第n-1个元素偏移+一个记录大小
```

因此，不同A和B对应的K不同，由于题目说明整数范围内可解决，所以A,B取值范围：`[0,31]`（32位最多移位31），只要遍历32*32种可能，选出最小K对应的A，B即可

+ **如何判断A和B合法？**

由公式（1）可知Q(i)为等差数列，只要公差d>=Sq，就能够存储数组Q，因此，推导可得：

```
d=Q(i+1)-Q(i)=(P(i+1)-P(i))(1+2^A)/(2^B)=Sp(1+2^A)/(2^B) >= Sq
//为了计算过程不溢出且避免除法误差，变换不等式如下
Sp+(Sp<<A) >= Sq<<B  // 注意C语言中移位优先级低于四则运算
```

### 注意点

+ 注意整型移位范围在[0,31]，可能存在溢出，可用long long类型避免该问题
+ 判断AB是否合法时注意变换不等式，避免除法和乘法溢出
+ 移位优先级低于四则运算，注意使用括号

### AC代码（C++11）

#### 直接比较版（19行代码）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL; // 避免移位溢出
int main() {
    LL n, Sp, Sq;
    while (cin >>n >>Sp >>Sq) {
        LL K=LONG_LONG_MAX, A, B;
        for (int i = 0; i < 32; i ++) { // A
            for (int j = 0; j < 32; j ++) { // B
                if (((Sp + (Sp << i)) >= (Sq << j)) && (K > ((Sp*(n-1)+((Sp*(n-1))<<i))>>j)+Sq)) { // 公差大于Sq且k更大
                    K = ((Sp*(n-1)+((Sp*(n-1))<<i))>>j)+Sq; // 更新KAB
                    A = i; B = j;
                }
            }
        }
        printf("%lld %lld %lld\n", K, A, B); // 第一个即符合条件
    }
    return 0;
}
```

#### sort排序版（28行代码）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL; // 避免移位溢出
typedef struct KAB {
    LL K, A, B;
    KAB(LL _k, LL _A, LL _B) : K(_k), A(_A), B(_B){} // 默认构造
}KAB;
bool cmp(const KAB& a, const KAB& b) { // 按KAB顺序取字典序小者
    if (a.K != b.K) return a.K < b.K; // 取K小
    else if (a.A != b.A) return a.A < b.A; // 取A小
    else return a.B < b.B; // 取B小
}
LL n, Sp, Sq;
int main() {
    while (cin >>n >>Sp >>Sq) {
        vector<KAB> kab; // 存储所有可能值
        for (int i = 0; i < 32; i ++) { // A
            for (int j = 0; j < 32; j ++) { // B
                if ((Sp + (Sp << i)) >= (Sq << j)) { // 公差大于Sq
                    kab.push_back({((Sp*(n-1)+((Sp*(n-1))<<i))>>j)+Sq, i, j}); // 移位优先级低于=-*/
                }
            }
        }
        sort(kab.begin(), kab.end(), cmp); // 排序
        printf("%lld %lld %lld\n", kab[0].K, kab[0].A, kab[0].B); // 第一个即符合条件
    }
    return 0;
}
```

## 习题4-10 UVA815 Flooded

### 题目大意

给定由m*n个**面积为100的正方形小网格**构成的大网格，同时给定每个小网格高度，大网格四周有无限高的边界，问往大网格中灌水cubic，求**水的高度**和**淹没小网格的百分比**（水位**严格大于**网格算淹没）

### 思路分析

定义` vector<int> a(m*n+2);`，从1开始存储1-m\*n个小网格的高度，为了处理淹没所有小网格的情况，令` a[m*n+1] = 0x7ffff;`，这里值不可太大，否则在计算中容易溢出。

将a从小到达排序，遍历a，计算前缀和，即`a[i]+=a[i-1]`，`a[i]`表示前i个小网格高度和。

核心算法伪代码如下：

```cpp
遍历a，当前下标为i（也表示底边长）
	if 用当前长方形面积-当前所有小网格面积>=cubic： // 找到第一个满足的底边
		计算高度和百分比
```

### 注意点

+ 注意浮点误差：计算过程中尽量用乘法，避免除法，cubic体积不用先除以100，而是让其它的乘以100
+ a数组最后一个值大小需适中，太大会导致计算的中间结果溢出
+ 四舍五入，可用round函数，注意需精确到千分位

### 补充测试用例

**样例输入**

```cpp
3 3
25 37 45
51 12 34
94 83 27
100000

1 1
10
1000

1 1
-10
100

2 1
-10 10
1000

2 1
-10 10
1900

3 1
10 -10 5
2000

3 1
-6
-5
-4
301

0 0
```

**样例输出**

```cpp
Region 1
Water level is 156.44 meters.
100.00 percent of the region is under water.

Region 2
Water level is 20.00 meters.
100.00 percent of the region is under water.

Region 3
Water level is -9.00 meters.
100.00 percent of the region is under water.

Region 4
Water level is 0.00 meters.
50.00 percent of the region is under water.

Region 5
Water level is 9.00 meters.
50.00 percent of the region is under water.

Region 6
Water level is 7.50 meters.
66.67 percent of the region is under water.

Region 7
Water level is -4.00 meters.
100.00 percent of the region is under water.

```

### AC代码（C++11，sort，补面积做差，浮点误差处理）

```cpp
#include<bits/stdc++.h>
using namespace std;
int m, n, cubic, num = 0;
int main() {
    while (cin >>m >>n && m != 0) {
        vector<int> a(m*n+2); a[m*n+1] = 0x7ffff; // 太大会溢出
        for (int i = 1; i <= m*n; i ++) cin >>a[i];
        cin >>cubic; // 体积
        sort(a.begin()+1, a.end()); // 从小到大排序
        for (int i = 2; i <= m*n; i ++) a[i] += a[i-1]; // a[i]表示前i个长度和
        double ans1, ans2;
        for (int i = 1; i <= m*n; i ++) {
            if (((i+1)*(a[i+1]-a[i]) - a[i+1])*100 >= cubic) { // 必须用乘法，除法会产生误差
                ans1 = (double)(cubic + a[i]*100) / (i*100); // 高度，先乘后除
                ans2 = (double)i / (m*n); // 百分比
                break;
            }
        }
        printf("Region %d\nWater level is %.2lf meters.\n", ++num, round(ans1*100)/100);
        printf("%.2lf percent of the region is under water.\n\n", round(ans2*10000)/100);
    }
    return 0;
}
```


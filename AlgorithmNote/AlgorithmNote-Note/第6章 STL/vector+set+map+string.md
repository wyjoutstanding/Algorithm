# 《算法笔记上机训练实战指南》习题报告

### 作者：wuyangjun

### 时间：2019/8/7~8/8

### 主题：vector+set+string+map

---



[TOC]

## vector常见用法

### [A1039 Course List for Student](https://pintia.cn/problem-sets/994805342720868352/problems/994805447855292416)

#### 思路

​		该题正常思路是：读取每一门可所有的选课学生，然后将该课程编号加入所有选择该门课的学生中去，这样最后就可以根据学生来查询选课情况。

​		为了解决学生以姓名方式给出的问题，第一反应是利用STL的map实现姓名和学生编号之间的映射（现在PAT时间限制是600ms，只要用scanf/printf时间可达256ms），从前此题时间限制为200ms，最后一个测试点STL的map无论如何都会超时。

​		如何解决超时问题？观察到姓名的格式：三个[A,Z]的大写字母+一个[0,9]的数字，因此可以使用散列，最关键一步在于将名字数值化，根据名字的固定格式可知至少需要26\*26\*26\*10个位置才能存放该散列。转换思路：前三个大写字母按照26进制转换得到一个中间结果，再将中间结果和最后一个数字按照10进制转换为数值。这样一定不会有冲突。代码如下：

```c++
int getId(char *str) {
    int len = strlen(str);
    int id = 0;
    // 类似26进制
    for(int i = 0; i < len - 1; i ++) {
        id = id * 26 + (str[i] - 'A');
    }
    // 10进制
    id = id * 10 + (str[len - 1] - '0');
    return id;
}
```

​		下面给出字符串哈希法和STL的map实现代码，注意使用map时必须用scanf/printf来输入输出，否则最后一个样例会超时。

#### C++(字符串哈希)

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-07 14:30:31
 * @LastEditTime: 2019-08-07 14:49:49
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 26 * 26 * 26 * 10 + 1;
vector<int> hashTable[maxn];
int hNum = 0;
// 3个大写一个数字的字符串转换为数值
int getId(char *str) {
    int len = strlen(str);
    int id = 0;
    // 类似26进制
    for(int i = 0; i < len - 1; i ++) {
        id = id * 26 + (str[i] - 'A');
    }
    // 10进制
    id = id * 10 + (str[len - 1] - '0');
    return id;
}
// 按学生名建立到课程序列的映射
int readData() {
    int N, K;
    scanf("%d %d", &N, &K);
    int idx, n;
    for(int i = 0; i < K; i ++) {
        scanf("%d %d", &idx, &n);
        char name[30];
        for(int i = 0; i < n; i ++) {
            scanf("%s", name);
            hashTable[getId(name)].push_back(idx);
        }
    }
    return N;
}
// 根据课程号升序排列
void sortByIdx() {
    for(int i = 0; i < maxn; i ++) 
        sort(hashTable[i].begin(), hashTable[i].end());
}
// 根据姓名查询
void queryByName(int n) {
    char name[30];
    for(int i = 0; i < n; i ++) {
        scanf("%s", name);
        printf("%s", name);
        int id = getId(name);
        printf(" %d", hashTable[id].size());
        for(auto p : hashTable[id]) printf(" %d", p);
        printf("\n");
    }
}
int main() {
    int N = readData();
    sortByIdx();
    queryByName(N);
    return 0;
}
```

#### C++(STL map)

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-07 13:32:44
 * @LastEditTime: 2019-08-07 14:05:26
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
map<string, vector<int> > res;
// 将数据建立映射:姓名->课程号列表
int readData() {
    int N, K;
    scanf("%d %d", &N, &K);
    int idx, n;
    for(int i = 0; i < K; i ++) {
        scanf("%d %d", &idx, &n);
        char str[40];
        string name;
        for(int i = 0; i < n; i ++) {
            scanf("%s", str); //避免超时
            name = str;
            res[name].push_back(idx);
        }
    }
    return N; //查询个数
}
// 对应的课程列表升序排列
void sortByIdx() {
    for(auto& mp : res) { //auto类型推导
        sort(mp.second.begin(), mp.second.end());
    }
}
// 根据N名字查询各自的课程号
void queryByName(int N) {
    char str[30];
    string name;
    for(int i = 0; i < N; i ++) {
        scanf("%s", str); //用scanf读入，否则会超时
        printf("%s", str);
        name =str;
        if(res.count(name) == 0) printf(" 0");
        else {
            auto vec = res[name];
            printf(" %d", vec.size());
            for(auto p : vec) printf(" %d", p);
        }
        printf("\n");
    }

}
int main() {
    int N = readData();
    sortByIdx();
    queryByName(N);
    return 0;
}
```



### [A1047 Student List for Course](https://pintia.cn/problem-sets/994805342720868352/problems/994805433955368960)

#### 思路

​		和上题思路基本一致，不过这里是根据每个人的选课情况统计出每门课程对应的选课学生。这里由于时间限制1000ms，完全可以用哈希法建立课程编号到学生姓名的映射，其中学生姓名可用string类型直接储存。若是之前时间限制在200ms时，必须用二维char数组替代string类型。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-07 15:20:00
 * @LastEditTime: 2019-08-07 15:29:40
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2510;
vector<string> hashTable[maxn];
int readData() {
    int N, K;
    scanf("%d %d", &N, &K);
    char str[20];
    string name;
    int n, idx;
    for(int i = 0; i < N; i ++) {
        scanf("%s%d", str, &n);
        name = str;
        for(int i = 0; i < n; i ++) {
            scanf("%d", &idx);
            hashTable[idx].push_back(name);
        }
    }
    return K;
}
bool cmp(string a, string b) {
    return a < b;
}
void showResult(int K) {
    for(int i = 1; i <= K; i ++) {
        sort(hashTable[i].begin(), hashTable[i].end());
        int len = hashTable[i].size();
        printf("%d %d\n", i, len);
        for(int j = 0; j < len; j ++) {
            printf("%s\n", hashTable[i][j].c_str());
        }
    }
}
int main() {
    int K = readData();
    showResult(K);
    return 0;
}
```



## set常见用法

### [A1063 Set Similarity](https://pintia.cn/problem-sets/994805342720868352/problems/994805409175420928)

#### 思路

​		步骤 1：设置maxn个集合，在读入数据时将元素放入相应的set中，以达到去除同一个集合中相同的元素。

​		步骤 2：对于每个查询，需要计算出集合a和集合b的交集大小与并集大小的商，可设置Nc记录两个集合相同的总个数，初值为0。枚举集合y中的元素，若其在集合y中出现，令Nc加1，表示找到一个共同元素。枚举完毕后，记Nt为两个集合的并集个数，其值可通过计算公式：Nt =a集合大小+b集合大小-Nc。最后返回商即可。

#### C++

``` c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-07 16:04:30
 * @LastEditTime: 2019-08-07 16:27:36
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 51;
set<int> sets[maxn];
void initSets() {
    int n;
    scanf("%d", &n);
    int m;
    for(int i = 1; i <= n; i ++) {
        scanf("%d", &m);
        int t;
        for(int j = 0; j < m; j ++) {
            scanf("%d", &t);
            sets[i].insert(t);
        }
    }
}
// 计算两个集合的交并集的元素个数即可
double getSimilarity(set<int> a, set<int> b) {
    int Nc = 0, Nt = 0;
    // 交集元素个数
    for(auto p : b) {
        if(a.count(p) != 0) Nc ++;
    }
    Nt = a.size() + b.size() - Nc; //并集元素个数
    return ((double)Nc / Nt) * 100;
}
void query() {
    int n;
    scanf("%d", &n);
    int a, b;
    for(int i = 0; i < n; i ++) {
        scanf("%d %d", &a, &b);
        printf("%.1lf%\n", getSimilarity(sets[a], sets[b]));
    }
}
int main() {
    initSets();
    query();
    return 0;
}
```



## string常见用法

### [A1060 Are They Equal](https://pintia.cn/problem-sets/994805342720868352/problems/994805409175420928)

#### 思路

​		题目要求将两个数改写为N位有效位数的科学计数法的形式，然后判断二者是否相等。而科学计数法的格式一定是$0.d_1d_2...d_N*10^e$（真正输出时指数用`^`与本体分割），因此自需获取本体部分$d_1d_2...d_N$与指数e，即可判断两个数在此情况下是否相等。因此定义结构体类型ScienceNum表示科学计数法，其中frac表示主体部分，exp表示指数。其结构如下：

```c++
struct ScienceNum {
    string frac;
    int exp; //指数
};
```

​		根据指数的正负，可将数据分为两类：

+ $0.a_1a_2...a_n$
+ $b_1b2...b_m.a_1a_2...a_n$

​		在处理前必须先解决前导0的问题，即输入可能存在000.123这种情况，需要将其多余前导0去除变成0.123，也就是上面中的输入的第一类数据格式（注意0需要特殊考虑）。

​		第一种指数肯定小于等于0，因此从第二位后开始枚举，若当前元素为`0`，exp减1，直到遇见非零为止。从当前非0元素开始，写入frac中，直到当前字符串遍历结束或者frac大小达到N为止。上述操作结束后，若frac长度依旧不足N，向后补0，直到长度到达N为止。(注意对`0`,`0.000`等特例的处理)。

​		第二类情况可细分为带小数点的和不带小数点的整数，通过string的find查找小数点的位置，若返回值为-1，表示不存在，表明该数是整数，指数exp即为字符串长度；若其返回值不为-1，exp就是返回的下标值。主体部分从字符串起始位置开始枚举，直到遍历完字符串或frac长度为N为止。以上操作结束后，若frac长度依旧不足N，与第一类处理一样，向后补0，直到长度到达N为止。

#### 注意点

+ 大坑--需要去除前导0，题目确实没说。
+ 需要对0、0.00等特例进行处理。

易错数据：

```
3 0000 0000.00 //YES 0.0000*10^0   测试前导0和特例0处理
```

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-07 20:09:27
 * @LastEditTime: 2019-08-07 21:16:07
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct ScienceNum {
    string frac;
    int exp; //指数
};
ScienceNum getScienceNum(string s, int n) {
    ScienceNum res;
    // 去除多余前导0，并且至少保留1位
    while(s.size() > 1 && s[0] == '0' && s[1] != '.') s.erase(s.begin());
    // xx.xx / xx
    if(s[0] != '0') {
        int pos = s.find('.');
        res.exp = (pos == -1) ? s.size() : pos;
        for(auto p : s) {
            if(p != '.' && res.frac.size() < n) res.frac.push_back(p);
        }
    }
    // 0.xx
    else {
        res.exp = 0;
        int i;
        for(i = 2; i < s.size(); i ++) {
            if(s[i] != '0') break;
            res.exp --;
        }
        if(i == s.size()) res.exp = 0; //0.00特判
        while(i < s.size() && res.frac.size() < n) res.frac.push_back(s[i++]);
    }
    // 不足n为向后补0
    while(res.frac.size() < n) res.frac.push_back('0');
    return res;
}
void print(ScienceNum a, int n) {
    printf("0.");
    cout <<a.frac;
    printf("*10^%d", a.exp);
}
// 比较两个计数法是否相同
bool cmp(ScienceNum a, ScienceNum b) {
    return a.exp == b.exp && a.frac == b.frac;
}
int main() {
    int n;
    scanf("%d", &n);
    string a, b;
    cin >>a >>b;
    ScienceNum sa = getScienceNum(a, n);
    ScienceNum sb = getScienceNum(b, n);
    // 输出
    if(cmp(sa, sb)) {
        printf("YES ");
        print(sa, n);
    }
    else {
        printf("NO ");
        print(sa, n);
        printf(" ");
        print(sb, n);
    }
    printf("\n");
    return 0;
}
```



## map常见用法

### [B1044/A1100 Mars Numbers](https://pintia.cn/problem-sets/994805342720868352/problems/994805367156883456)

#### 思路

​		本题由于数据量较小，所以可直接打表，但也可以对输入直接进行模拟。二者的一个重要核心在于对数3分类处理，以下对13进制分类（10->火星）：

+ 十位为0，个位为[0,12]：直接转为相应字符串，如5。
+ 十位为[1,12]，个位为0：只输出高位字符串，低位无需输出，如。
+ 十位为[1,12]，个位位[1,12]：高位低位均输出。

​		对应火星文先转为13进制再转为10进制，其中仅有一个字符串时需要判断其是否为高位。输出注意格式。

#### 注意

+ 输出格式控制，地球->火星时不要多空格
+ getline读入时最前面使用getchar吸收多余换行

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-07 22:06:03
 * @LastEditTime: 2019-08-07 23:15:31
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
string d[2][13] = {
    {"tret", "jan", "feb", "mar", "apr", "may", "jun", "jly", "aug", "sep", "oct", "nov", "dec"}, //第一位
    {"x", "tam", "hel", "maa", "huh", "tou", "kes", "hei", "elo", "syy", "lok", "mer", "jou"} //第二位
};
map<string, int> mp[2]; 
// 字符串->数字
void initMap() {
    for(int i = 0; i < 2; i ++) {
        for(int j = 0; j < 13; j ++) {
            mp[i][d[i][j]] = j;
        }
    }
    
}
// 地球->火星：10->13->字符串
void EarthToMars(string s) {
    stringstream input(s); 
    int n;
    input >>n; //利用流转换为数值
    if(n >= 13) cout <<d[1][n / 13];
    if(n >= 13 && n % 13 != 0) cout <<" "; //注意空格输出时机
    if(n == 0 || n % 13 != 0) cout <<d[0][n % 13]; //13的整倍数无需输出低位
    cout <<endl;
}
// 火星->地球：字符串->13->10
void MarsToEarth(string s) {
    stringstream input(s);
    string tmp[2], t;
    int sum = 0, cnt = 0;
    // 位数
    while(input >>t) {
        tmp[cnt ++] = t;
    }
    // 2位，正常运算
    if(cnt == 2) {
        sum = mp[1][tmp[0]] * 13 + mp[0][tmp[1]];
    }
    // 1位，需判断是否为高位
    else {
        if(mp[0].count(tmp[0]) == 0) sum = mp[1][tmp[0]] * 13;
        else sum = mp[0][tmp[0]];
    }
    cout <<sum <<endl;
}
int main() {
    initMap(); // 别忘了调用
    int n;
    scanf("%d", &n);
    getchar(); //吸收多余空格
    string s;
    for(int i = 0; i < n; i ++) {
        getline(cin, s);
        if(s[0] >= '0' && s[0] <= '9') EarthToMars(s);
        else MarsToEarth(s);
    }
    return 0;
}
```



### [A1054 The Dominant Color](https://pintia.cn/problem-sets/994805342720868352/problems/994805422639136768)

#### 思路

​		由于题目保证一定存在出现次数大于半数的数字，因此问题等价于找出给定数字矩阵中出现次数最多的数。这里有两种解决思路：

​		（1）由于出现的数范围较大，直接开散列数组会爆栈，于是使用map<int,int>统计每个元素出现次数，统计完毕后找出最大值输出即可。（**常规思路**）

​		（2）若不使用map容器，可利用题目要求目标数必定出现超过半数，也就是有超过半数的数相同，此时若采用两两不同的数相互抵消的策略，最后一定会剩下那个超过半数的数。

​		具体可设置一个整型变量ans存放答案，初值为-1；设另一个int型变量cnt计数ans出现次数，初值为1。接着在读入每个数t时，判断ans与t是否相等。若不等，进一步判断cnt是否为1，若cnt为1，将ans更新为t，表示当前ans必定不是答案；否则令cnt减1，表示抵消。若ans与t相等，令cnt加1，表示ans出现次数增加1。读入所有数后输出ans即可。（**巧妙思路**）

#### C++(map)

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-08 11:37:28
 * @LastEditTime: 2019-08-08 11:44:50
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    map<int, int> mp;
    int t;
    // 统计每个颜色出现次数
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            scanf("%d", &t);
            if(mp.count(t) == 0) mp[t] = 0; //初始化
            mp[t] ++;
        }
    }
    // 找出最大值
    int ans, maxCnt = 0;
    for(auto p : mp) {
        if(p.second > maxCnt) {
            maxCnt = p.second;
            ans = p.first;
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

#### C++(不同数抵消法)

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-08 11:55:39
 * @LastEditTime: 2019-08-08 11:59:19
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    int ans = -1, cnt = 1, t;
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            scanf("%d", &t);
            // 不等，需抵消
            if(ans != t) {
                if(cnt == 1) ans = t; //直接更新ans
                else cnt --;
            }
            else cnt ++; //相等
        }
    }
    printf("%d\n", ans);
    return 0;
}
```



### [A1071 Speech Patterns](https://pintia.cn/problem-sets/994805342720868352/problems/994805398257647616)

#### 思路

​		算法主要分两个步骤：从给定字符串中分割出单词、计数出现次数最多的单词。下面详细解释这两个步骤。

​		步骤  1：由题意可知，单词有大小写字母，数字组成（不妨称为有效字符），且由除有效字符外的字符进行分割，因此不妨枚举字符串中的字符，若该字符为有效字符，则将其加入当前单词word（若该字符是大写字母，则需先将其转换为对应小写字母）。若该字符**不是有效字符**（不可仅用空格判断）或者为**字符串的最后一个字符**，则判断当前单词word是否为空，若word为空，继续遍历下一个字符；若word不为空，则令word的出现次数加1。

​		步骤 2：遍历map中的所有元素，获取出现次数最多的单词，若有多个满足条件的单词，取字典序最小者。

#### 注意点

+ 由于可能出现两个单词间只有非空格字符，如`word1,word2`所以得到单词后只要遇到非有效字符就必须进行处理，而不是用是否遇到空格做判断依据。（以后尽量往坏的情形想想，别被样例误导）
+ 用map统计单词出现次数时，若该单词第一次出现，需要先对其次数初始化为0，然后再加1。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-08 13:06:40
 * @LastEditTime: 2019-08-08 13:44:19
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
// 判断c是否为数字字母表中的一员
bool judge(char c) {
    if(c >= '0' && c <= '9' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') return true;
    else return false;
         
} 
int main() {
    string s;
    getline(cin, s);
    map<string, int> mp;
    string t;
    for(int i = 0; i < s.size(); i ++) {
        char c = s[i];
        if(judge(c)) {
            if(c >= 'A' && c <= 'Z') c = c + ('a' - 'A'); //大写转小写
            t.push_back(c);
        }
        if(!judge(c) || i == s.size() - 1) { //遇到不合法字符||最后一个需处理t
            if(t.empty()) continue; //若t为空，继续循环
            if(mp.count(t) == 0) mp[t] = 0; //初始化
            mp[t] ++;
            t.clear(); //清空
        }
    }
    string ans;
    int maxCnt = -1;
    // map自动有序，找最大值，若有多对也是取字典序小者
    for(auto p : mp) {
        if(maxCnt < p.second) {
            ans = p.first;
            maxCnt = p.second;
        }
    }
    cout <<ans <<" " <<maxCnt <<endl;
    return 0;
}
```



### [A1022 Digital Library](https://pintia.cn/problem-sets/994805342720868352/problems/994805480801550336)

#### 思路

​		建立**书名，作者，关键词，出版社，年份**到**图书编号列表**的映射，再对图书编号列表按字典序升序排列，最后依次根据读入数据查询即可。

​		步骤 1：定义map<string，vector<string> >类型mp[6]，1~5依次存放书名，作者，关键词，出版社，年份到图书编号列表的映射（用set也行，而且其自动有序）。映射建立映射关系中，除了关键词需要进行分割提取外，其他的属性直接建立关系即可。分割提取可先按行读入所有关键词，接着用stringstream分割读入关键词，代码如下：

```c++
string tmp;
stringstream input(s);
while(input >>tmp) {
    mp[j][tmp].push_back(id);
}
```

​		步骤 2：若使用set则可以跳过这步。枚举mp中的元素，对每个元素，遍历其中每一个容器并将其按字典序升序排列。可用自动类型推导auto减少代码量，使用时记得加引用，否则排序结果不会保存。代码如下：

```c++
for(int i = 1; i < 6; i ++) {
    for(auto& p : mp[i]) {
        sort(p.second.begin(), p.second.end());
    }
}
```

​		步骤 3：可以用scanf读入指定格式数据，再查询即可。

#### 注意点

+ 灵活使用vector，string，map（key自动有序），set（自动有序）熟悉各自特性。
+ 灵活使用字符串处理工具，sscanf/printf，scanf/printf，stringstream，使用getline前注意要吸收多余换行
+ 合理使用自动类型推导auto简化代码
+ 传递容器类的参数最好用应用类型，否则容易超时

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-08 14:28:31
 * @LastEditTime: 2019-08-08 14:52:44
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    scanf("%d", &n);
    getchar();
    // 1~5分别存放书名，作者，关键词，出版社，年份 -> 编号
    map<string, vector<string> > mp[6];
    string id, s;
    for(int i = 0; i < n; i ++) {
        getline(cin, id); //编号
        for(int j = 1; j <= 5; j ++) {
            getline(cin, s);
            if(j != 3) {
                mp[j][s].push_back(id);
            }
            else { //key words拆分
                string tmp;
                stringstream input(s);
                while(input >>tmp) {
                    mp[j][tmp].push_back(id);
                }
            }
        }
    }
    // 对每个键值对应的id按字典序升序排列
    for(int i = 1; i < 6; i ++) {
        for(auto& p : mp[i]) {
            sort(p.second.begin(), p.second.end());
        }
    }
    int m, idx;
    scanf("%d", &m);
    string query;
    // 查询
    for(int i = 0; i < m; i ++) {
        scanf("%d: ", &idx);
        getline(cin, query);
        printf("%d: ", idx);
        cout <<query <<endl;
        if(mp[idx].count(query) == 0) {
            printf("Not Found\n");
        }
        else {
            for(auto p : mp[idx][query]) {
                cout <<p <<endl;
            }
        }
    }
    return 0;
}
```



## 总结

### 类型归纳

​		先了解这些容器的特性，再学会如何使用。具体要求如下：

​		掌握最常见的四种容器vector、string、map、set相互间的区别和联系，更加具体应用灵活。

​		（1）相同点

​		增删改查的接口基本都一样。

​		遍历方式均可用自动推导类型auto完成，简化代码

​		（2）不同点

​		线性容器vector和string在初始化后都可以通过下标直接访问，迭代器也支持增加操作，如`vec.begin()+3 `；而树形容器map，set都没以上两种便捷方式，只能通过迭代器顺序遍历。但是树形容器的自动有序是线性容器没有的优势。

### 具体技巧

- 灵活使用vector，string，map（key自动有序），set（自动有序）熟悉各自特性。
- 灵活使用字符串处理工具，sscanf/printf，scanf/printf，stringstream，使用getline前注意要吸收多余换行
- 合理使用自动类型推导auto简化代码
- 传递容器类的参数最好用应用类型，否则容易超时
- 熟练掌握string和char型数组的类型转换，便于使用scanf/printf来输入输出以减少时间消耗
- 复杂题目需要灵活组合多种容器，如**A1022**需要map<stirng, vector<string>>这种包含3个容器的组合，若将vector换为set还可以免去排序步骤

### 小感悟

​		本章总体来说比较容易，一是容器的便利操作，二是从一开始我就试着使用容器，所以现在对其比较熟悉，用起来自然也就得心应手，我觉得作者更应该把STL容器使用放在前面，一开始就学着用或许会好些（可能他想让我们对底层源码更熟悉写叭）。

​		到目前为止，正好做完一百道题，其中有75题一遍AC，15题1~3个样例无法通过，10道题第一次做没思路（其中有一题到现在依旧没通过）。总体来说还比较满意，锻炼了思考和编程的基本功同时学习到了很多技巧，受益匪浅。

​		讲真的学习计算机就是要有好的资料加上动手编程，只看是不会有本质进步的。有些字符串题看起来很麻烦，在脑海里想了半天也没啥思路，然后直接上机编程一步一步的就写了出来，突然想起《黑客与画家》提到编程语言是用来帮助程序猿思考的，在编写中一步步印证修改思路，而不是什么都想好再动手编写代码。此时深深认同他的观点，只有简单的程序才可能把什么都想清楚，对于复杂的问题，只要有一个模糊大致的思路即可上机验证。然后根据输入输出来修正思路，也就是调试。

​		学习过程学习到了许多的技巧，看完后立马手动实现一遍，发现自己原来理解似乎并不那么正确。所以，编程时最好的检验学习效果的工具，若是你对某个问题似懂非懂，把它写成程序，保证清晰无比。

​		果然，世上最怕认真的人，一旦坚持做某件事，结果真滴令人吃惊，开心一下，准备进入重点，图论。

​		
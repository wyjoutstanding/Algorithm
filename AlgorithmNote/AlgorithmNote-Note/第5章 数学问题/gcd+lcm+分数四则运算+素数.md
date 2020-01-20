# 《算法笔记上机训练实战指南》习题报告

### 作者：wuyangjun

### 时间：2019/8/5~8/6

### 主题：gcd+lcm+分数四则运算+素数+质因子分解+大整数运算

---

## 最大公约数与最小公倍数

### [B1008 数组元素循环右移问题](https://pintia.cn/problem-sets/994805260223102976/problems/994805316250615808)

这题有多种解法，这里提三种常见解法：

+ 单纯为了解题，可直接打印输出或者多开辟数组。
+ 按照题目要求，模拟每一位的循环移位。
+ 根据移动的位数来划分原序列，将整个序列看成整体，三次反转即可**（最简单）**

解法一就不细说了，主要详细解释解法二和解法三。

#### 解法二

​		步骤 1：输入的m和n存在三种关系，考虑到m可能大于n，所以m %= n，即对m进行预处理，落入0~n中。若m=0，表示移动m位后每个数依旧在原来的位置，可直接输出；否则，进入步骤2。

​		步骤 2：根据n与m，n-m是否为整除关系分两类情况讨论：

+ `n % m != 0 && n % (n-m) != 0`：从任意一个元素开始，间隔为m的一个轮换即可完成模拟。
+ `n % m == 0 || n % (n-m) == 0`：任意选取m/n-m个连续的元素，对于其中每一个元素，将其作为开始并完成一次轮换（即m/n-m组间隔为m的轮换）。

这两种情况仅仅是轮换的组数不同，因此，引入最大公约数d=gcd(n,m)来统一二者的轮换组数，如n=12,m=4，需要做4组间距为4的轮换；再如n=12，m=8，需要做4组间距为8的轮换。

​		步骤 3：实现轮换，假设起始元素为a[i]，j表示当前要移动的元素下标，初值为i；cur表示当前要移动的元素；next表示下个要被移动的元素，初值为a[i]。使用do...while结构，令cur=next，确定当前元素，再计算出下一个要移动的元素下标j = (j+m)%n，取出其值next=a[j]，将当前值移动到合理位置a[j]=cur。反复执行直至j==i。

#### 代码2

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-05 10:39:13
 * @LastEditTime: 2019-08-05 11:01:17
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int a[101];
// 打印
void print(int n) {
    for(int i = 0; i < n; i++) {
        if(i == 0) printf("%d", a[i]);
        else printf(" %d", a[i]);
    }
    printf("\n");
}
// 最大公约数
int gcd(int a, int b) {
    if(b == 0) return a;
    else return gcd(b, a % b);
}
// 模拟循环右移
void solve(int n, int m) {
    int d = gcd(n, m);
    // 轮换的组数d
    for(int i = 0; i < d; i++) {
        int j = i;
        // 以a[j]为起点，m为间隔的轮换
        int cur, next = a[j], to;
        do {
            cur = next;
            j = (j + m) % n;
            next = a[j];
            a[j] = cur;
        }while(j != i);
    }
}
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    m %= n; //m >= n的情况
    // m == 0直接输出即可
    if(m != 0) solve(n, m);
    print(n);
    return 0;
}
```

#### 解法三

​		这个解法是最巧妙的，理解后也是最简单的。假设有数组A：$a_1a_2...a_{n-m}a_{n-m+1}...a_n,(n\geq m)$，现在该数组循环右移m位后得到结果数组A‘：$a_{n-m+1}...a_na_1a_2...a_{n-m}$，若令X表示$a_1a_2...a_{n-m}$，令Y表示$a_{n-m+1}...a_n$，那么只需要先分别反转X和Y，再对整体数组进行反转即可令A变成A'，即$(X^TY^T)^T = YX$。举个例子，假设数组A：{1,2,3,4,5}，n=5，m=2，所以X={1,2,3}，Y={4,5}。转换过程如下：

1. X的反转$X^T$为{3,2,1}，Y的反转$Y^T$为{5,4}。此时A变成{3,2,1,5,4}
2. 整体反转A得A'：{4,5,1,2,3}。

​		该思想是将序列划分为两个部分，当做整体来对待，所以解法简洁，不必陷入细节；而解法二是逐个击破，分别处理每一个元素，所以是实打实的模拟，需要处理的细节较多。通过两者比较可以看出，宏观角度上看待问题难度对于自身抽象能力要求较高，但是只要常常练习，就可以跳出惯性思维，找到这种简单巧妙的解法。

#### 代码3

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-05 11:29:29
 * @LastEditTime: 2019-08-05 11:37:08
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
void print(int *a, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d%s", a[i], i + 1 - n ? " " : "\n");
    }
}
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n];
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    m %= n; // m > n
    // 3次反转
    reverse(a, a + (n - m));
    reverse(a + (n - m), a + n);
    reverse(a, a + n);
    print(a, n);
    return 0;
}
```



## 分数四则运算

### [A1081 Rational Sum](https://pintia.cn/problem-sets/994805342720868352/problems/994805386161274880)

#### 思路

​		主要分四步走，先定义好结构体表示分数，其次规定分数的最简形式，即化简原则，接着定义分数加法，最后根据题意以不同形式输出分数。具体步骤如下：

​		**步骤 1**：**分数表示**，以结构体类型Fraction表示分数，其中up表示分子，down表示分母，为防止溢出，用long long类型存储，代码如下：

```c++
typedef long long LL;
struct Fraction {
    LL up;
    LL down;
}sum, t;
```

同时对标准分数做以下三个约定：

+ 分母必定为正整数；若其为负，那么令分子为负，分母为正即可。
+ 若分数为0，约定分子为0，分母为1。
+ 分子分母最大公约数为1（化到最简的假分数/真分数）。

​		**步骤 2**：**分数化简**就是为了令分数满足以上三条规则，因此化简也有相对应的三个步骤：

+ 若分母为负，将分子分母均取为相反数。
+ 若分子为0，令分母为1。
+ 若分子不为0，进行约分：求出分子绝对值和分母的最大公约数d，然后令分子分母同除以d。

​	代码如下：

```c++
Fraction reduction(Fraction res) {
    // 保证分母为正
    if(res.down < 0) {
        res.up = -res.up;
        res.down = -res.down;
    }
    // 0：分子为0，分母为1
    if(res.up == 0) res.down = 1;
    else {//化为最简
        int d = gcd(abs(res.up), res.down); //最大公约数,分子必须用绝对值
        res.up /= d;
        res.down /= d;
    }
    return res;
}
```

​		**步骤 3**：**分数加法**，对于两个分数f1和f2，其加法公式如下：
$$
result=\frac{f1.up*f2.down+f2.up*f1.down}{f1.down*f2.down}
$$
​		其代码如下：

```c++
Fraction add(Fraction a, Fraction b) {
    Fraction t;
    t.up = a.up * b.down + b.up * a.down;
    t.down = a.down * b.down;
    return reduction(t); //返回最简结果
}
```

​		**步骤 4**：**分数输出**，按照题意，可分为以下4个步骤：

+ 输出前，先化为最简分数。

+ 若分数f的分母为1，说明该分数为整数，直接输出分子，省略分母。

+ 若分数f的**分子up绝对值**大于分母down，说明该分数是假分数，此时应该以带分数形式输出，即整数部分为`f.up/f.down`，分子部分为`abs(f.up) % f.down`（分子可能为负），分母部分为`f.down`。

+ 以上均不满足时说明分数f是真分数，按原样输出即可。

​		代码如下：

``` c++
void showResult(Fraction res) {
    Fraction r = reduction(res); //化简
    if(r.down == 1) printf("%d\n", r.up); //整数
    else if(abs(r.up) > r.down) printf("%d %d/%d\n", r.up / r.down, abs(r.up) % r.down, r.down); //假分数
    else printf("%d/%d\n", r.up, r.down); //真分数
}
```

#### 注意点

+ 数据类型若用int可能会溢出，所以采用**long long**。
+ **分数化简**中一定要取**分子绝对值**和分母的最大公约数，分子可能为负，而分母已经保证为正。
+ **分数加法**返回前**必须先化简**，若是将所有分数相加后再化简，在执行加法过程中可能就溢出了。
+ **分数输出**时必须判断用分子绝对值与分母比较，若是带分数，整数和分母部分无需特殊处理，分子部分必须用分子绝对值对分母求余。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-05 13:28:19
 * @LastEditTime: 2019-08-05 13:58:33
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
struct Fraction {
    LL up;
    LL down;
}sum, t;
// 最大公约数
int gcd(LL a, LL b) {
    if(b == 0) return a;
    else return gcd(b, a % b);
}
// 化简
Fraction reduction(Fraction res) {
    // 保证分母为正
    if(res.down < 0) {
        res.up = -res.up;
        res.down = -res.down;
    }
    // 0：分子为0，分母为1
    if(res.up == 0) res.down = 1;
    else {//化为最简
        int d = gcd(abs(res.up), res.down); //最大公约数,分子必须用绝对值
        res.up /= d;
        res.down /= d;
    }
    return res;
}
// 模拟分数加法
Fraction add(Fraction a, Fraction b) {
    Fraction t;
    t.up = a.up * b.down + b.up * a.down;
    t.down = a.down * b.down;
    return reduction(t); //返回最简结果
}
// 展示结果
void showResult(Fraction res) {
    Fraction r = reduction(res); //化简
    if(r.down == 1) printf("%d\n", r.up); //整数
    else if(abs(r.up) > r.down) printf("%d %d/%d\n", r.up / r.down, abs(r.up) % r.down, r.down); //假分数
    else printf("%d/%d\n", r.up, r.down); //真分数
}
int main() {
    int n;
    scanf("%d", &n);
    sum.up = 0;
    sum.down = 1;
    for(int i = 0; i < n; i++) {
        scanf("%lld/%lld", &t.up, &t.down);
        sum = add(sum, t);
        // printf("%lld/%lld\n", t.up, t.down);
    }
    showResult(sum);
    return 0;
}
```



### [A1088 Rational Arithmetic](https://pintia.cn/problem-sets/994805342720868352/problems/994805378443755520)

#### 思路

​		这是常规的分数四则运算题，基本框架与上一题一样，只是多了三种运算并且除法输出时需要特别判断。

​		作除法时，若除数为0，令返回结果res.down为0，这样当输出时遇到down为0直接输出`Inf`，同时令res.up为1，避免由于up为0导致down被化简为1。

​		此题可定义操作函数指针数组、操作符数组以及封装输出打印函数来简化代码。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-05 14:50:33
 * @LastEditTime: 2019-08-05 15:43:18
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// const ll inf = ((1ll) << 62) -2;
struct Fraction {
    ll up, down;
}a, b, res; 
ll gcd(ll a, ll b) {
    return (b == 0) ? a : gcd(b, a % b);
}
Fraction reduction(Fraction res) {
    if(res.down < 0) {
        res.up = -res.up;
        res.down = -res.down;
    }
    if(res.up == 0) res.down = 1;
    else {
        ll d = gcd(abs(res.up), res.down);
        res.up /= d;
        res.down /= d;
    }
    return res;
}
Fraction add(Fraction a, Fraction b) {
    Fraction res;
    res.up = a.up * b.down + b.up * a.down;
    res.down = a.down * b.down;
    return reduction(res);
}
Fraction sub(Fraction a, Fraction b) {
    Fraction res;
    res.up = a.up * b.down - b.up * a.down;
    res.down = a.down * b.down;
    return reduction(res);
}
Fraction mul(Fraction a, Fraction b) {
    Fraction res;
    res.up = a.up * b.up;
    res.down = a.down * b.down;
    return reduction(res);
}
Fraction div(Fraction a, Fraction b) {
    Fraction res;
    if(b.up == 0) { //除数为0，令分母为0，分子为1
        res.down = 0;
        res.up = 1; //仅仅为了分母不被化简为1
        return res;
    }
    else {
        res.up = a.up * b.down;
        res.down = a.down * b.up;
        return reduction(res);
    }
}
void showResult(Fraction res) {
    Fraction r = reduction(res);
    // 除法特例
    if(r.down == 0) printf("Inf"); 
    else {
        // 负数带括号
        if(r.up < 0) printf("(");
        // 整数
        if(r.down == 1) printf("%lld", r.up);
        // 假分数
        else if(abs(r.up) > r.down) printf("%lld %lld/%lld", r.up / r.down, abs(r.up) % r.down, r.down);
        // 真分数
        else printf("%lld/%lld", r.up, r.down);
        if(r.up < 0) printf(")");
    }
}
void print(Fraction a, Fraction b, Fraction res, char op) {
    showResult(a);
    printf(" %c ", op);
    showResult(b);
    printf(" = ");
    showResult(res);
    printf("\n");
} 
int main() {
    scanf("%lld/%lld", &a.up, &a.down);
    scanf("%lld/%lld", &b.up, &b.down);
    char op[4] = {'+', '-', '*', '/'};
    Fraction (*opFunc[4]) (Fraction a, Fraction b) = {add, sub, mul, div};
    for(int i = 0; i < 4; i++) {
        print(a, b, (*opFunc[i]) (a, b), op[i]);
    }
    return 0;
}
```



## 素数

### [B1007 素数对猜想](https://pintia.cn/problem-sets/994805260223102976/problems/994805317546655744)

#### 思路

​		枚举出[2,n]的所有素数，遍历一次统计出间距为2的素数对的总对数。思路简单，但是关键在于时间复杂度，若使用普通的枚举方式，时间复杂度最低达到$O(n\sqrt n)$，然而n最大可取$10^5$，一般来说会超时。所以这里采用**筛法**，其时间复杂度为$O(nloglogn)$，完全满足要求。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-05 16:34:16
 * @LastEditTime: 2019-08-05 17:05:54
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
int prime[maxn], pNum = 0; //素数表和素数个数
bool p[maxn] = {0};
// Eratosthenes筛法：O(nloglogn)，找出[2,n]的素数
void findPrime(int n) {
    for(int i = 2; i <= n; i++) {
        if(!p[i]) {
            prime[pNum++] = i;
            for(int j = i + i; j <= n; j += i) p[j] = true;
        }
    }
}
// 统计间距为2且不大于n的素数对数
int solve(int n) {
    int cnt = 0;
    for(int i = 0; i < pNum - 1; i++) {
        if(prime[i+1] - prime[i] == 2) cnt ++;
    }
    return cnt;
}
int main() {
    int n;
    scanf("%d", &n);
    findPrime(n);
    printf("%d\n", solve(n));
    return 0;
}
```



### [B1013 数素数](https://pintia.cn/problem-sets/994805260223102976/problems/994805309963354112)

#### 思路

​		此题是上题的简化版，直接枚举出第[0,n]个素数，然后按要求输出第[m,n]个即可，由于此题没有时间复杂度限制，所以使用普通暴力解法或筛法都是可行的。

​		（1）若使用筛法，需要将枚举的上界尽量调高，因为不知道到哪才有足够的素数个数。

​		（2）若使用暴力解法，直接枚举第[0,n]个，无需考虑上界问题，处理起来较简单。

​		若是边找素数边输出会使得代码凌乱复杂，不妨将符合条件的素数先存起来，最后再按要求输出。

#### C++

``` c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-05 17:13:53
 * @LastEditTime: 2019-08-05 17:52:39
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int prime[maxn], num = 0; //第m~n个素数
// 判断是否为素数，是->true；否->false
bool isPrime(int n) {
    if(n < 2) return false; //小于2不可能是素数
    int sqr = (int)sqrt(1.0 * n); //要乘1.0变成浮点数
    for(int i = 2; i <= sqr; i++) {
        if(n % i == 0) return false;
    }
    return true;
}
// 寻找第[m,n]个素数
void findPrime(int m, int n) {
    int pNum = 0, i = 2;
    do {
        if(isPrime(i)) {
            pNum ++;
            if(pNum >= m && pNum <= n) prime[num++] = i;
        }
        i ++;
    }while(pNum != n);
}
void print() {
    for(int i = 0; i < num; i++) {
        printf("%d%s", prime[i], (i % 10 == 9 || i == num - 1) ? "\n" : " ");
    }
}
int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    findPrime(m, n);
    print();
    return 0;
}
```



### [A1015 Reversible Primes](https://pintia.cn/problem-sets/994805342720868352/problems/994805495863296000)

#### 思路

​		本题关键在于solve函数的编写，以下是其具体步骤：

​		步骤 1：判断N是否为素数，若不是，直接返回false；否则，进入步骤 2。

​		步骤 2：正常思路是将10进制下的$(n)_{10}$转换为d进制下的$(n_1)_d$，再将其逆置为$(n_1^{T}）_d$，最后转换为$(n_2)_{10}$来判断其是否为素数。这里简化了代码，直接将10进制的n转换为d进制的同时计算n在d进制下的逆置的10进制值（除基取余法倒序的特性正好满足逆置条件，于是直接计算$(n)_d$的10进制值）。

#### 注意

+ 判断素数的循环条件一定要加等号，否则样例`4 10`就会误判。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-05 19:22:24
 * @LastEditTime: 2019-08-05 19:42:14
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
bool isPrime(int n) {
    if(n < 2) return false;
    for(int i = 2; i <= (int)sqrt(1.0 * n); i++) { //等于号别漏，否则4,10就过不了
        if(n % i == 0) return false;
    }
    return true;
}
bool solve(int n, int d) {
    if(!isPrime(n)) return false; //n不是素数直接返回false
    // 将10进制的n转为d进制再转为10进制，这里利用其倒序性质同步进行
    int sum = 0;
    do {
        sum = sum * d + n % d;
        n /= d;
    }while(n != 0);
    return isPrime(sum);
}
int main() {
    int n, d;
    while(true) {
        scanf("%d", &n);
        if(n < 0) break;
        scanf("%d", &d);
        printf("%s\n", solve(n, d) ? "Yes" : "No");
    }
    return 0;
}
```



### [A1078 Hashing](https://pintia.cn/problem-sets/994805342720868352/problems/994805389634158592)

#### 思路

​		步骤 1：首先，对于一个输入的MSize，若其不是素数，则必须找到第一个比他大的素数。

​		判断一个整数是否为素数的方法：如果n不能被$[2,\sqrt n]$中任意一个整数整除，那么n是素数。

​		步骤 2：开辟一个bool型数组pos[]，pos[i]=false表示第i位未被使用。对于每个插入的元素a，计算H(a)并判断对应位置是否被使用。

+ 若未被使用，插入对应位置（令pos[H(a)]=true实现），并输出。
+ 若已被使用，根据正向平方探测法，令步长i初值2为1，然后令下个检测下标为`((a % MSize) + i * i) % MSize`，判断该位置是否已被占用：若未被占用，返该下标；若已被占用，则令i++，继续进行判断。若i自增到MSize时还未找到插入位置，说明这个元素无法插入，详细见下面证明。

#### 证明

​		**证明命题**：证明如果i从[0,MSize)进行枚举依旧无法找到插入位置，那么对于i>=MSize也无法找到插入位置。

​		这里只需要证明当i取[MSize,2MSize-1]也无法找到位置即可：

​		$设0\leq x <MSize,那么$
$$
\begin{aligned}

&(H(a)+(MSize+x)*(MSize+x))\%MSize\\
&=(H(a)+MSize^2+2*MSize*x+x^2)\%MSize\\
&=(H(a)+x^2)\%MSize
\end{aligned}
$$
​		所以循环节为MSize，证明完毕。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-05 20:18:45
 * @LastEditTime: 2019-08-05 20:53:52
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
bool pos[maxn] = {0}; //标记位置是否被使用
bool isPrime(int n) {
    if(n < 2) return false;
    // 等于号别漏！！！！
    for(int i = 2; i <= (int)sqrt(1.0 * n); i++) {
        if(n % i == 0) return false; 
    }
    return true;
}
//找到第一个大于等于m的素数
int initMSize(int m) {
    while(true) {
        if(isPrime(m)) return m;
        else m ++;
    }
}
// 正向平方探查
int quadraticProbing(int n, int MSize) {
    int idx;
    for(int i = 1; i < MSize; i++) {
        idx = ((n % MSize) + i * i) % MSize;
        if(!pos[idx]) {
            pos[idx] = true;
            return idx;
        }
    }
    return -1; //未找到位置
}
// 哈希映射
int hashing(int n, int MSize) {
    int idx = n % MSize;
    if(!pos[idx]) {
        pos[idx] = true;
        return idx;
    }
    return quadraticProbing(n, MSize); //冲突
}
int main() {
    int MSize, N;
    scanf("%d %d", &MSize, &N);
    MSize = initMSize(MSize);
    int t;
    for(int i = 0; i < N; i ++) {
        scanf("%d", &t);
        int ret = hashing(t, MSize);
        if(ret == -1) printf("-%s", i + 1 == N ? "\n" : " ");
        else printf("%d%s", ret, i + 1 == N ? "\n" : " ");
    }
    return 0;
}
```



## 质因子分解

### [A1059 Prime Factors](https://pintia.cn/problem-sets/994805342720868352/problems/994805415005503488)

#### 思路

​		步骤 1：根据输入的n，利用筛法找到$[2,\sqrt n]$内的所有素数（为啥是根号n见**步骤3强化结论**解释）。

​		步骤 2：定义结构体类型Factor，其中x表示素数因子，cnt表示该因子个数。由于题目约定数据再int型范围内，Factor类型的数组fac开到10足够存放所有因子。

​		步骤 3：根据之前提到的素数判定方法：对于一个正整数n来说，如果它存在1和本身之外的因子，那么一定是在sqrt(n)的左右成对出现。若把这个结论用在质因子上，会得到一个**强化结论**：对一个正整数n来说，如若它存在[2,n]范围内的质因子，要么这些质因子全部小于等于sqrt(n)；要么仅存在一个大于sqrt(n)的质因子，而其余质因子全部小于等于sqrt(n)。根据强化结论可以得到以下与素数判定类似的求解思路：

​		（1）令fNum表示不同质因子个数，初值为0。枚举1~sqrt(n)范围内的所有质因子p，判断p是否为n的因子。

+ 若p是n的因子，初始化fac[fNum].x为p，个数fac[fNum].cnt为0。然后只要p还是n的因子，令fac[fNum].cnt加1，同时令n除以p，直至p不是n的因子为止。
+ 若p不是n的因子，直接跳过，判断下一个因子。

​		（2）如以上步骤结束后n大于1，说明n有且仅有一个大于sqrt(n)的质因子（可能是n自身），这时需要将这个质因子加入fac数组，个数置1。

​		步骤 4：按照题目要求输出，注意对1的特判。

#### 注意

+ n为1时直接输出`1=1`，注意输出格式的要求
+ 由于n在int范围，根号n不超过$10^5$，因此素数表开到该量级即可。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-06 12:54:42
 * @LastEditTime: 2019-08-06 13:32:21
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
int prime[maxn], pNum = 0;
bool p[maxn] = {0};
// 筛法查找[2,n]的素数表
void findPrime(int n) {
    for(int i = 2; i <= n; i++) {
        if(!p[i]) {
            prime[pNum++] = i;
            for(int j = i + i; j <= n; j += i) {
                p[j] = true;
            }
        }
    }
}
struct Factor {
    int x, cnt; //因子，次数
}fac[10]; //int足够
int fNum = 0; //不同因子个数
void primeFactor(int n) {
    int sqrn = (int)sqrt(1.0 * n);
    findPrime(sqrn);
    // 先在[2,sqrt(n)]找
    for(int i = 0; i < pNum; i++) {
        if(n % prime[i] == 0) {
            // 初始化
            fac[fNum].x = prime[i];
            fac[fNum].cnt = 0;
            // 计数
            while(n % prime[i] == 0) {
                fac[fNum].cnt ++;
                n /= prime[i];
            }
            fNum ++;
        }
        if(n == 1) break;
    }
    // 若不为1，必定存在一个因子位于(sqrt(n), n]
    if(n != 1) {
        fac[fNum].x = n;
        fac[fNum].cnt = 1;
        fNum ++;
    }
}
void print(int n) {
    printf("%d=", n);
    for(int i = 0; i < fNum; i++) {
        if(i != 0) printf("*");
        printf("%d", fac[i].x);
        if(fac[i].cnt != 1) printf("^%d", fac[i].cnt);
    }
    printf("\n");
}
int main() {
    int n;
    scanf("%d", &n);
    if(n == 1) printf("1=1\n"); //注意特判
    else {
        primeFactor(n);
        print(n);
    }
    return 0;
}
```



### [A1096 Consecutive Factors](https://pintia.cn/problem-sets/994805342720868352/problems/994805370650738688)

#### 思路

​		受到质因数的分布启发，得到新结论：对于正整数n，其最大连乘因子要么都小于等于sqrt(n)；要么仅一个大于sqrt(n)，其余均小于sqrt(n)。由此可得到以下解法：

​		步骤 1：令ansIdx表示最长且最小的连续整数的第一个元素，ansLen表示最长连续整数的长度，初值为0。枚举[2,sqrt(n)]的每个整数i，从i开始，找到第一个整数j，使得i到j的连续乘积之和无法被n整除，接着判断j-i与ansLen的关系，若大于，则更新ansIdx为i，ansLen为j-i（不取等可取出多组等长中起始最小的那组）。

​		步骤 2：步骤  1无法处理质数，也就是ansLen=0时，需要直接输出n。其余情况按照题目要求输出。

#### 注意

+ N最大可接近int型上界，若是直接对[1,n]暴力枚举可能超时，所以一定要用[1,sqrt(n)]枚举的技巧。同时，在计算乘积过程中可能溢出，所以使用longlong类型。
+ 注意质数的特殊判断。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-06 15:25:49
 * @LastEditTime: 2019-08-06 15:52:41
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
void solve(LL n) {
    LL sqrn = (LL)sqrt(1.0*n);
    LL ansIdx, ansLen = 0;
    for(LL i = 2; i <= sqrn; i++) {
        LL product = i, j = i;
        // 此处不可限制j <= sqrn，否则6就过不了
        while(n % product == 0) {
            j ++;
            product *= j;
        }
        // 若使用等于，无法从多对中筛选出最小的
        if(j - i > ansLen) {
            ansIdx = i;
            ansLen = j - i;
        }
    }
    if(ansLen == 0) printf("1\n%d\n", n);
    else {
        printf("%d\n", ansLen);
        for(int i = ansIdx; i < ansIdx + ansLen; i++) {
            printf("%d%s", i, i == ansIdx + ansLen - 1? "\n" : "*");
        }
    }
} 
int main() {
    LL n;
    scanf("%lld", &n);
    solve(n);
    return 0;
}
```



## 大整数运算

### [B1017 A除以B](https://pintia.cn/problem-sets/994805260223102976/problems/994805305181847552)

#### 思路

​		该题为高精度整数和低精度整数的除法操作，直接使用模板。主要考察对高精度整数的存储，除法运算。

​		步骤 1：**存储表示**，定义结构体类型bign表示大整数，其中数组d[1000]的0~999号位依次存储大整数的低到高位(之所以这样存储是因为四则运算中加减乘都是从低位开始计算的，只有除法从高位开始计算，遵循少数服从多数原则)，len表示整数的位数。同时为了编码的便利性，添加无参构造函数，初始化len和数组每个元素为0。其代码如下：

```c++
struct bign {
    int d[1000]; //低到高位依次存放
    int len; //位数
    // 无参构造函数
    bign() {
        memset(d, 0, sizeof(d)); //按位赋值
        len = 0;
    }
};
```

​		步骤 2：由于大整数逆向存储，而使用scanf读入字符串时，与其顺序相反，因此必须将读入的字符串反转。

```c++
bign change(char *str) {
   bign res;
   res.len = strlen(str);
   for(int i = 0; i < res.len; i ++) {
       res.d[i] = str[res.len - 1 - i] - '0'; //转换为整数
   }
   return res;
}
```

​		步骤 3：**模拟除法**，令余数为r，初值为0。从高位到低位枚举每一位，余数乘以10加上当前位的值，得到当前运算的临时被除数，将其与除数相比：若被除数小于除数，则该位的商为0；否则，该位的商为对应的商，余数更新为对应的余数。以上步骤完成后，最高位可能有多余0，此时需去除它们，但至少要保证结果有1位数。

```c++
bign div(bign a, int b, int &r) {
    bign res;
    res.len = a.len; //商与被除数位数相同
    // 从高位开始枚举
    for(int i = a.len - 1; i >= 0; i --) {
        r = r * 10 + a.d[i];
        if(r < b) res.d[i] = 0;
        else {
            res.d[i] = r / b;
            r = r % b;
        }
    }
    // 去除高位多余0，为0时需保留一位
    while(res.len > 1 && res.d[res.len - 1] == 0) res.len --;
    return res;
}
```



#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-06 20:26:20
 * @LastEditTime: 2019-08-06 21:01:25
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct bign {
    int d[1000]; //低到高位依次存放
    int len; //位数
    // 无参构造函数
    bign() {
        memset(d, 0, sizeof(d)); //按位赋值
        len = 0;
    }
};
// 将读入的字符串反转，小端存储
bign change(char *str) {
   bign res;
   res.len = strlen(str);
   for(int i = 0; i < res.len; i ++) {
       res.d[i] = str[res.len - 1 - i] - '0'; //转换为整数
   }
   return res;
}
// 高精度和低精度除法，r为余数，初值必须为0
bign div(bign a, int b, int &r) {
    bign res;
    res.len = a.len; //商与被除数位数相同
    // 从高位开始枚举
    for(int i = a.len - 1; i >= 0; i --) {
        r = r * 10 + a.d[i];
        if(r < b) res.d[i] = 0;
        else {
            res.d[i] = r / b;
            r = r % b;
        }
    }
    // 去除高位多余0，为0时需保留一位
    while(res.len > 1 && res.d[res.len - 1] == 0) res.len --;
    return res;
}
void printBign(bign a) {
    for(int i = a.len - 1; i >= 0; i --) printf("%d", a.d[i]);
    // printf("\n");
}
int main() {
    char str[1000];
    int b;
    scanf("%s %d", str, &b);
    bign a = change(str);
    int r = 0; // 余数初始值必须为0
    bign res = div(a, b, r);
    printBign(res);
    printf(" %d\n", r);
    return 0;
}
```



### [A1023 Have Fun with Numbers](https://pintia.cn/problem-sets/994805342720868352/problems/994805478658260992)

#### 思路

​		本题可用**高精度整数加法**或者**高精度整数和低精度整数乘法**实现，再判断新整数的数位是否为原整数的数位的一个排列即可。本题采用高精度整数加法实现。

​		**步骤 1**：高精度加法模板与上题基本一致，结构体与逆置函数一模一样，仅仅更换运算，加法操作思路：令carry表示进位，初值为0。从0开始枚举数位，将该位上的两个数字与进位相加，得到的结果取个位为该位结果，取十位数作为新的进位。结束后若进位不为0，需继续向前进位。模板代码如下：

```c++
bign add(bign a, bign b) {
    bign res;
    int carry = 0; //进位
    // 低位到高位，取较长者，较短者高位已经初始化为0
    for(int i = 0; i < a.len || i < b.len; i ++) {
        int tmp = a.d[i] + b.d[i] + carry;
        res.d[res.len++] = tmp % 10;
        carry = tmp / 10;
    }
    // 最高位的进位
    if(carry != 0) res.d[res.len++] = carry;
    return res;
}
```

​		**步骤 2**：判断新整数的数位是否为原整数的数位的一个排序，也就是说判断下二者的数字频率表是否完全一样，这启发我们可以用哈希思想。

​		首先，若两个整数长度不同肯定不满足命题，直接返回false。否则，开辟一个hashTable[10]存放0~9中每个数字出现的次数，然后枚举原整数所有数位，令对应位置的值加1；接着枚举新整数所有数位，令对应位置的值减1。最后，遍历hashTable，若所有位置的值均为0，说明满足命题，返回true；否则返回false。

#### 注意

+ change函数中将字符串反转时记得减去`'0'`，变成整型。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-06 21:32:32
 * @LastEditTime: 2019-08-06 21:50:22
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct bign {
    int d[100];
    int len;
    bign() {
        memset(d, 0, sizeof(d));
        len = 0;
    }
};
bign change(char *str) {
    bign res;
    res.len = strlen(str);
    for(int i = res.len - 1; i >= 0; i --) {
        res.d[i] = str[res.len - 1 - i] - '0';
    }
    return res;
}
bign add(bign a, bign b) {
    bign res;
    int carry = 0; //进位
    // 低位到高位，取较长者，较短者高位已经初始化为0
    for(int i = 0; i < a.len || i < b.len; i ++) {
        int tmp = a.d[i] + b.d[i] + carry;
        res.d[res.len++] = tmp % 10;
        carry = tmp / 10;
    }
    // 最高位的进位
    if(carry != 0) res.d[res.len++] = carry;
    return res;
}
// 哈希表判断两个序列是互为否为排列
bool isFind(bign a, bign b) {
    if(a.len != b.len) return false;
    int hashTable[10] = {0};
    for(int i = 0; i < a.len; i ++) {
        hashTable[a.d[i]] ++;
    }
    for(int i = 0; i < b.len; i ++) {
        hashTable[b.d[i]] --;
    }
    for(int i = 0; i < 10; i ++) {
        if(hashTable[i] != 0) return false;
    }
    return true;
}
void print(bign a) {
    for(int i = a.len - 1; i >= 0; i --) printf("%d", a.d[i]);
    printf("\n");
}
int main() {
    char str[21];
    scanf("%s", str);
    bign a = change(str);
    bign res = add(a, a);
    printf("%s\n", isFind(a, res) ? "Yes" : "No");
    print(res);
    return 0;
}
```



### [1024 Palindromic Number](https://pintia.cn/problem-sets/994805342720868352/problems/994805476473028608)

#### 思路

​		由于最大可取$10^{10}$的N操作100次后，位数肯定超过longlong的表示范围了，因此必须使用大整数加法。此题与之前两题一样，套用加法模板，只是需要增加回文数判断：只需要遍历下标0~len/2，判断其是否与其对称位置的数位相同，只要存在一个不相同，则其不是回文串。代码如下：

```c++
bool isPalindromicNum(bign a) {
    for(int i = 0; i < a.len / 2; i ++) {
        if(a.d[i] != a.d[a.len - 1 - i]) return false;
    }
    return true;
}
```

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-06 23:45:58
 * @LastEditTime: 2019-08-07 00:16:44
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct bign {
    int d[1000];
    int len;
    bign() {
        memset(d, 0, sizeof(d));
        len = 0;
    }
};
bign change(char *str) {
    bign res;
    res.len = strlen(str);
    for(int i = 0; i < res.len; i ++) {
        res.d[i] = str[res.len - 1 - i] - '0'; //记得减0
    }
    return res;
}
bign add(bign a, bign b) {
    bign res;
    int carry = 0;
    for(int i = 0; i < a.len || i < b.len; i ++) {
        int tmp = a.d[i] + b.d[i] + carry;
        res.d[res.len++] = tmp % 10;
        carry = tmp / 10;
    }
    if(carry != 0) res.d[res.len++] = carry;
    return res;
}
// a反转
bign reverse(bign a) {
    bign b;
    b.len = a.len;
    for(int i = 0; i < a.len; i ++) {
        b.d[i] = a.d[a.len - 1 - i];
    }
    return b;
}
// 判断大整数a是否为回文数
bool isPalindromicNum(bign a) {
    for(int i = 0; i < a.len / 2; i ++) {
        if(a.d[i] != a.d[a.len - 1 - i]) return false;
    }
    return true;
}
void print(bign a) {
    for(int i = a.len - 1; i >= 0; i --) printf("%d", a.d[i]);
    printf("\n");
}
void solve(bign a, int k) {
    bign res = a;
    int cnt = 0;
    while(cnt < k && !isPalindromicNum(res)) {
        res = add(res, reverse(res));
        cnt ++;
    }
    print(res);
    printf("%d\n", cnt);
}
int main() {
    char str[100];
    int k;
    scanf("%s %d", str, &k);
    bign a = change(str);
    solve(a, k);
    return 0;
}
```



## 总结

### 方法归纳

​		三种类型的题目实际上是层层递进的，从最开始的辗转相除法求解最大公约数，进而解除最小公倍数。其中最大公约数可以说是基石，直接为后续分数约分做铺垫。虽说素数求解和最大公约数没有直接关系，但是思想还是有些类似的。素数判定的思想可用于质因子的求解上。大整数运算和分数四则运算本质都是模拟运算。需要掌握以下内容：

+ 最大公约数的欧几里得算法（辗转相除法），间接可求最小公倍数。

+ 分数的表示、标准化、四则运算、输出打印需要熟练使用模板，否则容易在细节上失分。

+ 素数的判断方法（$[2,\sqrt n ]$，右边是闭区间！！！！）、暴力求解/筛法求解素数表，暴力求解复杂度最低为$O(n\sqrt n)$，筛法为$O(nloglogn)$。

+ 质因子的表示及利用强化结论求解。

+ 大整数的表示、转换、四则运算，熟练使用模板，学习思路和分数四则运算一致。

	以上内容都不难，注重细节，合理使用模板，即可快速解题。

### 技巧收获

+ 循环右移问题令我意识到跳出思维惯性，站在宏观角度看待问题的奇妙，即三次反转，抽象能力有待提高。同时锻炼了对比分析能力，虚心参考他人的解法，比如学到了极为惊艳的一句printf完成输出结果末尾没多余空行。
+ 有理数的处理让然我对分数家族有了更为清晰的认识，如整数、真分数和假分数，同时对其表示有了更深的理解，以前总是停留在纸面。对加减乘除处理时第一次应用到了函数指针数组和字符串数组来简化代码，体验到良好的封装带来的简洁优雅。
+ 素数判断令我对素数/质数有了清晰的认识，同时也不再恐惧，他不过如此，并轻易掌握它的判断方式。对于素数表的算法令我深刻体会到时间复杂度的重要性，在我学会快速的筛法后就想着以后只要会这一种就可以了，暴力解法没啥用了，结果并非如此，在做题过程中发现使用筛法的前提需要先知道自然数的上界，而暴力不需要，比如我要求第100000个素数，筛法不知道上界是多大，只能凭感觉定义一个极其大的上界，而暴力不需要，最后二者一样是通过计算已知素数个数来退出循环。可见，存在即意义，细心发掘每个算法的自身特点及其适用情况对于融汇贯通是大有裨益的。
+ 通过做**hashing**不仅复习了哈希算法，同时对于之前一直没勇气没耐性看的解决冲突的几种方式也明了许多，如线性探测，正负二次探测和链地址法。这些听着令人望而生畏的名词其实不过尔尔，都是纸老虎，思想其实很简单。同时，将素数和hash联系起来，hash之所以采用素数做表的长度，是因为对素数取模可以减低冲突的概率。
+ 做质因子分解的题突然发现他和素数判断的思想的同源性。
+ 大整数模拟整体思路与分数四则运算模拟类似，在表示阶段，它还用了小端储存，因为四则运算中加减乘都是从低位到高位运算，可见出处体现着tradeoff思想。
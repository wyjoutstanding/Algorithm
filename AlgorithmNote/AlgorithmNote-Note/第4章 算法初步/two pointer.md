# 《算法笔记上机训练实战指南》习题报告

### 作者：wuyangjun

### 时间：2019/8/3

### 主题：two pointers

---

## [A1085/B1030 Perfect Sequence](https://pintia.cn/problem-sets/994805342720868352/problems/994805381845336064)

### 思路

​		之前是用二分法来解决，这里使用two pointers来解决，代码貌似更加简洁，但是不容易想到。具体思路如下：

​		首先，较容易获得以下性质：如果$a[j] \leq a[i] * p$成立，那么对[i,j]内的任意位置k，一定有$a[k] \leq a[i] * p$成立。这种有序序列的性质就引导我们往two pointers思想去思考，由此可以获得以下时间复杂度为O(n)的算法：

​		以long long型数组a存放读入的数据，并将其从小到大排序。令两个下标i,j的初值均为0,表示i,j均指向有序序列的第一个元素，并设计计数器cnt存放满足条件的最大长度。接下来让j不断增加，直到$a[j] \leq a[i] * p$不成立为止（此过程不断跟新cnt）。之后让下标i右移一位，继续让j增加的操作，依次类推，直至j到达末端。这个操作的目的在于，cnt始终存放满足条件下的i和j的最大距离。

### 注意点

+ p和a[i]均可能达到$10^9$，二者相乘超出了int范围，所以全部都用long long。

### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-03 11:20:30
 * @LastEditTime: 2019-08-03 11:26:33
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int main() {
    LL N, p;
    scanf("%lld %lld", &N, &p);
    vector<LL> a(N);
    for(int i = 0; i < N; i++) scanf("%lld", &a[i]);
    sort(a.begin(), a.end()); // 从小到大排序
    // two pointer
    int cnt = 1, i = 0, j = 0;
    while(i < N && j < N) {
        while(j < N && a[j] <= p * a[i]) {
            cnt = max(cnt, j - i + 1); //最大间距
            j ++;
        }
        i ++;
    }
    printf("%d\n", cnt);
    return 0;
}
```



## [B1035/A1089 插入与归并](https://pintia.cn/problem-sets/994805260223102976/problems/994805286714327040)

### 思路

​		直接模拟插入排序和归并排序的每一步过程，其中归并排序若采用递归写法无法满足题目要求，所以采用非递归写法。整体做法为：先进行插入排序，在执行过程中若发现其结果与给定序列吻合，那么说明是插入排序，计算出下一步后结束算法；若不是插入排序，根据题意可知其一定是归并排序，模拟归并排序过程，若执行过程发现与给定序列吻合，那么计算出下一步的序列后结束算法。

### 注意

+ 由于题目保证无二义性，所以初始序列和已经有序的序列不会出现在给定序列中。
+ 由于数据量较小，归并排序可以不写merge，可直接用sort函数。

### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-03 12:58:18
 * @LastEditTime: 2019-08-03 19:40:20
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
// 打印数组
void print(vector<int> &a) {
    for(int i = 0; i < a.size(); i++) {
        if(i == 0) printf("%d", a[i]);
        else printf(" %d", a[i]);
    }
    printf("\n");
}
// 比较两个等长数组，相等返回true
bool cmpArray(vector<int> &a, vector<int> &b) {
    bool equal = true;
    for(int i = 0; i < a.size(); i++) {
        if(a[i] != b[i]) {
            equal = false;
            break;
        }
    }
    return equal;
}
// 向a中插入a[idx]，返回插入后的容器
vector<int> insert(vector<int> &a, int idx) {
    int j = idx;
    while(j > 0 && a[j] < a[j-1]) {
        swap(a[j], a[j-1]);
        j --;
    }
    return a;
}
bool insertSort(vector<int> &a, vector<int> &b, vector<int> &ans) {
    bool isFind = false;
    for(int i = 1; i < a.size(); i++) {
        insert(a, i);
        if(cmpArray(a, b)) { //找到符合条件的序列
            ans = insert(a, i + 1); //插入下一个元素
            isFind = true;
            break;
        }
    }
    return isFind;
}
// 合并两个升序序列a[_i, _j)和a[_j,_k)到a[_i,_k)
vector<int> merge(vector<int> &a, int _i, int _j, int _k) {
    int i = _i, j = _j;
    vector<int> tmp = a;
    int cnt = _i;
    while(i < _j && j < _k) {
        if(a[i] < a[j]) tmp[cnt] = a[i++];
        else tmp[cnt] = a[j++];
        cnt ++;
    }
    while(i < _j) tmp[cnt++] = a[i++];
    while(j < _k) tmp[cnt++] = a[j++];
    a = tmp;
    return a;
}
// 归并排序迭代实现
void mergeSort2(vector<int> &a, vector<int> &b, vector<int> &ans) {
    int n = a.size();
    bool isFind = false;
    // 步长从1开始，2的幂次方
    for(int step = 1; step <= n; step *= 2) {
        // 以固定步长遍历序列
        for(int i = 0; i < n; i += 2*step) {
            merge(a, i, min(i + step, n), min(i + 2 * step, n)); //取最小值防止溢出
        }
        // 控制找到符合条件的序列后输出下一个状态
        if(isFind) {
            ans = a;
            break;
        }
        // 判断是否找到符合条件的状态
        if(cmpArray(a, b)) {
            isFind = true;
        }
    }
}
int main() {
    int n;
    scanf("%d", &n);
    vector<int> a(n), a2(n), b(n), ans(n);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    for(int i = 0; i < n; i++) scanf("%d", &b[i]);
    a2 = a;
    if(insertSort(a, b, ans)) printf("Insertion Sort\n");
    else {
        mergeSort2(a2, b, ans);
        printf("Merge Sort\n");
    }
    print(ans);
    return 0;
}
```



## [A1029 Median](https://pintia.cn/problem-sets/994805342720868352/problems/994805466364755968)

### 思路

​		看到这题最容易想到的解法是将两个数组用merge合并后输出中位数，正在为自己的仅为O(n)时间复杂度算法而沾沾自喜时，“内存超限”横空出世，第一次遇到内存问题，原来他的内存限制是1.5MB，一个数组个数最大可达$2*10^5$，若是使用long int，在OJ上占8个字节，一定超出限制，改为使用int，仅存储第一个数组，接着一个一个读入第二个数列，思想与merge相同，只不过此时第二个数列只有一个元素，同时对确定位置的进行计数cnt，若cnt符合输出位置，直接输出结束程序即可，多余的输入不处理也没问题，因为OJ是根据程序输出来判断对错的。

### C++

``` c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-03 19:58:27
 * @LastEditTime: 2019-08-03 21:51:28
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n1, n2;
    scanf("%d", &n1);
    vector<int> a(n1);
    for(int i = 0; i < n1; i++) scanf("%d", &a[i]);
    scanf("%d", &n2);
    // 避免内存超限，第二个数组边读边计数
    int idx; //第idx个输出
    if((n1 + n2) % 2 == 0) idx = (n1 + n2 - 1) / 2; //偶数
    else idx = (n1 + n2) / 2;   //奇数
    int t, j = 0, cnt = 0;
    for(int i = 0; i < n2; i++) {
        scanf("%d", &t);
        // a数组找到比t大的数
        while(j < n1 && a[j] < t) {
            // 满足条件立刻输出
            if(idx == cnt) {
                printf("%d", a[j]);
                return 0;
            }
            j ++;
            cnt ++;
        }
        // a遍历完或找到比t 大的数
        if(idx == cnt) {
            printf("%d", t);
            return 0;
        }
        cnt ++;
    }
    // 第二个数组遍历完依旧不到中位数
    while(j < n1) {
        if(idx == cnt) {
            printf("%d", a[j]);
            return 0;
        }
        cnt ++;
        j ++;
    }
    return 0;
}
```



## [A1048 Find Coins](https://pintia.cn/problem-sets/994805342720868352/problems/994805432256675840)

### 思路

​		之前用二分法求解，这里用two pointer再解一次。具体步骤如下：

​		步骤 1：使用sort函数将序列从小到大排序。

​		步骤 2：定义两个下标i,j，初值分别为0，n-1，并根据a[i]+a[j]和m的大小关系来进行操作

​		（1）若a[i]+a[j] == m，则表明找到了一组方案，退出循环，由于升序排列，第一个找到的就是最小的。

​		（2）若a[i]+a[j]  < m，则令i加1

​		（3）若a[i]+a[j]  > m，则令j减1

​		步骤 3：反复执行步骤2的操作，直至i>=j或找到第一组解，若不存在解，输出`No solution`。

### 注意

+ 强烈建议输出提示信息时不要手打，直接复制！！！

### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-03 22:16:44
 * @LastEditTime: 2019-08-03 22:27:03
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<int> a(n);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    sort(a.begin(), a.end());
    bool flag = false;
    int i = 0, j = n - 1;
    while(i < j) {
        if(a[i] + a[j] == m) {
            flag = true;
            printf("%d %d\n", a[i], a[j]);
            break;
        }
        else if(a[i] + a[j] < m) i++;
        else j--;
    }
    if(!flag) printf("No Solution\n");
    return 0;
}
```



## 总结

### 题型归纳

​		two pointers和二分似乎很接近，大部分题目二者都可以互换，都是高效的技巧。在以下四种情况下应用较多：

+ 等于关系：如**A1048**，碰到等于关系均可分三种情况来完成O(n)遍历
+ 不等关系：如**A1085/B1030**，它们无法向等于关系那样简单的分情况讨论，需要自己发现内在关系，明白已计算过的结果可以接着利用，推出下一步，关键是发现隐性关系，充分挖掘信息之间的关系。减少不必要的计算，从而降低复杂度。
+ 归并：merge的简单应用，O(n)复杂度合并两个有序序列为1个有序序列，如**B1035/A1089**；或者不存储合并结果和要被合并的一个序列，以此来降低空间复杂度，如**A1029**。如果元素个数较少，在不超时的情况下。通常使用sort替代merge。
+ 快排：partition简单应用

### 感悟

​		散列，二分，two pointers都是降低时间复杂度的强有力技巧，需要对各自特性了如指掌，同时注意区分三者之间的区别和适用场景，最后，需要从题目的表象看出问题的实质，从而使用相应技巧解决。

​		最近这些题变难了，自信心容易受挫，成就感很低，导致没有激情，效率降低，不过坚持下去，进步是极其明显的，迟早守得云开见月明，fighting！！！
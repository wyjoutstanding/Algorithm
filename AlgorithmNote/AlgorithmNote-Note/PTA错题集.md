# PTA错题集

## 第一次错 [PTA错题集.md](PTA错题集.md) 

[B1048 数字加密](<https://pintia.cn/problem-sets/994805260223102976/problems/994805276438282240>)



## 一点错

[A1001 A+B Format](<https://pintia.cn/problem-sets/994805342720868352/problems/994805528788582400>)：字符串，0未考虑，可以用do..while写法

[A1082 Read Number in Chinese](<https://pintia.cn/problem-sets/994805342720868352/problems/994805385053978624>): 字符串，0未考虑，特殊判断（100001234中万位不可输出）

[A1028 List Sorting](<https://pintia.cn/problem-sets/994805342720868352/problems/994805468327690240>)：排序，cin/cout导致超时，需使用scanf/printf，所以string用不了

[B1033 旧键盘打字](https://pintia.cn/problem-sets/994805260223102976/problems/994805288530460672)：散列，题目没看清，“`,`、`.`、`-`、`+`（代表上档键）“表示只有`+`是上档键，而不是4个都是

[B1020/A1070 月饼](https://pintia.cn/problem-sets/994805260223102976/problems/994805301562163200)：贪心，题目将的库存和总售价是正数，即有可能是浮点数，类型不可错

[1037 Magic Coupon](https://pintia.cn/problem-sets/994805342720868352/problems/994805451374313472)：贪心，集合中存在0未考虑，需要跳过它

[1067 Sort with Swap(0, i)](https://pintia.cn/problem-sets/994805342720868352/problems/994805403651522560)：超时，不可通过遍历来选择未归位的数，可用一个容器记录未归位的数。

[A1071 Speech Patterns](https://pintia.cn/problem-sets/994805342720868352/problems/994805398257647616)，map，输入的单词间可能没有空格，如`word1,word2`，不要局限于样例，多想想恶劣情况。

[B1025/A1074 反转链表](https://pintia.cn/problem-sets/994805260223102976/problems/994805296180871168)：链表，输入节点中可能存在不在以head为起始的链表上。

[A1032 Sharing](https://pintia.cn/problem-sets/994805342720868352/problems/994805460652113920)：链表，超时，**原因尚不清楚**，应该是遍历链表写法导致某些样例死循环，最好使用模板遍历。

[A1052 Linked List Sorting](https://pintia.cn/problem-sets/994805342720868352/problems/994805425780670464)：链表，有效节点数三种情况：0,1，n。没考虑0的特例。

[A1053 Path of Equal Weight](https://pintia.cn/problem-sets/994805342720868352/problems/994805424153280512)，树遍历，字典序比较时，默认情况需返回false，返回true都会**段错误**。

[A1034 Head of a Gang](https://pintia.cn/problem-sets/994805342720868352/problems/994805456881434624)：图遍历，段错误，记录最多1000条，因此不同的人最多可能为2000，数组必须开2000+

[A1014 Waiting in Line](https://pintia.cn/problem-sets/994805342720868352/problems/994805498207911936)：快乐模拟，队列数组模拟，无论顾客是否为sorry，均需进入队列（占位使用），否则导致后续顾客选错窗口。

## 两点错

[A1048 Find Coins](https://pintia.cn/problem-sets/994805342720868352/problems/994805432256675840)：two pointers，输出`No Solution`时大小写打错，以后直接复制，别手打！！！

[B1045/A1101 快速排序](https://pintia.cn/problem-sets/994805260223102976/problems/994805278589960192)：two pointers，格式错误，最后需要输出换行；思路不对，不能包含本位。

[B1049/A1104 数列的片段和](https://pintia.cn/problem-sets/994805260223102976/problems/994805275792359424)：简单数学，找规律题，用double，long long而不是float,int。

[A1060 Are They Equal](https://pintia.cn/problem-sets/994805342720868352/problems/994805409175420928)：string应用，前导0隐含条件没看出来。

[A1018 Public Bike Management](https://pintia.cn/problem-sets/994805342720868352/problems/994805489282433024)：最短路Dijkstra+DFS，题意理解错误，每个车站在前往问题车站过程中必须被调整好，回程时不调整。必须从起点开始模拟，路径是逆序存储，且计算点权时不可包括起点。

[A1072 Gas Station](https://pintia.cn/problem-sets/994805342720868352/problems/994805396953219072)：最短路，Dijkstra，题意很绕，先求所有最近房屋距离，选择距离尽可能大的最近房屋，第二标尺为平均距离小，第三标尺为下标小。同时四舍五入问题突出，与样例1矛盾。

[A1040 Longest Symmetric String](https://pintia.cn/problem-sets/994805342720868352/problems/994805446102073344)：动态规划，非回文没考虑清楚，需要跳过它。

### 三点错

[A1016 Phone Bills](<https://pintia.cn/problem-sets/994805342720868352/problems/994805493648703488>)：排序题意理解错误：存在无匹配记录的用户，无需输出；费用计算需考虑同一天同一个小时内的，若是采用模拟计算则无需考虑

[A1029 Median](https://pintia.cn/problem-sets/994805342720868352/problems/994805466364755968)：two pointers，内存超限，思路简单，merge求中位数即可，可内存仅1.5MB，只能一个个读入第二个序列，同时，long int 不一定是4字节，在OJ上是8字节。

[A1013 Battle Over Cities](https://pintia.cn/problem-sets/994805342720868352/problems/994805500414115840)：图的遍历，顶点从1开始编号，访问数组vis右边界为vis+N，少了1个。以后直接用vis+maxn，避免出错。

## 五点错

[A1103 Integer Factorization](https://pintia.cn/problem-sets/994805342720868352/problems/994805364711604224)：DFS，使用库函数pow且未合理剪枝导致超时，可见22以内的P次方记录在表中，后续直接查询即可。剪枝可极大降低复杂度。amazing！！！

[A1017 Queueing at Bank](https://pintia.cn/problem-sets/994805342720868352/problems/994805491530579968)：快乐模拟，队列+优先队列，没有考虑到排队队首顾客达到时刻大于当前时刻。

## 好题

[A1095 Cars on Campus](<https://pintia.cn/problem-sets/994805342720868352/problems/994805371602845696>)：是A1016的分类匹配处理和A1055查询时间复杂度优化的综合。

1、分类匹配有两种思路

+ 使用map<string,vector<Object> >映射
+ 直接对结构体数组按照规则排序，规则定义中string优先级高，再选一个属性作为第二优先，即可完成分类。

2、查询优化通常有以下技巧

+ 哈希打表是首选
+ 抓住题目的查询条件，对特定限制进行查询数组的优化
+ 使用scanf/printf替代cin/cout，熟练string和char[]的转换
+ 时间标准格式和最小单位之间的转换（相对间隔）

[B1008 数组元素循环右移问题](<https://pintia.cn/problem-sets/994805260223102976/problems/994805316250615808>)：gcd应用，规律好奇特，能够统一轮换和非轮换

[A1054 The Dominant Color](https://pintia.cn/problem-sets/994805342720868352/problems/994805422639136768)：map应用，若不用map实现，有以下结论：可通过**两两不同相消法**找到出现**次数超过一半**的数。

[A1043 Is It a Binary Search Tree](https://pintia.cn/problem-sets/994805342720868352/problems/994805440976633856)：BST，推理思路值得借鉴，任意序列可构建BST，前序遍历该BST，若结果和最初序列相同，说明最初是前序序列。（前序构建的BST的前序遍历还是自身）

[A1064 Complete Binary Search Tree](https://pintia.cn/problem-sets/994805342720868352/problems/994805407749357568)：CBST，完全二叉排序树构建，完全：静态数组；BST：中序遍历为有序。将输入序列升序排列，中序遍历空白完全二叉树时，依次填入相应数值。

[A1026 Table Tennis](https://pintia.cn/problem-sets/994805342720868352/problems/994805472333250560)：快乐模拟，队列+优先级，把特殊处理的唯一情况理清，分类讨论。

## 第一次不会做

[A1012 The Best Rank](<https://pintia.cn/problem-sets/994805342720868352/problems/994805502658068480>)：排序思路混乱，关键在于结构体设计

[A1055 The World's Richest](<https://pintia.cn/problem-sets/994805342720868352/problems/994805421066272768>)：排序的基本思路有，但是知道一定会**超时**。抓住条件查询次数M<=100，从而至多保留每个年龄段的前100名，这步预处理可有效降低时间复杂度

[A1033 To Fill or Not to Fill](https://pintia.cn/problem-sets/994805342720868352/problems/994805458722734080)：贪心，策略设计错误，应该选择第一个价格低于当前油价的点，而不是直接寻找最低油价点；不可达终点情况有二，只考虑两点距离大于满油行程，未考虑起点无加油站；终点应按照策略1处理。

[1038 Recover the Smallest Number](https://pintia.cn/problem-sets/994805342720868352/problems/994805449625288704)：贪心，仅想到策略的第一步且误认为不同长度的数字串可拼接后进行比较，导致思绪混乱，实际上是不存在影响的。证明的过程值得学习。

[A1044 Shopping in Mars](https://pintia.cn/problem-sets/994805342720868352/problems/994805439202443264)：二分，巧妙构造，通过累加每一项得到单调递增序列，枚举每个元素，从而使用二分法

[A1085/B1030 Perfect Sequence](https://pintia.cn/problem-sets/994805342720868352/problems/994805381845336064)：two pointers/二分，第一次用二分还好说，这次用two pointers一开始没啥思路，看了题解，豁然开朗，构思巧妙。

[B1003 我要通过！](https://pintia.cn/problem-sets/994805260223102976/problems/994805323154440192)：简单数学，一开始有些懵，规律没找到，从源头分析，找到规律，善用RE

[A1049 Counting Ones](https://pintia.cn/problem-sets/994805342720868352/problems/994805430595731456)：简单数学，一开始相用打表的思路是错的，没想到应该从每一位上出现1的次数找规律。

[A1096 Consecutive Factors](https://pintia.cn/problem-sets/994805342720868352/problems/994805370650738688)：质因子分解，其实和质因子没啥太大关系，只是借用[2,sqrt(n)]结论，然后暴力求解。

[A1056 Mice and Rice](https://pintia.cn/problem-sets/994805342720868352/problems/994805419468242944)：队列，题目半天没看懂，理解后就是**分组和排名**设置有些巧妙。

[A1068 Find More Coins](https://pintia.cn/problem-sets/994805342720868352/problems/994805402305150976)：动规，最初用dfs，最后的测试点超时，只能用01背包动规解法，这里的w和c一样。

## 巨坑（待填）

[A1010 Radix](https://pintia.cn/problem-sets/994805342720868352/problems/994805507225665536)：二分，20个测试样例就过15个，接着寸步难行，有数据溢出问题，上下界选择问题，一位数特例。随后再回来做



|                             题目                             |       类型        | 错误样例数 |                           格式                            |                             思路                             |                  数据类型                   | 时间复杂度 | 空间复杂度 |
| :----------------------------------------------------------: | :---------------: | :--------: | :-------------------------------------------------------: | :----------------------------------------------------------: | :-----------------------------------------: | :--------: | :--------: |
| [A1085/B1030 Perfect Sequence](https://pintia.cn/problem-sets/994805342720868352/problems/994805381845336064) | two pointers/二分 |     -1     |                                                           |                           题解精妙                           |                                             |            |            |
| [A1044 Shopping in Mars](https://pintia.cn/problem-sets/994805342720868352/problems/994805439202443264) |       二分        |     -1     |                                                           | 巧妙构造，通过累加每一项得到单调递增序列，枚举每个元素，从而使用二分法 |                                             |            |            |
| [A1048 Find Coins](https://pintia.cn/problem-sets/994805342720868352/problems/994805432256675840) |   two pointers    |     2      | 输出`No Solution`时大小写打错，以后直接复制，别手打！！！ |                                                              |                                             |            |            |
| [B1045/A1101 快速排序](https://pintia.cn/problem-sets/994805260223102976/problems/994805278589960192) |   two pointers    |     2      |                    最后需要输出换行；                     |                    思路不对，不能包含本位                    |                                             |            |            |
| [A1029 Median](https://pintia.cn/problem-sets/994805342720868352/problems/994805466364755968) |   two pointers    |     3      |                                                           | 思路简单，merge求中位数即可，可内存仅1.5MB，只能一个个读入第二个序列， | 同时，long int 不一定是4字节，在OJ上是8字节 |            |  内存超限  |


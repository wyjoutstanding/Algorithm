# 《算法笔记上机训练实战指南》习题报告

### 作者：wuyangjun

### 时间：2019/8/11~8/14

### 主题：二叉树+树遍历+BST+AVL+并查集+堆

---



[TOC]

## 二叉树遍历

### [A1020 Tree Traversals](https://pintia.cn/problem-sets/994805342720868352/problems/994805485033603072)

#### 思路

​		根据给定的后序和中序遍历序列，建立二叉树，并输出该二叉树的层序遍历序列。层序遍历与BFS模板一样，这里关键在于如何利用后序和中序遍历序列建立二叉树。

​		后序和中序区别在于根结点的访问时机不同，因此导致二者有不同性质，后序用来确定根，必定在序列的最右侧；根据后序得到的根结点，找到其在中序序列中的位置k，该位置的左右侧分别对应该根结点的左右子树。由因为在后序遍历序列中左右子树是分开的连续序列，因此可根据中序求得的左子树的结点数目计算出后序序列的左右子树区间。

​		令vector<int>post，in，layer分别存储后序、中序、层序遍历的序列。以下为建树的递归设计：

+ **接口设计**：`TNode* createTree(int postL, int postR, int inL, int inR)`，其中postL，postR表示后序遍历序列的区间：[postL,postR]（注意，左右皆为闭区间）；类似的，inL，inR表示中序遍历序列的区间：[inL,inR]。最后返回为头结点指针。
+ **边界**：当后序序列个数为0时表示遍历结束，即`postL>postR`，注意区间左闭右闭，所以取等时有1个结点结点。这里由于没有约束，所以也没有剪枝。
+ **递归式**：每个结点均有两条路可走，左右子树。后序最右侧元素为post[postR]，找到其在中序in中的位置k，可计算出in左侧连续序列（左子树）长度numLeft=k-inL，因此该二叉树的左子树对应两个序列的区间：`post:[postL,postL+numLeft-1] in:[inL,k-1]`；同理，其右子树对应两个序列的区间：`post:[postL+numLeft,postR-1] in:[k+1,inR]`。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-11 14:48:08
 * @LastEditTime: 2019-08-11 15:24:04
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct TNode { //树结点
    int data;
    TNode *lchild, *rchild;
    TNode() { //默认构造函数初始化
        lchild = NULL;
        rchild = NULL;
    }
};
int n; //结点个数
vector<int> post, in, layer; //存放后、中、层序遍历结果
TNode* createTree(int postL, int postR, int inL, int inR) {
    if(postL > postR) return NULL; //后序遍历结束，返回
    TNode* root = new TNode; //申请结点
    root->data = post[postR]; //数据域,后序从最右边开始
    // 找到根在中序的位置
    int k  = find(in.begin() + inL, in.begin() + inR + 1, post[postR]) - in.begin();
    int numLeft = k - inL; //左子树结点个数
    // 左子树：post:[postL,postL+numLeft-1] in:[inL,k-1]
    root->lchild = createTree(postL, postL + numLeft - 1, inL, k - 1);
    // 右子树：post:[postL+numLeft,postR-1] in:[k+1,inR]
    root->rchild = createTree(postL + numLeft, postR - 1, k + 1, inR);
    return root; //返回根结点
}
// 层序遍历：与BFS一样
void layerTraverse(TNode* root) {
    queue<TNode*> q;
    q.push(root);
    while(!q.empty()) {
        TNode* now = q.front();
        q.pop();
        layer.push_back(now->data);
        if(now->lchild != NULL) q.push(now->lchild);
        if(now->rchild != NULL) q.push(now->rchild);
    }
}
// 读入数据
void readData() {
    scanf("%d", &n);
    int t;
    for(int i = 0; i < n; i ++) {
        scanf("%d", &t);
        post.push_back(t);
    }
    for(int i = 0; i < n; i ++) {
        scanf("%d", &t);
        in.push_back(t);
    }
}
// 打印层序结果
void showResult() {
    for(int i = 0; i < n; i ++) {
        printf("%d%s", layer[i], i == n - 1 ? "\n" : " ");
    }
}
int main() {
    readData();
    layerTraverse(createTree(0, n - 1, 0, n - 1));
    showResult();
    return 0;
}
```



### [A1086 Tree Traversals Again](https://pintia.cn/problem-sets/994805342720868352/problems/994805380754817024)

#### 思路

​		题目已经明确用栈模拟中序遍历，所以pop顺序就是中序遍历的顺序。但此题关键在于发现push顺序就是前序遍历。知道这规律后有两种思路解决：

+ **前序+中序建树**：现在已知push顺序为前序遍历顺序，pop顺序为中序遍历顺序，那么问题就转换为已知前序和中序，重构出二叉树，再输出其后续遍历。具体实现与上一题**A1020**基本一致，只是将后序变为前序。
+ **前序建树**：如果把pop看成一个NULL标识符，一遇到pop操作就返回，其实就是带着分割标记的前序遍历建树。可以在输入的时候直接建树。但此题最好将输入数据处理完后再用数组来建立，比较清晰。可以定义一个vector<int>op来记录每一个操作，若当前操作是push，则记录相应数值；否则，记录-1，表示是pop操作。

​		知道push顺序为前序后问题变得简单许多，那么问题来了，怎么发现的？两种方式：

​	（1）直接从输入输出样例猜测验证规律，较难发现

​	（2）熟悉栈模拟中序遍历的过程：直观来说，从当前点出发，只要其左子树非空，就将其入栈，反复执行直至左子树为空，此时将栈顶出栈，访问它，在将当前点更新为其右子树，重复之前操作

1. 从当前点root开始，若root左子树非空，将其入栈，同时将root更新为其左子树。重复以上过程直至root为空
2. 弹出栈顶top，访问top，并将root更新为top的右子树。
3. 重复1,2两步，直至栈空。（do...while结构较易实现）

​		了解栈实现中序遍历的算法后，通过模拟该过程也能发现这其实就是前序建树。

#### C++（前序+中序建树）

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-11 19:17:16
 * @LastEditTime: 2019-08-11 19:33:31
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct TNode {
    int data;
    TNode *lchild, *rchild;
};
int n;
vector<int> pre, in, post; //前中后序遍历结果
TNode* createTree(int preL, int preR, int inL, int inR) {
    if(preL > preR) return NULL; //边界
    TNode* root = new TNode;
    root->data = pre[preL]; //左侧第一个数为根
    // 根在in中的位置
    int k = find(in.begin() + inL, in.begin() + inR + 1, root->data) - in.begin();
    int numLeft = k - inL;//左子树结点个数
    root->lchild = createTree(preL + 1, preL + numLeft, inL, k - 1);
    root->rchild = createTree(preL + numLeft + 1, preR, k + 1, inR);
    return root;
}
void postTraverse(TNode* root) {
    if(root == NULL) return;
    postTraverse(root->lchild);
    postTraverse(root->rchild);
    post.push_back(root->data);
}
void showResult() {
    for(int i = 0; i < post.size(); i ++) {
        printf("%d%s", post[i], i == post.size() - 1 ? "\n" : " ");
    }
}
void init() {
    scanf("%d", &n);
    string str;
    int t;
    stack<int> s; 
    // 读入数据并计算出先序和中序序列
    for(int i = 0; i < 2 * n; i ++) {
        cin >>str;
        if(str == "Push") {
            scanf("%d", &t);
            pre.push_back(t); //push对应前序
            s.push(t); //栈为了中序输出
        }
        else {
            in.push_back(s.top()); //中序
            s.pop();
        }
    }
}
int main() {
    init();
    postTraverse(createTree(0, n - 1, 0, n - 1));
    showResult();
    return 0;
}
```

#### C++（前序建树）

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-11 16:47:03
 * @LastEditTime: 2019-08-11 17:19:26
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct TNode {
    int data;
    TNode *lchild, *rchild;
};
vector<int> op, post; //操作序列、后序遍历结果
int N, cnt = 0; //结点总数、当前操作下标
// 遍历操作数组，idx为全局变量cnt的引用，表示当前的操作
TNode* createTree(int &idx) {
    // 遍历完所有操作或pop直接返回空
    if(idx == 2 * N || op[idx] == -1) return NULL;
    TNode* root = new TNode;
    root->data = op[idx];
    root->lchild = createTree(++idx); //左子树优先
    root->rchild = createTree(++idx);
    return root;
}
// 后序遍历
void postTraverse(TNode* root) {
    if(root == NULL) return;
    postTraverse(root->lchild);
    postTraverse(root->rchild);
    post.push_back(root->data);
}
// 打印结果
void showResult() {
    for(int i = 0; i < N; i ++) {
        printf("%d%s", post[i], i == N - 1 ? "\n" : " ");
    }
}
int main() {
    scanf("%d", &N);
    string s;
    int t;
    for(int i = 0; i < 2 * N; i ++) {
        cin >>s;
        if(s == "Push") { //push存放输入的数据
            scanf("%d", &t);
            op.push_back(t);
        }
        else op.push_back(-1); //pop用-1表示
    }
    postTraverse(createTree(cnt));
    showResult();
    return 0;
}
```



### [A1102 Invert a Binary Tree](https://pintia.cn/problem-sets/994805342720868352/problems/994805365537882112)

#### 思路

​		步骤 1：根据题目给出的N个结点编号的关系，用静态数组建立静态二叉树。定义结构体STNode，其中lchild，rchild，father依次表示结点的左、右孩子和父结点的下标，初值均为-1，表示NULL。因为这里数组下标即为数据，所以data没有也行。其结构如下:

```c++
struct STNode {
    int data; //和下标一样，所以不要此项也行
    int lchild, rchild, father; //左右子树, 父结点下标
    STNode() { //初始化，-1表示NULL
        lchild = -1;
        rchild = -1;
        father = -1;
    }
}STree[maxn]; //静态数组实现
```

​		步骤 2：类似并查集方式找到根结点，即遍历所有结点now，只要now的左或由子树非空，将非空子树的father设置为now的下标，表示now是他们的父结点。遍历结束后，除根结点外所有结点的父结点都被标记，此时在遍历一次找出father为-1的结点，它就是根结点。

​		步骤 3：使用先序或后续遍历均可轻易反转二叉树，但先序在定义上有些说不过去，因为反转后左右子树交换，此时访问左子树等价于访问右子树，所以访问顺序变为根、右、左。与原先的根、左、右顺序相违背，不过二者效果一样。

​		步骤 4：定义vector<int>layer,in来保存层序和中序遍历的结果，以便于输出。层序和中序遍历只需要在动态二叉树的基础上稍微修改即可。

#### 注意点

+ scanf的%c格式可读入换行符，所以使用前先用getchar吸收换行，或者在c之前加上\*,也可以多吸收一个字符，即`scanf("%*c",&ch)`。
+ 测试时从结点数：0、1、2、3和题目给定N来测试。由于二叉树编程是根据其递归定义而来，因此前几个可看成边界测试，保证边界正确，最后一个是递归式测试，保证逻辑正确。等价于递归测试。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-11 20:27:00
 * @LastEditTime: 2019-08-11 21:02:23
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 21;
struct STNode {
    int data; //和下标一样，所以不要此项也行
    int lchild, rchild, father; //左右子树, 父结点下标
    STNode() { //初始化，-1表示NULL
        lchild = -1;
        rchild = -1;
        father = -1;
    }
}STree[maxn]; //静态数组实现
vector<int> layer, in;
// 查找根结点，类似并查集
int findRoot(int N) {
    for(int i = 0; i < N; i ++) {
        if(STree[i].lchild != -1) STree[STree[i].lchild].father = i;
        if(STree[i].rchild != -1) STree[STree[i].rchild].father = i;        
    }
    for(int i = 0; i < N; i ++) {
        if(STree[i].father == -1) return i;
    }
}
// 交换左右子树
void invertBT(int root) {
    // 空结点则结束
    if(root == -1) return;
    swap(STree[root].lchild, STree[root].rchild); //交换左右子树下标
    invertBT(STree[root].lchild);
    invertBT(STree[root].rchild);
}
// 层序遍历
void layerTraverse(int root) {
    queue<int> q;
    q.push(root);
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        layer.push_back(now);
        if(STree[now].lchild != -1) q.push(STree[now].lchild);
        if(STree[now].rchild != -1) q.push(STree[now].rchild);
    }
}
// 先序遍历
void inTraverse(int root) {
    if(root == -1) return;
    inTraverse(STree[root].lchild);
    in.push_back(root);
    inTraverse(STree[root].rchild);
}
void showResult() {
    for(int i = 0; i < layer.size(); i ++) {
        printf("%d%s", layer[i], i == layer.size() - 1 ? "\n" : " ");
    }
    for(int i = 0; i < in.size(); i ++) {
        printf("%d%s", in[i], i == in.size() - 1 ? "\n" : " ");
    }
}
int main() {
    int n;
    scanf("%d", &n);
    char a, b;
    for(int i = 0; i < n; i ++) {
        getchar(); //必须先吸收换行
        scanf("%c %c", &a, &b);
        if(a != '-') STree[i].lchild = a - '0';
        if(b != '-') STree[i].rchild = b - '0';
    }
    int root = findRoot(n);
    invertBT(root);
    layerTraverse(root);
    inTraverse(root);
    showResult();
    return 0;
}
```

### 小结

​		二叉树的遍历与建立息息相关，根据题目所给数据形式，常见建立二叉树方法可分为标记法，结点关系和中+前/后/层三种类型。

（1）**标记法**：例如给出前序表示`1 2 4 # # 5 # # 3 # #`，直接用相应的遍历方式在读入时建树即可。例如**A1086**的前序建树。

（2）**结点关系**：题目给定结点间的关系，用**静态数组**建立二叉树最容易，例如**A1102**，其操作与动态二叉链表基本一致，甚至更简单。

（3）**中+前/后/层序**：给定中序序列和前序、后序、层序遍历中的任意一种都可以唯一还原一棵二叉树。其中中序与前序和后序重构思路基本一致，如**A1020**和**A1086**。至于中序和层序则可以每次将子树的层序遍历结果存储起来，在进行递归。

​		由于二叉树的递归定义性质导致大多数算法都是递归实现，不易调试，所以建议考虑清楚再动手，将接口设计，递归边界和递归式想明白。同时，测试也可利用其递归特性，先测试边界：结点个数为0，1，2，3。正确后在测试题目给定的结点为N的二叉树，保证递归式正确，这样基本就没问题了。



## 树的遍历

### [A1090 Highest Price in Supply Chain](https://pintia.cn/problem-sets/994805342720868352/problems/994805376476626944)

#### 思路

​		给定一颗销售供应的树，树根唯一，在树根出的价格为P，然后从根结点开始每往子结点走一层，该层的货物价格会在父结点的价格上增加r%。要求所有叶结点中的最高价格以及这个价格的结点个数。

​		使用DFS和BFS均可解题，具体如下。

（1）BFS就是层次遍历，每层的单价都一样，越往下走单价越高，因此，只需计算最后一层的价格和个数即可。（2）DFS则需遍历所有结点，每次找到叶子结点都取单价较高者。具体设计如下：

+ **接口设计**：`void dfs(int root, double price)`，root表示当前结点，price表示当前结点的单价。
+ **边界**：当前结点为叶子结点，无孩子即`STree[root].child.empty()`为真。若当前价格大于全局最大价格maxPrice，更新maxPrice为price，同时全局最大价格结点计数器tot置1；若maxPrice==price，则tot加1，表示最大价格的结点数加1。
+ **递归式**：遍历当前结点的所有子结点，并更新价格为`price * (1 + r / 100)`。

#### 注意点

+ 第二行输入的第i个值$x_i$表示第i个结点的**父结点**为$x_i$。若$x_i$为-1，表明i为根结点。
+ r是不带百分号的，所以计算时需除以100。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-12 10:35:31
 * @LastEditTime: 2019-08-12 10:54:34
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
struct STNode {
    vector<int> child;
}STree[maxn];
double P, r, maxPrice = -1; //root单价，增加比率，最大单价
int tot = 0; // 最大单价的个数
// 找到单价最高的叶子个数及其最大值
void dfs(int root, double price) {
    // 叶子，retailers
    if(STree[root].child.empty()) {
        if(maxPrice < price) {
            maxPrice = price;
            tot = 1; //重新找到最大值
        } 
        else if(maxPrice == price) tot ++; //最大值个数
        return;
    }
    // 遍历所有子结点
    for(auto p : STree[root].child) {
        dfs(p, price * (1 + r / 100));
    }
}
int readData() {
    int n;
    scanf("%d %lf %lf", &n, &P, &r);
    int t, root;
    for(int i = 0; i < n; i ++) {
        scanf("%d", &t);
        if(t != -1) {
            STree[t].child.push_back(i);
        }
        else root = i; // 根节点
    }
    return root;
}
int main() {
    int root = readData();
    dfs(root, P);
    printf("%.2lf %d\n", maxPrice, tot);
    return 0;
}
```



### [A1079 Total Sales of Supply Chain](https://pintia.cn/problem-sets/994805342720868352/problems/994805388447170560)

#### 思路

​		这道题是上题**A1090**的加强版，在其基础上增加约束：叶子结点具有权值。同时要求计算出所有叶子的售价之和。其实和上面一题思路几乎一样，只要遍历到每个叶子时乘以权值，并累加所有叶子的价格即可。

​		因此也可用BFS和DFS解决，BFS较直观，DFS代码简洁，根据个人喜好选择，以下给出各自的代码。

#### C++（BFS）

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-12 08:35:40
 * @LastEditTime: 2019-08-12 09:20:57
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
// 静态二叉树
struct STNode {
    double data, price; //权值和单价
    vector<int> child; //孩子
    bool isRoot; //便于判断是否为根
    STNode() {isRoot = true;}
}STree[maxn];
double P, r, tot = 0; //根单价、增加比率、总价
int N; //结点个数
void layerTravesal(int root) {
    queue<int> q;
    q.push(root);
    STree[root].price = P; //根销售的单价
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        double price = (now == root) ? STree[now].price : STree[now].price * (1 + r / 100); //下一层的单价,r%，有百分号
        // 叶子，即retailer
        if(STree[now].child.empty()) tot += price * STree[now].data;
        else {
            for(auto p : STree[now].child) {
                STree[p].price = price;
                q.push(p);
            }
        }
    }
}
void readData() {
    scanf("%d %lf %lf", &N, &P, &r);
    int n, idx;
    double t;
    for(int i = 0; i < N; i ++) {
        scanf("%d", &n);
        if(n == 0) { //叶子，，retailers
            scanf("%lf", &t);
            STree[i].data = t;
        }
        else { //suppliers，distributors
            for(int j = 0; j < n; j ++) {
                scanf("%d", &idx);
                STree[i].child.push_back(idx);
                STree[idx].isRoot = false; //i为idx的父结点
            }
        }
    }
}
// 找到root
int findRoot() {
    for(int i = 0; i < N; i ++) {
        if(STree[i].isRoot) return i;
    }
}
int main() {
    readData();
    int root = findRoot();
    layerTravesal(root);
    printf("%.1lf\n", tot);
    return 0;
}
```

#### C++(DFS)

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-12 09:54:35
 * @LastEditTime: 2019-08-12 10:15:26
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
// 静态二叉树
struct STNode {
    double data, price; //权值和单价
    vector<int> child; //孩子
    bool isRoot; //便于判断是否为根
    STNode() {isRoot = true;}
}STree[maxn];
double P, r, tot = 0; //根单价、增加比率、总价
int N; //结点个数
// root：当前结点 price：当前销售单价
double dfs(int root, double price) {
    // 叶子，即retailer
    if(STree[root].child.empty()) return price * STree[root].data;
    double tot = 0; //总和
    // 遍历所有孩子
    for(auto p : STree[root].child) {
        tot += dfs(p, price * (1 + r / 100)); //r%增比
    }
    return tot;
}
void readData() {
    scanf("%d %lf %lf", &N, &P, &r);
    int n, idx;
    double t;
    for(int i = 0; i < N; i ++) {
        scanf("%d", &n);
        if(n == 0) { //叶子，，retailers
            scanf("%lf", &t);
            STree[i].data = t;
        }
        else { //suppliers，distributors
            for(int j = 0; j < n; j ++) {
                scanf("%d", &idx);
                STree[i].child.push_back(idx);
                STree[idx].isRoot = false; //i为idx的父结点
            }
        }
    }
}
// 找到root
int findRoot() {
    for(int i = 0; i < N; i ++) {
        if(STree[i].isRoot) return i;
    }
}
int main() {
    readData();
    int root = findRoot();
    tot = dfs(root, P);
    printf("%.1lf\n", tot);
    return 0;
}
```

### [A1094 The Largest Generation](https://pintia.cn/problem-sets/994805342720868352/problems/994805372601090048)

#### 思路

​		考察树的层序遍历，DFS或BFS实现均可，这里采用BFS。首先定义一个全局cnt数组，记录每一层的个数，初值为0。每个结点出队时令相应cnt+1即可。最后取出最大值。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-12 11:31:15
 * @LastEditTime: 2019-08-12 12:01:12
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
struct STNode {
    int layer;
    vector<int> child;
}STree[maxn];
int cnt[maxn] = {0};
void layerTraversal(int root) {
    queue<int> q;
    STree[root].layer = 1;
    q.push(root);
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        cnt[STree[now].layer] ++; // 层号出现次数计算
        for(auto p : STree[now].child) {
            STree[p].layer = STree[now].layer + 1;
            q.push(p);
        }
    }
} 
void readData() {
    int N, M;
    scanf("%d %d", &N, &M);
    int cur, n, idx;
    for(int i = 0; i < M; i++) {
        scanf("%d %d", &cur, &n);
        for(int j = 0; j < n; j ++) {
            scanf("%d", &idx);
            STree[cur].child.push_back(idx);
        }
    }
}
int main() {
    readData();
    layerTraversal(1);
    int maxCnt = -1, ans;
    for(int i = 0; i < maxn; i ++) {
        if(maxCnt < cnt[i]) {
            maxCnt = cnt[i];
            ans = i;
        }
    }
    printf("%d %d\n", maxCnt, ans);
    return 0;
}
```



### [A1106 Lowest Price in Supply Chain](https://pintia.cn/problem-sets/994805342720868352/problems/994805362341822464)

#### 思路

​		这题就是将**A1090**的dfs思路和**A1079**的数据处理融合在一块，所以只在**A1090**的基础上稍作修改，变成求最小值即可。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-12 13:43:22
 * @LastEditTime: 2019-08-12 13:53:27
 * @Github: https://github.com/wyjoutstanding
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
struct STNode {
    vector<int> child;
    bool isRoot;
    STNode() {isRoot = true;}
}STree[maxn];
double P, r, minPrice = 0x7fffffffffff; //root单价，增加比率，最大单价
int N, tot = 0; // 最大单价的个数
// 找到单价最高的叶子个数及其最大值
void dfs(int root, double price) {
    // 叶子，retailers
    if(STree[root].child.empty()) {
        if(minPrice > price) {
            minPrice = price;
            tot = 1; //重新找到最大值
        } 
        else if(minPrice == price) tot ++; //最大值个数
        return;
    }
    // 遍历所有子结点
    for(auto p : STree[root].child) {
        dfs(p, price * (1 + r / 100));
    }
}
void readData() {
    scanf("%d %lf %lf", &N, &P, &r);
    int n, idx;
    double t;
    for(int i = 0; i < N; i ++) {
        scanf("%d", &n);
        if(n != 0) { //叶子，，retailers
            for(int j = 0; j < n; j ++) {
                scanf("%d", &idx);
                STree[i].child.push_back(idx);
                STree[idx].isRoot = false; //i为idx的父结点
            }
        }
    }
}
// 找到root
int findRoot() {
    for(int i = 0; i < N; i ++) {
        if(STree[i].isRoot) return i;
    }
}
int main() {
    readData();
    int root = findRoot();
    dfs(root, P);
    printf("%.4lf %d\n", minPrice, tot);
    return 0;
}
```



### [A1004 Counting Leaves](https://pintia.cn/problem-sets/994805342720868352/problems/994805521431773184)

#### 思路

​		输出每一层的叶子结点数，BFS和DFS均可，BFS常规思路即可实现。这里解释下DFS做法：

+ **接口设计**：`void dfs(int root, int depth) `，其中root表示当前结点，depth表示当前结点的深度，根结点算第1层。
+ **边界**：遇到叶子结点，将该深度对应的叶子数加1，同时更新最大深度。
+ **递归式**：遍历当前结点的每一个孩子结点。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-12 14:11:40
 * @LastEditTime: 2019-08-12 14:29:01
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
struct STNode {
    vector<int> child;
    bool isRoot; //判断是否为根
    STNode() {isRoot = true;}
}STree[maxn];
int N, M, maxLayer = -1; //结点个数、非叶子个数、最大层数
int leafs[maxn] = {0}; // 每一层叶子个数
// root：当前结点 depth：当前深度
void dfs(int root, int depth) {
    if(STree[root].child.empty()) {
        leafs[depth] ++;
        if(maxLayer < depth) maxLayer = depth; //最大深度
        return;
    }
    for(auto p : STree[root].child) {
        dfs(p, depth + 1);
    }
}
void readData() {
    scanf("%d %d", &N, &M);
    int id, k, idx;
    for(int i = 0; i < M; i ++) {
        scanf("%d %d", &id, &k);
        for(int j = 0; j < k; j ++) {
            scanf("%d", &idx);
            STree[id].child.push_back(idx);
            STree[idx].isRoot = false; //不是根
        }
    }
}
// 从1开始找
int findRoot() {
    for(int i = 1; i < N; i ++) {
        if(STree[i].isRoot) return i;
    }
}
int main() {
    readData();
    int root = findRoot();
    dfs(root, 1);
    for(int i = 1; i <= maxLayer; i ++) {
        printf("%d%s", leafs[i], i == maxLayer ? "\n" : " ");
    }
    return 0;
}
```

### [A1053 Path of Equal Weight](https://pintia.cn/problem-sets/994805342720868352/problems/994805424153280512)

#### 思路

​		DFS搜索每一条从根到叶子的路径，在过程中记录经过的结点权值，并计算总和，满足条件则保留结果。由于题目要求路径按照字典序非升序输出，因此可以在输入时将每个节点的子结点从大到小排序，这样权值大的结点一定先被搜索到。若是不这样处理，而是采用cmp排序方式，则必须注意cmp的每一种情况均要有返回值，且默认返回值必须为false，为true的话最后一个样例照样会出现段错误。

​		DFS详细解释如下：

+ **接口设计**：`void dfs(int root, int sum)`，root为当前结点 ，sum表示从根到当前结点的权重总和（不包括当前结点）
+ **边界+剪枝**：当前结点为叶子时，若总和为S时，保存该当前路径。当总和大于等于S时，可知再继续搜索也不存在解，因此可直接返回，此乃剪枝。
+ **递归式**：遍历当前结点的所有子结点。

​		其中使用vector<int>tmp来保存当前路径，进入递归时将其推入tmp，返回退出时将其pop。

#### 注意点

+ cmp函数每一种情况必须都有返回，若有默认返回，则必须是false，不能为true，不知道为什么？？

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-12 14:50:47
 * @LastEditTime: 2019-08-12 16:10:17
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
struct STNode {
    int data; //权重
    vector<int> child;
}STree[maxn];
int N, M, S;
vector<int> tmp; //临时存放符合条件序列
vector<vector<int> > ans; //结果存放
// root：当前结点 sum：从根到当前结点的权重总和（不包括当前结点）
void dfs(int root, int sum) {
    sum += STree[root].data;
    tmp.push_back(STree[root].data); //保存路径权重
    if(STree[root].child.empty()) { //叶子
        if(sum == S) { //满足条件
            ans.push_back(tmp); //保存结果
        }
        return ;
    }
    if(sum >= S) return; //剪枝
    for(auto p : STree[root].child) { //遍历所有子结点
        dfs(p, sum); 
        tmp.pop_back(); //弹出返回的结点
    }
}
// 字典序非升序
bool cmp(vector<int> &a, vector<int> &b) {
    int len = min(a.size(), b.size());
    for(int i = 0; i < len; i ++) {
        if(a[i] != b[i]) return a[i] > b[i];
    }
    return false; //完全相同，必须返回false，返回true/不写这个会报段错误
}
void showResult() {
    sort(ans.begin(), ans.end(), cmp); //字典序非降序排列
    for(auto vec : ans) {
        for(int i = 0; i < vec.size(); i ++) {
            printf("%d%s", vec[i], i == vec.size() - 1 ? "\n" : " ");
        }
    }
}
void readData() {
    scanf("%d %d %d", &N, &M, &S);
    for(int i = 0; i < N; i ++) scanf("%d", &STree[i].data);
    int id, k, idx;
    for(int i = 0; i < M; i ++) {
        scanf("%d %d", &id, &k);
        for(int j = 0; j < k; j ++) {
            scanf("%d", &idx);
            STree[id].child.push_back(idx);
        }
    }
}
int main() {
    readData();
    dfs(0, 0);
    showResult();
    return 0;
}
```



### 小结

​		普通树的操作一般都是用静态数组实现，然后考察一些先序、层次遍历（DFS、BFS），例如统计每一层叶子个数（**A1094、A1004**）、统计根到叶子的路径和的最大或最小值（**A1090**、**A1079**、**A1106**、**A1053**）。

​		大多数题目使用DFS和BFS都是可行的，各有优劣。BFS较直观，符合人的认知，便与思考调试，但代码量稍大；DFS则与BFS相反，思维量较大，不易调试，结点数过多时容易爆栈，但代码简洁。

​		由于普通树遍历的思路与二叉树无二，关键在于存储结构，通常使用以下静态结构：

```c++
struct STNode {
    dataType data; //数据
    int layer; //层号
    vector<int> child; //孩子结点编号
}STree[maxn];
```



## 二叉查找树（BST）

### [A1043 Is It a Binary Search Tree](https://pintia.cn/problem-sets/994805342720868352/problems/994805440976633856)

#### 思路

​		根据给定的序列，判断其是否为某个BST或镜像BST的前序遍历序列，若是，则输出相应BST的后序遍历序列。如何判断是个难题，先看以下**性质**：

1. 以任意一个序列的顺序作为BST的插入顺序，都可以建立一棵BST。

2. 给定一棵BST，得到它的前序遍历序列A。以序列A作为BST结点的插入顺序，那么一定可以还原出最初的BST。

​		那么，假设现在输入的序列为B，借用第一个性质，建立了一棵BST，记为T1，此时先序遍历T1得到序列C，若B为T1的前序遍历序列，那么根据性质2可知B==C；否则，B!=C。因此，可用这种方式去验证B是否为一棵BST的前序遍历序列。

​		对于**镜像BST**的处理有3种方式：

1. 写一个镜像BST的结点插入函数，只需让插入的值**x大于等于当前点**的值时，向左子树递归插入；否则向右递归插入。这样在读入数据时同时建立两棵树，就可以只写一份先序和后序遍历。
2. 与第二种相反，不多写插入函数，而是多写对于镜像BST的先序和后序遍历函数，只需将原来的先序后序左右子树访问位置交换即可。
3. 建立BST后，直接反转BST，得到镜像BST。可写一个反转递归函数invert，若当前结点非空，交换左右子树，接着对左右子树递归执行交换，先序或后续均可实现。

#### 注意点

+ 对于BST的定义众说纷纭，国内数据结构严书定义BST左右子树与当前结点是严格小于和大于关系，算法笔记的定义左子树可以取等，算法导论两边都可以取等，**而这一题，只有右边可以取等**。正好凑齐4种组合，以后还是以题目定义为准，不要先入为主，导致不应该的错误。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-12 20:58:11
 * @LastEditTime: 2019-08-12 21:34:22
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct TNode {
    int data;
    TNode *lchild, *rchild;
    TNode() {
        lchild = NULL;
        rchild = NULL;
    }
};
TNode *root = NULL, *rootImage = NULL; //正常和镜像BST
vector<int> origin, preNormal, preImage, post; //存放输入、先序、先序镜像、后序序列
// 正常插入
void insert(TNode* &root, int x) {
    if(root == NULL) {
        root = new TNode;
        root->data = x;
        return;
    }
    if(x < root->data) insert(root->lchild, x);
    else insert(root->rchild, x);
}
// 镜像插入：只需改变大小关系即可
void insertImage(TNode* &root, int x) {
    if(root == NULL) {
        root = new TNode;
        root->data = x;
        return;
    }
    if(x >= root->data) insertImage(root->lchild, x);
    else insertImage(root->rchild, x);
}
// 创建正常和镜像BST
void createBST() {
    int N;
    scanf("%d", &N);
    int t;
    for(int i = 0; i < N; i ++) {
        scanf("%d", &t);
        origin.push_back(t); //保存原始序列
        insert(root, t); //正常BST
        insertImage(rootImage, t); //镜像BST
    }
}
// 先序遍历
void preorderTraversal(TNode* root, vector<int> &pre) {
    if(root == NULL) return;
    pre.push_back(root->data);
    preorderTraversal(root->lchild, pre);
    preorderTraversal(root->rchild, pre);
}
// 后序遍历
void postorderTraversal(TNode* root) {
    if(root == NULL) return;
    postorderTraversal(root->lchild);
    postorderTraversal(root->rchild);
    post.push_back(root->data);
}
void print(TNode* root) {
    printf("YES\n");
    postorderTraversal(root);
    for(int i = 0; i < post.size(); i ++) {
        printf("%d%s", post[i], i == post.size() - 1 ? "\n" : " ");
    }
}
int main() {
    createBST();
    preorderTraversal(root, preNormal);
    preorderTraversal(rootImage, preImage);
    if(origin == preNormal) print(root);
    else if(origin == preImage) print(rootImage); 
    else printf("NO\n");
    return 0;
}
```



### [A1064 Complete Binary Search Tree](https://pintia.cn/problem-sets/994805342720868352/problems/994805407749357568)

#### 思路一

​		根据所给序列，构建一棵完全二叉排序树，并输出该树的层序遍历序列。

​		目标是完全二叉排序树，在二叉树基础上，增加了两个约束，一是完全树，二是排序树。两个约束在这不太好思考，所以先固定一个约束，尝试使用静态数组来固定完全树（若二叉树有N个结点，开辟大小为N+1的数组，下标表示结点，对于任意结点x，2x，2x+1分为为其左右子树）。所以只要开辟好数组，那么一个完全二叉树的结构就确定了，因此只需要确定每个结点的数值即可。那么如何确定每个结点的值呢？

​		考虑到第二个约束，想到二叉树的性质：中序遍历为升序。那么我们可以将输入的序列按升序排列，接着对定义好的**完全二叉树结构**进行中序遍历，访问其中第i个结点时，就将排好序的输入序列的第i个值填入。那么遍历结束后，完全二叉树结构的每个结点都有了数值，此时在对其中序遍历，一定是升序序列。

​		由于静态数组就是按照层序存结点的，因此只需将数组元素按顺序输出即为层序遍历序列。

#### 思路二

​		以上思路比较巧妙，对这些性质不熟悉不易想到。这里针对第二个约束，还有一种处理：

​		借用堆调整的思想，遍历输入序列，将每个元素插入当前数组的末尾，这样可保证完全二叉树的约束。然后不断调整该元素的位置，直至为二叉排序树。假设当前结点为x，总结点个数为N，以下是调整步骤：

1. 若x为奇数，即为x/2的左孩子，此时若T[x]>=T[x/2]，交换二者，并更新x为x/2。重复该操作直至x满足条件或达到根结点。若仅达到根结点，进入步骤2。
2. 若x为偶数，即为2x的右孩子，此时若T[x]>=T[2x]，交换二者，并更新x为2x。重复该操作直至x满足条件或超过总结点数N。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-12 23:32:22
 * @LastEditTime: 2019-08-12 23:42:13
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
int CBST[maxn], in[maxn]; //完全二叉排序树、中序遍历序列
int N, idx = 0; //结点数
// 中序遍历将in的值依次填入相应结点
void inorderTravesal(int root) {
    if(root > N) return;
    inorderTravesal(2 * root);
    CBST[root] = in[idx ++]; //填入相应值
    inorderTravesal(2 * root + 1);
}
int main() {
    scanf("%d", &N);
    for(int i = 0; i < N; i ++) {
        scanf("%d", &in[i]);
    }
    sort(in, in + N); //BST中序必为升序
    inorderTravesal(1);
    // 数组存放顺序即为层序遍历，从1开始存
    for(int i = 1; i <= N; i ++) {
        printf("%d%s", CBST[i], i == N ? "\n" : " ");
    }
    return 0;
}
```



### [A1099 Build A Binary Search Tree](https://pintia.cn/problem-sets/994805342720868352/problems/994805367987355648)

#### 思路

​		给定二叉树的结构，将给定的N个整数填入二叉树的结点中，使得二叉树成为一棵BST。最后输出其层序遍历序列。

​		借鉴**A1064**对二叉排序树约束的处理：BST的中序遍历序列是递增的，因此仅需对输入的序列从小到大排序，然后对给定二叉树进行中序遍历，将排序后的序列按中序遍历的顺序依次填入二叉树结点中，即可形成BST。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-13 13:55:20
 * @LastEditTime: 2019-08-13 14:21:22
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
struct STNode {
    int data;
    int lchild, rchild;
    STNode() {
        lchild = -1;
        rchild = -1;
    }
}STree[maxn];
int N, number[maxn], idx = 0; //结点总数、输入权值序列、升序排列后权值序列下标、
vector<int> layer; //层序遍历序列，便于输出
void inorderTraversal(int root) {
    if(root == -1) return;
    inorderTraversal(STree[root].lchild);
    STree[root].data = number[idx++]; //中序遍历填入
    inorderTraversal(STree[root].rchild);
}
void layerTraversal(int root) {
    queue<int> q;
    q.push(root);
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        layer.push_back(STree[now].data);
        if(STree[now].lchild != -1) q.push(STree[now].lchild);
        if(STree[now].rchild != -1) q.push(STree[now].rchild);
    }
}
void showResult() {
    for(int i = 0; i < N; i ++) {
        printf("%d%s", layer[i], i == N - 1 ? "\n" : " ");
    }
}
void readData() {
    scanf("%d", &N);
    int l, r;
    for(int i = 0; i < N; i ++) {
        scanf("%d %d", &l, &r);
        STree[i].lchild = l;
        STree[i].rchild = r;
    }
    for(int i = 0; i < N; i ++) {
        scanf("%d", &number[i]);
    }
}
int main() {
    readData();
    sort(number, number + N); //升序排序，BST中序遍历为升序
    inorderTraversal(0);
    layerTraversal(0);
    showResult();
    return 0;
}
```



### 小结

​		BST的重要性质：中序遍历序列是递增的。后面两题都涉及到了该性质的应用。其中**BST的构建**，主要有两种形式：

+ **给定结点插入顺序**：如**A1043**，有趣的是，按任意序列插入都可以构建一棵BST，但是只有BST的前序序列可还原BST，中序后序均不行。（$BST<=>前序序列$）
+ **已知二叉树结构，所有结点的数值**：例如**A1064**可利用完全二叉树特性，用N+1个元素的静态数组存放二叉树，它的结构是确定的。再如**A1099**，题目直接给定结点间关系，也是确定了二叉树结构。再利用BST中序为有序性质，将所有的的数字从小到大排序，中序遍历已知的二叉树结构时依次填入数值即可。



## 平衡二叉树（AVL）

### [A1066 Root of AVL Tree](https://pintia.cn/problem-sets/994805342720868352/problems/994805404939173888)

#### 思路

​		给出N个正整数，将他们依次插入一棵初始为空的AVL树上，求插入后的根结点的值。考察AVL的插入操作。

​		AVL是在BST基础上增加了平衡的条件，即任何一个结点左右子树高度差绝对值不超过1。

（1）空树必定为平衡二叉树。

（2）若当前T为AVL，插入一个结点后，如何判断T是否依旧为AVL？

（3）若不是AVL，如何调整使其成为AVL？

​		树的问题基本都能用递归思想解决，这里也不例外，以上3条就是一个递归插入建立AVL的思路：从空树开始，插入一个结点，若此时树不是AVL，将其调整为AVL，再继续插入。因此插入的关键就在于如何解决第2,3个问题。

##### 如何判断一棵BST为AVL？

​		从其定义出发，AVL的每个结点都平衡，即左右子树高度差绝对值不超过1。那么我们就可以通过记录每个结点的高度，计算左右子树高度差值即可求出平衡因子。因此，在树结点结构体中添加高度属性。

```c++
struct TNode {
    int data, height;
    TNode *lchild, *rchild;
    TNode() { // 默认构造函数初始化
        height = 0;
        lchild = NULL;
        rchild = NULL;
    }
};
```

​		为了便于获取结点的高度，为后续编程提供便利，定义以下接口：

```c++
int getHeight(TNode* root) {
    return root == NULL ? 0 : root->height;
}
```

​		当前结点高度为左右子树较大者高度加1，便于每次**插入结点**和**调整结构**后能更新相应点的高度。

```c++
void updateHeight(TNode* root) {
    root->height = max(getHeight(root->lchild), getHeight(root->rchild)) + 1;
}
```

​		规定当前结点的平衡因子为左子树高度减右子树高度。

```c++
int getBalanceFactor(TNode* root) {
    return getHeight(root->lchild) - getHeight(root->rchild);
}
```

​		至此，在每次对树进行插入或调整操作室，都能及时更新每个结点的高度，并轻松获取其平衡因子。直接用于AVL的判断。

##### 如何调整？

​		因为插入一个结点而导致AVL不再平衡，可通过旋转操作来调整。其实只要掌握一个右旋就掌握了所有调整的核心。因为右旋与左旋是对称互逆的操作，交换右旋中的左右子树即可得到左旋。对于四种树型，也仅仅是来调用相应的左旋和右旋完成调整，因此，关键要会右旋/左旋。

**(一) 右/左旋**

​		假设当前结点为root，root左子树为tmp，**右旋**分4步走：

1. 将root左子树指向tmp的右子树。
2. 将tmp的右子树指向root。
3. 形象来说，此时tmp被转上去，root被转下来，因此先更新root高度，再更新tmp高度。
4. 将tmp作为新的root

```c++
// 右旋：改变结构，需引用&
void R(TNode* &root) {
    TNode* tmp = root->lchild;
    root->lchild = tmp->rchild;
    tmp->rchild = root;
    updateHeight(root); //更新根的高度，必须先更新根，因为他在下方
    updateHeight(tmp);  //更新被交换上去的点的高度
    root = tmp; //新的根结点
}
```

​		利用右旋与左旋的高度对称性，交换右旋中左右子树即可获得**左旋**操作：

```c++
void L(TNode* &root) {
    TNode* tmp = root->rchild;
    root->rchild = tmp->lchild;
    tmp->lchild = root;
    updateHeight(root);
    updateHeight(tmp);
    root = tmp;
}
```

**（二）树型判断**

​		四种树型关键在于掌握RR。RL必须先利用右旋调整为RR，然后再用左旋调整RR。得到RR和RL后，利用对称性，即可得到LL和LR。因此，掌握RR的判断方法就可以轻易推出其余情况。

​		RR也是利用平衡因子来判断，假设当前结点为root，那么root的平衡因子为-2且root右子树的平衡因子为-1，左旋即可。RL对应的平衡因子为-2，1，需先右旋变成RR，再左旋。将RR和RL对应的平衡因子取相反数并互换R，L，就得到了LL和LR的判定条件和调整方法。具体见下表：

| 树型 | 判定条件（BF平衡因子）           | 调整方法(L左旋，R右旋)   |
| ---- | -------------------------------- | ------------------------ |
| RR   | BF(root)=-2，BF(root->rchild)=-1 | L(root)                  |
| RL   | BF(root)=-2，BF(root->rchild)=1  | R(root->rchild)，L(root) |
| LL   | BF(root)=2，BF(root->lchild)=1   | R(root)                  |
| LR   | BF(root)=2，BF(root->lchild)=-1  | L(root->lchild)，R(root) |

​		归根到底，掌握了右旋就等于掌握了核心。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-13 15:12:12
 * @LastEditTime: 2019-08-13 16:42:19
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct TNode {
    int data, height;
    TNode *lchild, *rchild;
    TNode() {
        height = 0;
        lchild = NULL;
        rchild = NULL;
    }
};
// 获取当前结点高度，需考虑空
int getHeight(TNode* root) {
    return root == NULL ? 0 : root->height;
}
// 更新当前结点高度，左右子树较高者加1
void updateHeight(TNode* root) {
    root->height = max(getHeight(root->lchild), getHeight(root->rchild)) + 1;
}
// 获取平衡因子：左-右
int getBalanceFactor(TNode* root) {
    return getHeight(root->lchild) - getHeight(root->rchild);
}
// 右旋：改变结构，需引用&
void R(TNode* &root) {
    TNode* tmp = root->lchild;
    root->lchild = tmp->rchild;
    tmp->rchild = root;
    updateHeight(root); //更新根的高度，必须先更新根，因为他在下方
    updateHeight(tmp);  //更新被交换上去的点的高度
    root = tmp; //新的根结点
}
// 左旋：与右旋互逆，交换左右子树即可
void L(TNode* &root) {
    TNode* tmp = root->rchild;
    root->rchild = tmp->lchild;
    tmp->lchild = root;
    updateHeight(root);
    updateHeight(tmp);
    root = tmp;
}
// 封装结点平衡判断及其旋转操作
void adjust(TNode* &root) {
    updateHeight(root); //更新当前结点高度
    if(getBalanceFactor(root) == 2) { // 离插入点最近的不平衡点
        if(getBalanceFactor(root->lchild) == 1) { // LL
            R(root);
        }
        else { // LR
            L(root->lchild);
            R(root);
        }
    }
    else if(getBalanceFactor(root) == -2) { // 该分支必须明确指出，否则平衡因子为1时也会调整
        if(getBalanceFactor(root->rchild) == -1) { // RR
            L(root);
        }
        else { // RL
            R(root->rchild);
            L(root);
        }
    }
}
// 递归插入
void insert(TNode* &root, int x) {
    if(root == NULL) {
        root = new TNode;
        root->data = x;
        updateHeight(root); //更新插入的点高度，为后续点高度准备
        return;
    }
    if(x < root->data) insert(root->lchild, x);// 往左子树递归插入
    else insert(root->rchild, x); // 右子树递归插入
    adjust(root); // 判断是否失衡，若是则旋转调整
}
// 读入数据时插入创建AVL
void createAVL(TNode* &root) {
    int n;
    scanf("%d", &n);
    int t;
    for(int i = 0; i < n; i ++) {
        scanf("%d", &t);
        insert(root, t);
    }
}
int main() {
    TNode* root = NULL;
    createAVL(root);
    printf("%d\n", root->data);
    return 0;
}
```



## 并查集

### [A1107 Social Clusters](https://pintia.cn/problem-sets/994805342720868352/problems/994805361586847744)

#### 思路

​		只要两个人有一个相同爱好，则属于一个社交圈，并且具有传递性，即A和B属于一个圈子，B和C属于一个圈子，那么A和C属于一个圈子。

​		步骤 1：开辟一个int型数组hobby，hobby[i]记录任意一个喜欢第i号活动的人的编号，因此father[hobby[i]]就是这个人所在社交圈的根节点。对于每一个人i，读入它的每一个喜欢的活动j时，合并i和hobby[j]即可。
​		步骤 2：开辟一个整型数组cnt，初值为0，cnt[x]用来记录以x为根结点的社交网络有多少人，只需遍历每一个人，令cnt[findRoot(i)]加1即可。最后统计非零的元素，按非升序输出。

#### 注意点

+ 最后计数时不可用`cnt[father[i]]`，因为并非每个结点都会被遍历压缩到，所以需要每次都调用查找函数，以此来找到真正的根结点。
+ 并查集的初始化、查找、合并三大步骤中，初始化别忘，查找可以不压缩路径。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-13 19:16:26
 * @LastEditTime: 2019-08-13 20:00:57
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
int hobby[maxn], father[maxn], cnt[maxn] = {0};
int N; // 总人数
void init() {
    fill(hobby, hobby + maxn, -1);
    for(int i = 1; i < maxn; i ++) father[i] = i;
}
// 查
int findRoot(int x) {
    int a = x; // 保存起点
    while(x != father[x]) x = father[x]; //找到根结点
    // 路径压缩
    while(a != father[a]) {
        int t = a; // 保存孩子
        a = father[a]; // 回溯父亲
        father[t] = x; // 父亲改为root
    }
    return x;
}
// 并
void unionSet(int a, int b) {
    int fa = findRoot(a);
    int fb = findRoot(b);
    if(fa != fb) {
        father[fa] = fb;
    }
}
void showResult() {
    vector<int> ans;
    for(int i = 1; i <= N; i ++) cnt[findRoot(i)] ++; // 计算每个根结点出现次数，保证每个点都被查找，压缩路径
    for(int i = 1; i <= N; i ++) {
        if(cnt[i] != 0) ans.push_back(cnt[i]); // 将每个根结点出现次数存到ans，便于排序，统计个数
    }
    sort(ans.begin(), ans.end(), [](int a, int b){return a > b;}); //非降序，lamda语法
    int len = ans.size();
    printf("%d\n", len);
    for(int i = 0; i < len; i ++) printf("%d%s", ans[i], i == len - 1 ? "\n" : " ");
}
int main() {
    init();
    scanf("%d", &N);
    int n, t;
    // 第i个人
    for(int i = 1; i <= N; i ++) {
        scanf("%d:", &n);
        for(int j = 0; j < n; j ++) { // 兴趣
            scanf("%d", &t);
            if(hobby[t] == -1) hobby[t] = i;
            else unionSet(hobby[t], i);
        }
    }
    showResult();
    return 0;
}
```

## 堆

### [A1098 Insertion or Heap Sort](https://pintia.cn/problem-sets/994805342720868352/problems/994805368847187968)

#### 思路

​		根据给定初始序列和中间序列，判断使用了哪种排序，并且输出相应排序方法的下一次排序结果。与**A1089**一样，模拟插入排序和堆排序即可。这里详细解释堆排序。
​		堆排序关键在于使用**向下调整法**建立起堆，接着反复交换首尾元素，再使用向下调整法。因此，向下调整法为核心。其思路为：选出当前结点root左右孩子较大者x，若当前结点root小于x，交换二者，继续以上操作，直至满足条件或无孩子。(注意区间)

```c++
// 向下调整,区间：[low, high]
void downAdjust(int low, int high) {
    int i = low, j = 2 * i;
    while(j <= high) { // 孩子存在，注意别写成j <= N，建堆成立，但排序调整就是错的，边界改了
        if(j + 1 <= high && heap[j + 1] > heap[j]) j = j + 1; //左右取大者
        if(heap[i] < heap[j]) {
            swap(heap[i], heap[j]);
            i = j;
            j = 2 * i;
        }
        else break;
    }
}
```

#### 注意点

+ downAdjust中右边界应该为high，而不是写死为N，这样堆排序调整时会出错。

#### C++

```c++
/*
 * @Author: wuyangjun
 * @Date: 2019-08-13 23:42:36
 * @LastEditTime: 2019-08-14 00:41:34
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
vector<int> origin, test, insert, heap; 
int N;
void print(vector<int> &a) {
    for(int i = 1; i <= a.size() - 1; i ++) {
        printf("%d%s", a[i], i == a.size() - 1 ? "\n" : " ");
    }
}
// 第一个均不用
void init() {
    origin.push_back(0);
    test.push_back(0);
    insert.push_back(0);
    heap.push_back(0);
}
// 向下调整,区间：[low, high]
void downAdjust(int low, int high) {
    int i = low, j = 2 * i;
    while(j <= high) { // 孩子存在，注意别写成j <= N，建堆成立，但排序调整就是错的，边界改了
        if(j + 1 <= high && heap[j + 1] > heap[j]) j = j + 1; //左右取大者
        if(heap[i] < heap[j]) {
            swap(heap[i], heap[j]);
            i = j;
            j = 2 * i;
        }
        else break;
    }
}
// 构造大顶堆
void makeHeap() {
    for(int i = N / 2; i >= 1; i --) { // 从非叶子结点开始调整
        downAdjust(i, N);
    }
}
bool heapSort() {
    makeHeap();
    bool ret = false;
    for(int i = N; i > 1; i --) {
        swap(heap[1], heap[i]);
        downAdjust(1, i - 1);
        if(test == heap) {
            ret = true;
            continue;
        }
        if(ret) break;
    }
    return ret;
}
// 插入排序模拟
bool insertSort() {
    bool ret = false;
    for(int i = 1; i <= N; i ++) {
        int j = i;
        while(j > 1 && insert[j] < insert[j - 1]) {
            swap(insert[j], insert[j - 1]);
            j --;
        }
        if(test == insert) {
            ret = true;
            continue;
        }
        if(ret) break;
    }
    return ret;
}
void readData() {
    scanf("%d", &N);
    int t;
    for(int i = 0; i < N; i ++) {
        scanf("%d", &t);
        origin.push_back(t);
    }
    for(int i = 0; i < N; i ++) {
        scanf("%d", &t);
        test.push_back(t);
    }
    insert = origin;
    heap = origin;
}
int main() {
    init();
    readData();
    if(insertSort()) {
        printf("Insertion Sort\n");
        print(insert);
    }
    else {
        heapSort();
        printf("Heap Sort\n");
        print(heap);
    }
    return 0;
}
```



## 总结

[思维导图总结](https://mubu.com/doc/mu_iaAA9bo)

​		树是连通无回路的图，也是回溯法DFS，BFS的实现根基。树的难点在于**如何构建**，因为遍历方式较为简单。同时树的种类繁多，需要把握其内在联系，从普通二叉树开始，增加大小的约束变为BST，对BST增加平衡约束，成为AVL；对普通二叉树增加结构约束：完全二叉树即为堆。借用树的思想，使用并查集来维护集合，可求出集合个数和每个集合的大小。哈夫曼树为最优树，即WPL最小的二叉树，对其使用前缀编码，就成了哈夫曼编码。
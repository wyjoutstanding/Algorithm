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
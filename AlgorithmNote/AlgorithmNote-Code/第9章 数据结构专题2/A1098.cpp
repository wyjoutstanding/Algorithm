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
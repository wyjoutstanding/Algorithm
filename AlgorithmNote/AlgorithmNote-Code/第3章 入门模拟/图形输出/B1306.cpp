#include <bits/stdc++.h>
using namespace std;
int main() {
    int col, rank;  //column, rank
    char ch;    //input's character
    scanf("%d %c", &col, &ch);
    rank = (int)((float)col / 2 + 0.5); //四舍五入
    for(int i = 0; i < rank; i++) {
        for(int j = 0; j < col; j++) {
            if(i == 0 || i == rank - 1) printf("%c", ch);   //头尾两行
            else {//中间
                if(j == 0 || j == col - 1)  printf("%c", ch);   //头尾两列
                else printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
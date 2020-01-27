#include<bits/stdc++.h>
using namespace std;
int main() {
    srand(time(0));
    for (int j = 0; j < 0x3fff; j ++) {
        for (int i = 0; i < 6; i ++) {
            printf("%d %d\n", rand() % 10000, rand() % 10000);
        }
    }
    return 0;
}
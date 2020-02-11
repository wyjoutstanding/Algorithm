#include<bits/stdc++.h>
using namespace std;
int main() {
    set<int> _set{1,2,4,5,6};
    for (auto p : _set) cout <<p <<" ";
    cout <<endl;
    auto tp = _set;
    for (auto p : tp) {
        cout <<"  p:" <<p;
        if (p % 2 == 0) _set.erase(p);
    }cout<<endl;
    for (auto p : _set) cout <<p <<" ";
    cout <<endl;
    // printf("%d\n", n);
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
int a, b;
map<set<int>, int> box;
int main() {
    while(cin >>a >> b) {
        bool isBox = false;
        box.clear(); 
        for (int i = 0; i < 6; i ++) {
            if (i != 0) cin >>a >>b;
            if (box.find({a,b}) == box.end()) {
                box.insert({{a,b},1});
            }
            else box[{a,b}] ++;
        }
        // for (auto p : box) {
        //     printf("set:");
        //     for (auto k : p.first) {
        //         printf("%d ", k);
        //     }
        //     printf(" cnt:%d\n", p.second);
        // }
        if (box.size() <=3) {
            if (box.size() == 1) { // 正方形，边长仅一种
                if (box.begin()->first.size() == 1) isBox = true;
            }
            else if (box.size() == 2) {
                auto it = box.begin();
                auto p1 = it, p2 = ++it;
                if (p1->second != 2) swap(p1, p2);
                if (p1->second == 2 && p2->second == 4 && p1->first.size() == 1 && p2->first.find(*p1->first.begin()) != p2->first.end()) isBox = true;
            }
            else {
                vector<int> a;
                for (auto p : box) {
                    if (p.second != 2 || p.first.size() != 2) break;
                    for (auto k : p.first) a.push_back(k);
                }
                if (a.size() == 6) {
                    for (int i = 0; i < 2; i ++) {
                        for (int j = 0; j < 2; j ++) {
                            if (a[i] == a[j]) {
                                if ((a[i+1%2] == a[4] || a[i+1%2] == a[5])
                                && (a[j+1%2] == a[4] || a[j+1%2] == a[5])) {
                                    isBox = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        printf("%s\n", isBox ? "POSSIBLE" : "IMPOSSIBLE");
    }
    return 0;
}
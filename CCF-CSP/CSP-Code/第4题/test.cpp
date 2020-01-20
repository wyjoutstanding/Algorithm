#include<bits/stdc++.h>
using namespace std;
int main() {
  map<int, int> mp;
  mp.insert({1,10});
  for (auto _mp : mp) {
    printf("%d %d\n", _mp.first, _mp.second);
  }
  return 0;
}
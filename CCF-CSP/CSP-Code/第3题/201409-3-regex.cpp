/*
 * @Author: wuyangjun
 * @Date: 2019-09-07 22:03:51
 * @LastEditTime: 2019-09-07 22:56:28
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    string dist, tmp, s;
    int flag, n;
    cin >>dist >>flag >>n;
    while(n --) {
        cin >>s;
        // if(flag == 0 && regex_match(s, regex("[[:alpha:]]*"+dist+"[[:alpha:]]*", regex::icase))) puts(s.c_str());
        // if(flag == 1 && regex_match(s, regex("[[:alpha:]]*"+dist+"[[:alpha:]]*"))) puts(s.c_str());
        // if(flag == 0 && regex_search(s, regex("[[:alpha:]]*"+dist+"[[:alpha:]]*", regex::icase))) puts(s.c_str());
        // if(flag == 1 && regex_search(s, regex("[[:alpha:]]*"+dist+"[[:alpha:]]*"))) puts(s.c_str());
        if(flag == 0 && regex_search(s, regex(dist, regex::icase))) puts(s.c_str());
        if(flag == 1 && regex_search(s, regex(dist))) puts(s.c_str());
        
    }
    return 0;
}
// [a-zA-Z]*Hello[a-zA-Z]*
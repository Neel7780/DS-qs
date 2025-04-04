#include <bits/stdc++.h>
using namespace std;
#define __GodLikeNeel__ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

int firstUniqChar(string s) {
    unordered_map<char, int> charCount; 

    for (char c : s) {
        charCount[c]++;
    }
    
    for (int i = 0; i < s.size(); i++) {
        if (charCount[s[i]] == 1) {
            return i; 
        }
    }

    return -1; 
}

int main() {
    __GodLikeNeel__
    string s = "leetcode";

    return 0;
}
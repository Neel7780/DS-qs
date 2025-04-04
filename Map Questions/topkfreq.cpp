#include <bits/stdc++.h>
using namespace std;
#define __GodLikeNeel__ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

int topKFrequent(vector<int>& nums, int k) {
    int n = nums.size();
        unordered_map<int, int> m;
        for(int i =0; i<nums.size(); i++){
            m[nums[i]]++;
        }
        vector<int> ans;
        vector<vector<int>> arr(n + 1);
        for (auto [a, b] : m) arr[b].push_back(a);
        for (int i = n; i > 0; i--) {
            for (int &x : arr[i]) {
                if (ans.size() == k) return ans;
                ans.push_back(x);
            }
        }
        return ans;
}

int main() {
    __GodLikeNeel__
    vector<int> nums = {1, 1, 1, 2, 2, 3};
    int k = 2; // Number of top frequent elements to return
    vector<int> result = topKFrequent(nums, k);
    cout << "Top " << k << " frequent elements: ";
    return 0;
}
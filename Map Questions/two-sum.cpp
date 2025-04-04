#include <bits/stdc++.h>
using namespace std;
#define __GodLikeNeel__ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

vector<int> twoSum(vector<int>& nums, int target) {
    vector<pair<int, int>> indexedNums; 
    
    for (int i = 0; i < nums.size(); i++) {
        indexedNums.push_back({nums[i], i});
    }
    sort(indexedNums.begin(), indexedNums.end());

    int left = 0, right = nums.size() - 1;
    
    while (left < right) {
        int sum = indexedNums[left].first + indexedNums[right].first;
            
        if (sum == target) {
            return {indexedNums[left].second, indexedNums[right].second}; 
        }
        else if (sum < target) {
            left++; 
        }
        else {
            right--; 
        }
    }
        
    return {}; 
}

// 2-pointer approach
// Time Complexity: O(nlogn) for sorting + O(n) for 2-pointer traversal = O(nlogn)
// Space Complexity: O(n) for storing indexed numbers
// 2-pointer approach is used after sorting the array to find the two numbers that add up to the target.

int main() {
    __GodLikeNeel__
    vector<int> nums = {3,2,4};
    int target = 6;
    vector<int> result = twoSum(nums, target);
    for(int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    return 0;
}
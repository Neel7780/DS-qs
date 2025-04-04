#include <bits/stdc++.h>
using namespace std;
#define __GodLikeNeel__ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

int longestConsecutive(vector<int>& nums) {
    unordered_set<int> numSet(nums.begin(), nums.end()); // Insert all numbers into a set for O(1) lookups
    int longestStreak = 0;

    for (int num : numSet) {
        if (numSet.find(num - 1) == numSet.end()) { // Check if it's the start of a sequence
            int currentNum = num; // Start counting from this number
            int currentStreak = 1; // Initialize streak length

            while (numSet.find(currentNum + 1) != numSet.end()) { // Check for the next number in the sequence
                currentNum++;
                currentStreak++;
            }

            longestStreak = max(longestStreak, currentStreak); // Update longest streak if current is longer
        }
    }

    return longestStreak;
}

int main() {
    __GodLikeNeel__
    vector<int> nums = {100, 4, 200, 1, 3, 2};
    int result = longestConsecutive(nums);
    cout << "Longest consecutive sequence length: " << result << endl;
    
    return 0;
}
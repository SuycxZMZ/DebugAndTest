//
// Created by yuan su on 24-6-30.
//
#include <vector>
#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>

using namespace std;

// 1: 01背包求最多背多少
// 2: 01背包求背一定容量多少种方案
class Solution {
public:
    // 1 分割等和子集
    bool canPartition(vector<int>& nums) {
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) return false;
        sum /= 2;
        vector<int> f(sum + 1, 0);

        for (int i = 0; i < nums.size(); ++i) {
            for (int j = sum; j >= nums[i]; --j) {
                f[j] = max(f[j], f[j - nums[i]] + nums[i]);
            }
        }
        if (f[sum] == sum) return true;
        return false;
    }
};

int main() {


    return 0;
}
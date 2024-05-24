//
// Created by yuan su on 24-5-9.
//
#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    /**
     * @brief 三数之和，返回相加等于0的三元组
     *
     * */
    std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
        int n = nums.size();
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> ans;
        for (int i = 0; i < n - 2; ++i) {
            int x = nums[i];
            if (i > 0 && x == nums[i - 1]) continue;
            // 与最大的相加仍小于0，要继续往后找，跳过当前i
            if (x + nums[n - 2] + nums[n - 1] < 0) continue;
            // 与最小的相加 > 0 ,则后面的i仍会大于0, 直接跳出
            if (x + nums[i + 1] + nums[i + 2] > 0) break;

            int j = i + 1, k = n - 1;
            while (j < k) {
                int s = x + nums[j] + nums[k];
                if (s > 0) --k;
                else if (s < 0) ++j;
                else {
                    ans.push_back({x, nums[j], nums[k]});
                    for (++j; j < k && nums[j] == nums[j - 1]; ++j);
                    for (--k; j < k && nums[k] == nums[k + 1]; --k);
                }
            }
        }
        return ans;
    }

    /**
     * @brief 四数之和，相加等于target
     *
     * */
    std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        std::vector<std::vector<int>> ans;
        for (int a = 0; a < n - 3; ++a) {
            long long x = nums[a];
            if (a > 0 && x == nums[a - 1]) continue;
            if (x + nums[a + 1] + nums[a + 2] + nums[a + 3] > target) break;
            if (x + nums[n - 3] + nums[n - 2] + nums[n - 1] < target) continue;
            for (int b = a + 1; b < n - 2; ++b) {
                long long y = nums[b];
                if (b > a + 1 && nums[b] == nums[b - 1]) continue;
                if (x + y + nums[b + 1] + nums[b + 2] > target) break;
                if (x + y + nums[n - 2] + nums[n - 1] < target) continue;

                int c = b + 1, d = n - 1;
                while (c < d) {
                    long long s = x + y + nums[c] + nums[d];
                    if (s > target) --d;
                    else if (s < target) ++c;
                    else {
                        ans.push_back({(int)x, (int)y, nums[c], nums[d]});
                        for (++c; c < d && nums[c] == nums[c - 1]; ++c);
                        for (--d; c < d && nums[d] == nums[d + 1]; --d);
                    }
                }
            }
        }
        return ans;
    }
};


int main() {
    std::vector<int> nums = {-1,0,1,2,-1,-4};
    Solution s;
    std::vector<std::vector<int>> result = s.threeSum(nums);
    for (auto &vec : result) {
        for (int &i : vec) std::cout << i << " ";
        std::cout << std::endl;
    }

    std::cout << "----------------" << std::endl;
    std::vector<int> nums2 = {1,0,-1,0,-2,2};
    std::vector<std::vector<int>> result2 = s.fourSum(nums2, 0);
    for (auto &vec : result2) {
        for (int &i : vec) std::cout << i << " ";
        std::cout << std::endl;
    }
    return  0;
}
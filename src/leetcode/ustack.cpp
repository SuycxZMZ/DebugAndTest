#include <iostream>
#include <stack>
#include <vector>
#include <deque>
// #include <math.h>
#include <algorithm>

/**
 * @SuycxZMZ
 * @brief 单调栈
*/
class Solution {

public:
    /**
     * @brief 每日温度,返回下一个更高温度出现在几天后
     *        栈顶一定是最低的
    */
    std::vector<int> dailyTemperatures(std::vector<int>& t) {
        std::stack<int> st;
        int n = t.size();
        std::vector<int> res(n, -1);
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && t[st.top()] < t[i]) {
                res[st.top()] = i - st.top();
                st.pop();
            }
            st.push(i);
        }
        return res;
    }
    /**
     * @brief 下一个更大元素, 循环数组
    */
    std::vector<int> nextGreaterElements(std::vector<int>& nums) {
        int n = nums.size();
        int MOD = n;
        std::stack<int> st;
        std::vector<int> res(n, -1);
        for (int i = 0; i < n * 2; ++i) {
            while (!st.empty() && nums[st.top() % MOD] < nums[i % MOD]) {
                res[st.top() % MOD] = nums[i % MOD];
                st.pop();
            }
            st.push(i);
        }
        return res;
    }

    /**
     * @brief 接雨水，单调栈，遇到高的，找上一个高的，形成凹槽
    */
    int trap1(std::vector<int>& h) {
        int n = h.size();
        std::stack<int> st;
        int res = 0;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && h[st.top()] <= h[i]) {
                int mididx = st.top();
                st.pop();
                // 没有上一个
                if (st.empty()) {
                    break;
                }
                int leftidx = st.top();
                res += ((std::min(h[leftidx], h[i]) - h[mididx]) * (i - leftidx - 1));
            }

            st.push(i);
        }
        return res;
    }

    /**
     * @brief 接雨水，前后缀做法
    */
    int trap2(std::vector<int>& h) {
        int n = h.size();
        // 0 --> i 的最高
        std::vector<int> lmax(n);
        // i --> n-1 的最高
        std::vector<int> rmax(n);

        int tmp = 0;
        for (int i = 0; i < n; ++i) {
            lmax[i] = std::max(h[i], tmp);
            tmp = lmax[i];
        }

        tmp = 0;
        for (int i = n - 1; i >= 0; --i) {
            rmax[i] = std::max(h[i], tmp);
            tmp = rmax[i];
        }

        int res = 0;
        for (int i = 0; i < n; ++i) {
            // 累加每个桶里装多少水
            res += std::min(lmax[i], rmax[i]) - h[i];
        }
        return res;
    }

    /**
     * @brief 柱状图中最大的矩形，单调栈
    */
    int largestRectangleArea(std::vector<int>& h) {
        int n = h.size();

        // lmin[i] 表示 i 左侧第一个小于 h[i] 的下标
        std::vector<int> lmin(n, -1);
        // rmin[i] 表示 i 右侧第一个小于 h[i] 的下标
        std::vector<int> rmin(n, n);
        std::stack<int> st;

        for (int i = 0; i < n; ++i) {
            while (!st.empty() && h[i] <= h[st.top()]) {
                st.pop();
            }
            if (!st.empty()) {
                lmin[i] = st.top();
            }
            st.push(i);
        }

        st = std::stack<int>();
        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty() && h[i] <= h[st.top()]) {
                st.pop();
            }
            if (!st.empty()) {
                rmin[i] = st.top();
            }
            st.push(i);
        }

        int res = 0;
        for (int i = 0; i < n; ++i) {
            res = std::max(res, (rmin[i] - lmin[i] - 1) * h[i]);
        }
        return res;
    }
};


int main() {
    


    return 0;
}
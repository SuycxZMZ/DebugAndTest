#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution 
{
public:
    // ******************* 美丽塔 ******************* //
    long long maximumSumOfHeights_1(vector<int>& a) 
    {
        // 左侧递增段 a[0] --> a[i] 元素最大和记到 pre[i] 中
        // 右侧递减段 a[i] --> a[n - 1] 元素最大和记到 suf[i] 中
        // 答案是 max(pre[i] + suf[i + 1])

        // pre
        int n = a.size();
        vector<int> pre(n+1);
        stack<int> st;
        st.push(-1);
        long long sum = 0;
        for (int i = 0; i < n - 1; ++i)
        {
            int x = a[i];
            while (st.size() > 1 && x <= a[st.top()])
            {
                int j = st.top(); st.pop();
                sum -= (long long)a[j] * (j - st.top());
            }
            sum += (long long)x * (i - st.top());
            pre[i] = sum;
            st.push(i);
        }
        // for (auto & it : pre) cout << it << " ";
        // cout << endl;
        // 计算 suf 与结果
        sum = 0;
        long long ans = pre[n - 1];
        st = stack<int>();
        st.push(n);
        for (int i = n - 1; i >= 0; --i)
        {
            int x = a[i];
            while (st.size() > 1 && x < a[st.top()])
            {
                int j = st.top(); st.pop();
                sum -= (long long)a[j] * (st.top() - j);
            }
            sum += (long long)x * (st.top() - i);
            if (i > 0) ans = max(ans, sum + pre[i - 1]);
            else ans = max(ans, sum);
            st.push(i);
        }
        return ans;
    }

    vector<int> resultArray(vector<int>& nums) 
    {
        vector<int> ans;
        vector<int> arr2;
        ans.emplace_back(nums[0]);
        arr2.emplace_back(nums[1]);
        for (int i = 2; i < nums.size(); ++i)
        {
            if (ans.back() > arr2.back()) ans.emplace_back(nums[i]);
            else arr2.emplace_back(nums[i]);
        }
        for (auto &it : arr2)
        {
            ans.emplace_back(it);
        }
        return ans;
    }

    vector<vector<int>> calculatePrefixSum(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        // 创建一个与原始矩阵相同大小的二维矩阵，用于存储前缀和
        vector<vector<int>> prefixSum(rows, vector<int>(cols, 0));

        // 计算第一行的前缀和
        prefixSum[0][0] = grid[0][0];
        for (int j = 1; j < cols; ++j) {
            prefixSum[0][j] = prefixSum[0][j - 1] + grid[0][j];
        }

        // 计算第一列的前缀和
        for (int i = 1; i < rows; ++i) {
            prefixSum[i][0] = prefixSum[i - 1][0] + grid[i][0];
        }

        // 计算其他位置的前缀和
        for (int i = 1; i < rows; ++i) {
            for (int j = 1; j < cols; ++j) {
                prefixSum[i][j] = grid[i][j] + prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1];
            }
        }

        return prefixSum;
    }
    int countSubmatrices(vector<vector<int>>& grid, int k) 
    {
        int rows = grid.size();
        int cols = grid[0].size();

        // 创建一个与原始矩阵相同大小的二维矩阵，用于存储前缀和
        vector<vector<int>> prefixSum(rows, vector<int>(cols, 0));

        // 计算第一行的前缀和
        prefixSum[0][0] = grid[0][0];
        for (int j = 1; j < cols; ++j) {
            prefixSum[0][j] = prefixSum[0][j - 1] + grid[0][j];
        }

        // 计算第一列的前缀和
        for (int i = 1; i < rows; ++i) {
            prefixSum[i][0] = prefixSum[i - 1][0] + grid[i][0];
        }
        int ans = 0;
        // 计算其他位置的前缀和
        for (int i = 1; i < rows; ++i) {
            for (int j = 1; j < cols; ++j) {
                prefixSum[i][j] = grid[i][j] + prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1];
                
            }
        }  
        for (auto & line : prefixSum)
        {
            for (auto & it : line)
            {
                if (it <= k) ans++;
            }
        }
        return ans;      
    }

    bool isY(int n, int i, int j)
    {
        int center = n/2;
        if ((i <= center && i == j) || (i <= center && n - j - 1 == i)) return true;
        else if (i >= center && j == center) return true;
        return false;
    }
    int minimumOperationsToWriteY(vector<vector<int>>& grid) 
    {
        vector<int> Ycount(3, 0);
        vector<int> Ncount(3, 0);
        int n = grid.size();
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (isY(n, i, j)) Ycount[grid[i][j]]++;
                else Ncount[grid[i][j]]++;
            }
        }
        // for (int i : Ycount) cout << i << " ";
        // cout << endl;
        // for (int j : Ncount) cout << j << " ";
        // cout << endl;
        // auto it1 = max_element(Ycount.begin(), Ycount.end());
        // int maxy_idx = it1 - Ycount.begin();
        // auto it2 = max_element(Ncount.begin(), Ncount.end());
        // int maxn_idx = it2 - Ncount.begin();
        int minOps = 0;

        return minOps;
    }
};


int main()
{
    vector<int> a = {5,4,3,8};
    Solution s_s;
    vector<vector<int>> grid = {{1,2,2}, {1,1,0},{0,1,0}};
    int res = s_s.minimumOperationsToWriteY(grid);
    cout << "res : " << res << endl;

    return 0;
}
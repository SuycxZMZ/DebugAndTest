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

class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) 
    {
        int n = customers.size();
        int cus_cnt = 0;
        for (int i = 0; i < n; ++i)
        {
            if (grumpy[i] == 0) cus_cnt += customers[i];
        }
        // cout << "cus_cnt : " << cus_cnt << endl;
        int l = 0, r = 0, ans = 0;
        for ( ; r < n && l <= r; ++l)
        {
            while (r < n && r - l < minutes - 1)
            {
                if (grumpy[r] == 1) cus_cnt += customers[r];
                ++r;
            }
            cout << cus_cnt << " " << "r:" << r << " ";
            ans = ans > cus_cnt ? ans : cus_cnt;
            if (grumpy[l] == 1) cus_cnt -= customers[l];
            cout << "debug:" << cus_cnt << " " << "l" << l << endl;
        }
        return ans;
    }
};


int main()
{
    vector<int> customs = {1,0,1,2,1,1,7,5};
    vector<int> gromy = {0,1,0,1,0,1,0,1};
    Solution s_s;
    int res = s_s.maxSatisfied(customs, gromy, 3);
    return 0;
}
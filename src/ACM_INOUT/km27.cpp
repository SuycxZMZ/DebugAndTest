//
// Created by SuycxZMZ on 24-7-13.
//
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// 计算最长递增子序列长度的函数
int lengthOfLIS(vector<int>& nums) {
    if (nums.size() <= 1) return nums.size();
    vector<int> dp(nums.size(), 1);
    int max_len = 1;
    for (size_t i = 1; i < nums.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        max_len = max(max_len, dp[i]);
    }
    return max_len;
}


int main(){
    int n;
    cin>>n;
    while(n--) {

        string str1;
        cin>>str1;

        string str = str1.substr(1, str1.size() - 2);

        // 使用 stringstream 分割
        stringstream ss(str);
        string s;
        vector<int> st;
        while(getline(ss,s,',')){
            st.push_back(stoi(s));
        }
        int maxlen= lengthOfLIS(st);

        cout<<maxlen<<endl;
    }

}

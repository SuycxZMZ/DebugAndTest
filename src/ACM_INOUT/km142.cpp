//
// Created by yuan su on 24-7-14.
//
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

int minimumDeleteSum(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // 初始化 dp 表
    for (int i = 1; i <= m; ++i) {
        dp[i][0] = dp[i-1][0] + s1[i-1];
    }
    for (int j = 1; j <= n; ++j) {
        dp[0][j] = dp[0][j-1] + s2[j-1];
    }

    // 填充 dp 表
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = min(dp[i-1][j] + s1[i-1], dp[i][j-1] + s2[j-1]);
            }
        }
    }

    return dp[m][n];
}

int main() {
    string a, b;
    cin >> a >> b;

    cout << minimumDeleteSum(a, b) << endl;

    return 0;
}
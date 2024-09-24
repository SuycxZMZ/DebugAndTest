/// 小红有一笔旅游预算，旅游地点有若干组项目，每个项目有自己的价格和体验次数，
/// 求在当前预算下最多能体验的次数。预算和价格都是50的倍数。

/// 输入
/// 第一行输入总预算。之后K行输入每个项目的花费和能体验的项目次数。

/// 输出
/// 在当前预算下最多能体验的次数。

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int money = 0;
int ans = 0;
vector<pair<int, int>> nums;

int main() {
    cin >> money;
    int n, t;
    while (cin >> n >> t) {
        nums.emplace_back(n, t);
    }

    // 贪心
    int mm = money;
    int ans1 = 0;
    sort(nums.begin(), nums.end(), [](const pair<int, int>& a, const pair<int, int>& b) -> bool {
        return a.first < b.first;
    });
    for (int i = 0; i < nums.size(); ++i) {
        int tmp = nums[i].first * nums[i].second;
        if (tmp <= mm) {
            ans1 += nums[i].second;
            mm -= tmp;
        } else {
            ans1 += (mm / nums[i].first);
            break;
        }
    }
    cout << "ans1:" << ans1 << endl;
    // dp
    vector<int> dp(money + 1, 0);
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = 0; j < nums[i].second; ++j) {
            for (int k = money; k >= nums[i].first; ++k) {
                dp[k] = max(dp[k], dp[k - nums[i].first] + 1);
            }
        }
    }

    cout << "ans2:" << dp[money] << endl;

    return 0;
}
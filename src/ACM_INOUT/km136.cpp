//
// Created by SuycxZMZ on 24-7-13.
//
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <algorithm>

using namespace std;
using LL = long long;

bool check(unordered_set<LL>& ori, vector<LL>& nums) {
    if (nums.empty()) return false;
    for (LL n : nums) {
        if (ori.find(n) != ori.end()) return true;
    }
    return false;
}

int main() {

    int M = 0;
    cin >> M;
    unordered_set<LL> uset;
    LL tmp;
    for (int i = 0; i < M; ++i) {
        cin >> tmp;
        uset.emplace(tmp);
    }

    // 接下来 n 个节点
    int n = 0;
    cin >> n;

    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        int x = 0, y = 0;
        cin >> x >> y;
        vector<LL> nums(y, 0);
        for (int i = 0; i < y; ++i) {
            cin >> nums[i];
        }
        if (check(uset, nums)) ans.emplace_back(x);
    }

    std::sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (LL p : ans) {
        cout << p << " ";
    }

    return 0;
}
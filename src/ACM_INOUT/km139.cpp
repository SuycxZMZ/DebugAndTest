//
// Created by 28329 on 24-7-15.
//
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

bool checkPerfect(int n) {
    int cnt = 0;
    while (n) {
        cnt += (n % 10 != 0);
        n /= 10;
    }
    return cnt == 1;
}

int getPerfectNums(vector<int>& nums) {
    int ans = 0;
    for (int i = 0; i < nums.size() - 1; ++i) {
        for (int j = i + 1; j < nums.size(); ++j) {
            ans += checkPerfect(nums[i] * nums[j]);
        }
    }
    return ans;
}

int main() {
    int N = 0;
    cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; ++i) cin >> nums[i];

    cout << getPerfectNums(nums) << endl;

    return 0;
}
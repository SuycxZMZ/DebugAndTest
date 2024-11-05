// 给定二维数组，求一天之内同时在线的最大人数
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int most_online(vector<vector<int>> &times) {
  int n = times.size();
  if (n == 0) return  0;
  vector<int> s(n, 0), e(n, 0);
  for (int i = 0; i < n; ++i) {
    s[i] = times[i][0];
    e[i] = times[i][1];
  }
  sort(s.begin(), s.end());
  sort(e.begin(),e.end());

  int ans = 0, i = 0, j = 0;
  int cur = 0;
  while (i < n && j < n) {
    // 开始时间小于当前结束时间，有人上线
    if (s[i] < e[j]) {
      ++cur;
      ans = max(ans, cur);
      ++i;
    } else { // 结束时间不大于开始时间，有人下线
      --cur;
      ++j;
    }
  }
  return ans;
}

int main() {
  vector<vector<int>> times = {{1, 3}, {2, 4}, {2, 5}, {4, 5}};
  cout << "ans: " << most_online(times) << endl; // 预期输出: 3

  times = {{5, 10}, {1, 3}, {2, 6}, {4, 8}, {7, 9}, {10, 12}};
  cout << "ans: " << most_online(times) << endl; // 预期输出: 3

  times = {{1, 10}, {2, 3}, {4, 5}, {6, 7}, {8, 9}};
  cout << "ans: " << most_online(times) << endl; // 预期输出: 2

  times = {{1, 5}, {1, 5}, {1, 5}, {1, 5}, {1, 5}};
  cout << "ans: " << most_online(times) << endl; // 预期输出: 5

  return 0;
}
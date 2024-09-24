#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T> void heapify(vector<T> &input, int n, int idx) {
  int l = idx * 2 + 1;
  int r = idx * 2 + 2;
  int biggest = idx;
  if (l < n && input[l] > input[biggest])
    biggest = l;
  if (r < n && input[r] > input[biggest])
    biggest = r;
  if (biggest != idx) {
    swap(input[idx], input[biggest]);
    heapify(input, n, biggest);
  }
}

template <typename T> void heapSort(vector<T> &input) {
  // 从后往前，先调整建堆
  int n = input.size();
  for (int i = n / 2; i >= 0; --i) {
    heapify(input, n, i);
  }

  for (int i = n - 1; i >= 0; --i) {
    swap(input[0], input[i]);
    heapify(input, i, 0);
  }
}

template <typename T> void qqSotr(vector<T> &input, int left, int right) {
  if (left >= right)
    return;
  int l = left, r = right;
  T privot = input[(l + r) / 2];
  while (l <= r) {
    while (l <= r && input[l] < privot)
      ++l;
    while (l <= r && input[r] > privot)
      --r;
    if (l <= r)
      swap(input[l++], input[r--]);
  }
  if (r > left)
    qqSotr(input, left, r);
  if (right > l)
    qqSotr(input, l, right);
}

void getNext(const string &needle, vector<int> &next) {
  int n = needle.size();
  int i = 1, j = 0;
  while (i < n) {
    while (j > 0 && needle[j] != needle[i])
      j = next[j - 1];
    if (needle[j] == needle[i])
      ++j;
    next[i] = j;
    ++i;
  }
  cout << "debug --> next:";
  for (int x : next)
    cout << x << " ";
  cout << endl;
}

int KMP(const string &pattern, const string &needle) {
  vector<int> next(needle.size(), 0);
  getNext(needle, next);
  int i = 1, j = 0;
  while (i < pattern.size()) {
    while (j > 0 && pattern[i] != needle[j])
      j = next[j - 1];
    if (needle[j] == pattern[i])
      ++j;
    if (j == needle.size()) {
      cout << "p:" << (i - j + 1) << endl;
      // return i - j + 1;
      j = next[j - 1];
    }
    ++i;
  }
  return -1;
}

int main() {
  vector<int> input = {1, 7, 3, 2, 5, 4, 19, 11, 10, 15, 14, 13};
  vector<int> input2 = {1, 7, 3, 2, 5, 4, 19, 11, 10, 15, 14, 13};
  heapSort(input);
  for (int n : input)
    cout << n << " ";
  cout << endl;
  qqSotr(input2, 0, input2.size() - 1);
  for (int n : input2)
    cout << n << " ";

  cout << endl;
  
  string pattern = "mymyhellhellomymyhel";
  string needle = "myhel";
  int ans = KMP(pattern, needle);
  cout << "pp:" << ans << endl;

  return 0;
}

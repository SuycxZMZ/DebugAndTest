#include <bits/stdc++.h>
#include <vector>

using namespace std;

template <typename T>
void myQsort(vector<T> &input, int start, int end) {
  if (end == start)
    return;
  int l = start, r = end;
  T privot = input[(l + r) / 2];
  while (l < r) {
    while (input[l] < privot)
      ++l;
    while (input[r] > privot)
      --r;
    std::swap(input[l], input[r]);
    ++l;
    --r;
  }
  if (r > start)
    myQsort(input, start, r);
  if (l < end)
    myQsort(input, l, end);
}

void getNext(const string& needle, vector<int>& next) {
  int j = 0, n = needle.size();
  int i = 0;
  while (i < n) {
    while (j > 0 && needle[i] != needle[j])
      j = next[j];
    if (needle[i] == needle[j])
      ++j;
    next[i] = j;
    ++i;
  }
}

int strStr(const string &s, const string &needle) {
  vector<int> next(needle.size(), 0);
  getNext(needle, next);
  int ans = -1;
  int i = 0, j = 0;
  int n = s.size(), ns = needle.size();
  while (i < n) {
    while (j > 0 && s[i] != needle[j])
      j = next[j];
    if (s[i] == needle[j])
      ++j;
    if (j == ns)
      return i - j + 1;
    ++i;
  }
  return ans;
}


int main() {

  vector<int> input = {1, 12, 16, 2, 4, 6, 5, 7, 11, 22, 16};
  myQsort(input, 0, input.size() - 1);
  for (int i : input) {
    cout << i << " " ;
  }
  
  std::cout << " -------------------- KMP -------------------- " << std::endl;
  string s = "mymymkmpmpmymymykmp";
  string needle = "ymkmp";
  cout << strStr(s, needle) << endl;

  return 0;
}
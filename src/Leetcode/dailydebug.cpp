#include <bits/stdc++.h>
using namespace std;

int main() {
  string input;
  cin >> input;
  vector<int> v, i, o;
  int count = 0;

  for (int idx = 0; idx < input.size(); idx++) {
    if (input[idx] == 'v') {
      v.push_back(idx);
    } else if (input[idx] == 'i') {
      i.push_back(idx);
    } else if (input[idx] == 'o') {
      o.push_back(idx);
    }
  }


  int v1 = 0, i1 = 0, o1 = 0;
  while (v1 < v.size() && i1 < i.size() && o1 < o.size()) {

    if (v[v1] < i[i1] && i[i1] < o[o1]) {

      int v2 = i1 + 1; 
      while (v2 < v.size() && v[v2] <= i[i1])
        v2++;

      if (v2 < v.size() && v[v2] < o[o1]) {

        count++;
        v1 = v2 + 1; 
        i1++;
        o1++;
      } else {

        i1++;
        o1++;
      }
    } else {

      if (v[v1] >= i[i1])
        i1++;
      else if (i[i1] >= o[o1])
        o1++;
      else
        v1++;
    }
  }

  cout << count << endl;
  return 0;
}

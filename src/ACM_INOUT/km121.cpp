//
// Created by yuan su on 24-7-14.
//
#include <iostream>
#include <vector>

using namespace std;

int reversTimes(vector<int>& a, vector<int>& b) {
    int n = a.size();
    int count = 0;

    vector<int> prefix(n, 0);
    vector<int> suefix(n, 0);
    for (int i = 0; i < n; ++i) {
        if (a[i] != b[i]) break;
        prefix[i] = 1;
    }
    for (int j = n - 1; j >= 0; --j) {
        if (a[j] != b[j]) break;
        suefix[j] = 1;
    }

    // 遍历区间
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            bool isValid = true;
            if ((i == 0 || prefix[i - 1]) && (j == n - 1 || suefix[j + 1])) {
                for (int k = 0; k < (j - i) / 2; ++k) {
                    if (a[i + k] != b[j - k]) {
                        isValid = false;
                        break;
                    }
                }
                count += isValid;
            }
            // count += isValid;
        }
    }
    return count;
}

int main() {
    int N = 0;
    cin >> N;
    vector<int> a(N, 0);
    vector<int> b(N, 0);
    for (int i = 0; i < N; ++i) cin >> a[i];
    for (int i = 0; i < N; ++i) cin >> b[i];

    cout << reversTimes(a, b) << endl;

    return 0;
}
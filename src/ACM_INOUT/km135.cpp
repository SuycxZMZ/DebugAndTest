//
// Created by 28329 on 24-7-16.
//
#include <vector>
#include <string>
#include <iostream>
#include <queue>

using namespace std;

int minGo(vector<string>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<bool>> vis(m, vector<bool>(n, false));
    int ans = -1;
    queue<pair<int, int>> q;
    q.emplace(0, 0);
    vis[0][0] = true;

    while (!q.empty()) {
        int sz = q.size();
        ans++;
        for (int i = 0; i < sz; ++i) {
            auto [x, y] = q.front();
            q.pop();
            for (int j = x + 1; j < m && grid[j][y] != '*'; ++j) {
                if (j == m - 1 && y == n - 1) return ans + 1;
                if (!vis[j][y]) {
                    q.emplace(j, y);
                    vis[j][y] = true;
                }
            }

            for (int j = y + 1; j < n && grid[x][j] != '*'; ++j) {
                if (x == m - 1 && j == n - 1) return ans + 1;
                if (!vis[x][j]) {
                    q.emplace(x, j);
                    vis[x][j] = true;
                }
            }

            for (int j = x + 1, k = y + 1; j < m && k < n && grid[j][k] != '*'; ++j, ++k) {
                if (j == m - 1 && k == n - 1) return ans + 1;
                if (!vis[j][k]) {
                    q.emplace(j, k);
                    vis[j][k] = true;
                }
            }
        }
    }
    return -1;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    cout << minGo(grid) << endl;

    return 0;
}
//
// Created by SuycxZMZ on 24-7-13.
//
#include <iostream>
#include <unordered_set>
#include <set>
#include <queue>
#include <vector>

using namespace std;

vector<vector<int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int result = 0;
int cnt = 1;
int signalTowerCnt = 0;

void bfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
    queue<tuple<int, int, int>> que;
    que.push({grid[x][y], x, y});
    visited[x][y] = true;

    while (!que.empty()) {
        int size = que.size();
        for (int n = 0; n < size; ++n) {
            auto& [t, x, y] = que.front();
            que.pop();
            if (t == 2) {
                que.push({--t, x, y});
                continue;
            }
            for (int i = 0; i < 4; ++i) {
                int newX = x + dirs[i][0];
                int newY = y + dirs[i][1];
                if (newX < 0 || newX >= grid.size() ||
                    newY < 0 || newY >= grid[0].size() ||
                    visited[newX][newY] || grid[newX][newY] == 0) {
                        continue;
                }
                visited[newX][newY] = true;
                ++cnt;
                que.push({grid[newX][newY] ,newX, newY});
            }
        }
        ++result;
        if (cnt == signalTowerCnt) {
            return;
        }
    }
}

int main() {
    int m, n;
    cin >> m >> n;

    int startX, startY;
    cin >> startX >> startY;
    vector<vector<int>> grid(n, vector<int>(m, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] != 0) {
                ++signalTowerCnt;
            }
        }
    }

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    bfs(grid, visited, startX, startY);
    if (cnt < signalTowerCnt) {
        result = -1;
    }
    cout << result << endl;
    return 0;
}


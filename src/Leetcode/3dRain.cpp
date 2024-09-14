#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

class Solution {
public:
  int trapRainWater(vector<vector<int>> &heightMap) {
    if (heightMap.empty() || heightMap[0].empty())
      return 0;

    int m = heightMap.size();
    int n = heightMap[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,
                   greater<pair<int, pair<int, int>>>>
        minHeap;

    // Push all the boundary cells into the min heap
    for (int i = 0; i < m; ++i) {
      minHeap.push({heightMap[i][0], {i, 0}});
      minHeap.push({heightMap[i][n - 1], {i, n - 1}});
      visited[i][0] = visited[i][n - 1] = true;
    }
    for (int j = 1; j < n - 1; ++j) {
      minHeap.push({heightMap[0][j], {0, j}});
      minHeap.push({heightMap[m - 1][j], {m - 1, j}});
      visited[0][j] = visited[m - 1][j] = true;
    }

    // Directions for moving in the grid
    vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int trappedWater = 0;

    while (!minHeap.empty()) {
      auto curr = minHeap.top();
      minHeap.pop();
      int height = curr.first;
      int x = curr.second.first;
      int y = curr.second.second;

      for (auto dir : directions) {
        int nx = x + dir[0];
        int ny = y + dir[1];

        if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny]) {
          visited[nx][ny] = true;
          // If the neighbor is lower, water will be trapped
          trappedWater += max(0, height - heightMap[nx][ny]);
          // Push the maximum of current height and neighbor height into the
          // heap
          minHeap.push({max(height, heightMap[nx][ny]), {nx, ny}});
        }
      }
    }

    return trappedWater;
  }
};

int main() {
  Solution solution;
  vector<vector<int>> heightMap = {
      {1, 4, 3, 1, 3, 2}, {3, 2, 1, 3, 2, 4}, {2, 3, 3, 2, 3, 1}};
  cout << "Trapped Rain Water: " << solution.trapRainWater(heightMap) << endl;
  return 0;
}

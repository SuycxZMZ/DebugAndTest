#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int m = board.size(), n = board[0].size();
        if (word.size() > m * n) return false;
        vector<vector<bool>> vis(m, vector<bool>(n, false));
        function<bool(int, int, int)> dfs = [&](int idx, int x, int y) -> bool {
            if (board[x][y] != word[idx] || idx >= word.size()) return false;
            if (board[x][y] == word[idx] && idx == word.size() - 1) return true;
            bool isvalid = false;
            int next_x = 0, next_y = 0;
            for (int i = 0; i < 4; ++i) {
                if (isvalid) break;
                next_x = x + dir[i][0];
                next_y = y + dir[i][1];
                if (next_x < 0 || next_x >= m || next_y < 0 || next_y >= n ||
                    vis[next_x][next_y])
                    continue;
                vis[next_x][next_y] = true;
                isvalid = dfs(idx + 1, next_x, next_y) || isvalid;
                vis[next_x][next_y] = false;
            }
            return isvalid;
        };
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == word[0]) {
                    if (dfs(0, i, j)) {
                        std::cout << i << " " << j;
                        return true;
                    }
                }
            }
        }
        return false;
    }
};


int main()
{
    vector<vector<char>> bord = {{'a', 'a'}, {'A', 'A'}};
    bool res = Solution().exist(bord, "aaa");
    std::cout << res << std::endl;
    return 0;
}
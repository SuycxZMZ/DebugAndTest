#include <bits/stdc++.h>

using namespace std;

const int M = 2e5;
const int Mod = 1e5;

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> soider(n + 1, vector<int>(4, 0));
    vector<vector<pair<bool, int>>> grid(M, vector<pair<bool, int>>(M, pair<bool, int>(false, -1)));
    for (int i = 1; i <= n; ++i)
    {
        cin >> soider[i][0] >> soider[i][1] >> soider[i][2] >> soider[i][3];
        auto tmp = pair<bool, int>(true, i);
        grid[Mod + soider[i][0]][Mod + soider[i][i]] = std::move(tmp);
    }

    unordered_map<int, vector<int>> adj;
    int xx = 0, len = 0, x = 0, y = 0;
    float dis = 0, reDis = 0;
    for (int i = 1; i <= n; ++i)
    {
        x = soider[i][0], y = soider[i][1];
        xx = soider[i][2];
        len = soider[i][3];
        reDis = len * len;
        // 右上
        if (xx = 1) {
            // 右
            for (int j = Mod + soider[i][0]; j < Mod + soider[i][0] + len && j < M; ++j) {
                // 上
                float d_x = (j - x) * (j - x);
                for (int k = Mod + soider[i][1]; k > Mod + soider[i][1] - len && k >= 0; --k)
                {
                    if (d_x + (k - y) * (k - y) < reDis && grid[j][k].first) {
                        // 这个点的入度加上 i 点
                        adj[grid[j][k].second].emplace_back(i);
                    }
                }
            }
        }
        // 左上
        if (xx == 2) {

        }
        // 左下
        if (xx == 3) {

        }
        // 右下
        if (xx == 4) {

        }
    }

}

/// 一组n个软件和k（k < (n*(n - 1)/2)）个依赖关系,若干组查询，查询两个软件的前者是否是后者的直接依赖或间接依赖。
/// （对于[a,b]判断a是否是b的前驱节点）

/// 输入
/// 第一行输入两个正整数n和d ，代表软件的个数和依赖关系。后面d行输入相应的依赖关系。
/// 下一行输入一个正整数q，代表查询的组数。之后q行输入相应的查询。

/// 输出
/// 第一行输出q。之后q行每行输出一个正整数，如果是依赖关系，输出1，否则输出0。

#include <bits/stdc++.h>

using namespace std;

int n = 0, d = 0, q = 0;
unordered_map<int, vector<int>> adj;

int dfs(int x, int y, vector<vector<bool>>& cache) {
    if (cache[x][y]) return 1;
    bool valid = false;
    for (int next : adj[x]) {
        cache[x][next] = true;
        if (next == y || dfs(next, y, cache) == 1) {
            valid = true;
            break;
        }
    }
    if (valid) return cache[x][y] = true;
    return false;
}

int main() {
    cin >> n >> d;
    int tmp1, tmp2;
    int cacheSize = INT_MIN;
    for (int i = 0; i < d; ++i) {
        cin >> tmp1 >> tmp2;
        adj[tmp1].push_back(tmp2);
        cacheSize = max({cacheSize, tmp1, tmp2});
    }

    cin >> q;
    vector<int> ans(q);
    vector<vector<bool>> cache(cacheSize + 1, vector<bool>(cacheSize + 1, false));
    for (int i = 0; i < q; ++i) {
        cin >> tmp1 >> tmp2;
        ans[i] = dfs(tmp1, tmp2, cache);
    }

    for (int i = 0; i < q; ++i) {
        if (i != q - 1) {
            cout << ans[i] << endl;
        } else {
            cout << ans[i];
        }
    }
    return 0;
}
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

// 模版
class unionFound
{
private:
    int n = 10000;
    vector<int> father;
public:
    unionFound() : father(n, 0) {};
    unionFound(int _n) : n(_n), father(n, 0) {};
    // 并查集初始化
    void init()
    {
        for (int i = 0; i < n; ++i) father[i] = i;
    }
    // find过程
    int find(int u)
    {
        if (u == father[u]) return u;
        // 路径压缩
        else return father[u] = find(father[u]);
    }
    // 判断 u 和 v 是否同根
    bool isSame(int u, int v)
    {
        u = find(u);
        v = find(v);
        return u == v;
    }
    // 将 v --> u 加入并查集
    void join(int u, int v)
    {
        u = find(u);
        v = find(v);
        if (u == v) return; // 同根
        else father[v] = u;
    }
};

class Solution {
public:
    // leetcode-721
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, int> eToIndex;
        unordered_map<string, string> eToName;

        // 初始化map表
        int eCount = 0;
        for (auto &account : accounts) {
            string &name = account[0];
            for (int i = 1; i < account.size(); ++i) {
                string &em = account[i];
                if (eToIndex.find(em) == eToIndex.end()) {
                    eToIndex.emplace(em, eCount++);
                    eToName.emplace(em, name);
                }
            }
        }

        // 初始化并查集
        unionFound uf(eCount);
        for (auto &account : accounts) {
            int ac1Idx = eToIndex[account[1]];
            for (int i = 2; i < account.size(); ++i) {
                int nextac = eToIndex[account[i]];
                uf.join(ac1Idx, nextac);
            }
        }

        // 答案 map 表
        unordered_map<int, vector<string>> ansMap;
        for (auto &[ac, ec] : eToIndex) {
            int idx = uf.find(ec);
            ansMap[idx].emplace_back(ac);
        }

        vector<vector<string>> ans;
        for (auto &[_, acVec] : ansMap) {
            string &name = eToName[acVec[0]];
            sort(acVec.begin(), acVec.end());
            vector<string> tmp;
            tmp.emplace_back(name);
            for (auto & ac : acVec) {
                tmp.emplace_back(ac);
            }
            ans.emplace_back(tmp);
        }
        return ans;
    }
};

int main()
{


    return 0;
}
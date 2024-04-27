#include <vector>
#include <iostream>
#include <string>

using namespace std;

// 模版
class Solution
{
private:
    int n = 10000;
    vector<int> father;
public:
    Solution() : father(n, 0) {};
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

int main()
{


    return 0;
}
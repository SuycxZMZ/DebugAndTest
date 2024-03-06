#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>
#include <cmath>
using namespace std;

class Solution
{
public:
    using ll = long long;
    // 堆优化 dijkstra
    vector<ll> dijkstra(vector<vector<int>> &roads, int s) 
    {
        // 邻接表
        vector<vector<pair<int, int>>> adj;
        // 节点个数
        int n = 0;
        for (auto road : roads)
        {
            n = max(n, max(road[0], road[1]) + 1);
        }
        adj.resize(n);
        for (auto road : roads)
        {
            int x = road[0], y = road[1], w = road[2];
            adj[x].emplace_back(y, w);
            adj[y].emplace_back(x, w);
        }
        // 用优先级队列做广度遍历
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        vector<ll> dis(n, LLONG_MAX);
        dis[s] = 0;
        pq.emplace(0, s);
        while (!pq.empty())
        {
            auto [w, u] = pq.top(); 
            pq.pop();
            if (w > dis[u]) continue;
            // 可以更新
            for (auto [v, w2] : adj[u])
            {
                if (w + w2 < dis[v])
                {
                    dis[v] = w + w2;
                    pq.emplace(dis[v], v);
                }
            }
        }

        return dis;
    }
    // 朴素 dijkstra
    vector<ll> dijkstra2(vector<vector<int>> &roads, int s) 
    {
        // 邻接表
        vector<vector<pair<int, int>>> adj;
        // 节点个数
        int n = 0;
        for (auto road : roads)
        {
            n = max(n, max(road[0], road[1]) + 1);
        }
        adj.resize(n);
        for (auto road : roads)
        {
            int x = road[0], y = road[1], w = road[2];
            adj[x].emplace_back(y, w);
            adj[y].emplace_back(x, w);
        }
        vector<ll> dis(n, INT_MAX);
        vector<bool> visit(n, false);
        visit[s] = true;
        dis[s] = 0;
        while (1)
        {
            // 每一轮 找未添加且距离最小的点
            int x = -1;
            for (int i = 0; i < n; ++i)
            {
                // 添加过， 直接下一个
                if (visit[i]) continue;
                // 没添加
                if (x < 0 || dis[i] < dis[x])
                {
                    x = i;
                }
            }

            // 找完，如果全部添加完，x == -1，可以直接退出while
            // 如果找到的最小距离为 INT_MAX 则该 x 不可达
            if (x == -1) break;
            if (dis[x] == INT_MAX)
            {
                visit[x] = true;
                continue;
            }

            // 找到未添加的最小距离, 把该点的邻接点全扫描一遍
            visit[x] = true;
            for (auto & [v, w] : adj[x])
            {
                dis[v] = min(dis[v], dis[x] + w);
            }
        }

        return dis;
    }
    // 找 0 --> n-1 最短路径的数量  --> 朴素 dijkstra 算法
    int countPaths(int n, vector<vector<int>>& roads) 
    {
        vector<vector<pair<int, long long>>> graph;
        graph.resize(n);
        for (vector<int> &road : roads) 
        {
            int n1 = road[0], n2 = road[1], c = road[2];
            graph[n1].emplace_back(n2, c);
            graph[n2].emplace_back(n1, c);
        }

        constexpr int N = 1e9 + 7;
        vector<long long> dist(n, LONG_LONG_MAX);
        vector<int> mark(n, 0);
        vector<int> cnt(n, 0);
        dist[0] = 0;
        cnt[0] = 1;
        for (int i = 0; i + 1 < n; i++) 
        {
            long long minInd = -1, minDis = LONG_LONG_MAX;
            for (int j = 0; j < n; j++) 
            {
                if (mark[j] == 0 && dist[j] < minDis) 
                {
                    minDis = dist[j];
                    minInd = j;
                }
            }
            mark[minInd] = 1;
            if (minInd == n - 1) break;
            for (auto [n2, cost] : graph[minInd]) 
            {
                long long newCost = minDis + cost;
                if (newCost < dist[n2]) 
                {
                    dist[n2] = newCost;
                    cnt[n2] = cnt[minInd];
                } 
                else if (newCost == dist[n2]) 
                {
                    cnt[n2] = (cnt[n2] + cnt[minInd]) % N;
                }
            }
        }
        return cnt[n - 1];
    }
};

int main()
{

    return 0;
}

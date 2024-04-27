#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <numeric>
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
    vector<int> dijkstra2(vector<vector<int>> &roads, int k, int n) 
    {
        // 邻接矩阵
        vector<vector<int>> g(n, vector<int>(n, INT_MAX/2));
        for (auto &road : roads) 
        {
            g[road[0] - 1][road[1] - 1] = road[2];
            g[road[1] - 1][road[0] - 1] = road[2];
        }
        vector<int> dis(n, INT_MAX/2), done(n);
        dis[k - 1] = 0;
        while (true)
        {
            int x = -1;
            for (int i = 0; i < n; ++i)
            {
                if (!done[i] && (x < 0 || dis[i] < dis[x])) x = i;
            }

            if (x < 0) break;
            done[x] = true;
            
            for (int y = 0; y < n; ++y)
            {
                dis[y] = min(dis[y], dis[x] + g[x][y]);
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
        vector<long long> dist(n, LLONG_MAX);
        vector<int> mark(n, 0);
        vector<int> cnt(n, 0);
        dist[0] = 0;
        cnt[0] = 1;
        for (int i = 0; i + 1 < n; i++) 
        {
            long long minInd = -1, minDis = LLONG_MAX;
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
    vector<vector<int>> roads = {{1,2,5}, {2,3,6}, {3,6,1}, {5,6,2}, {3,5,2}, {1,4,7}, {4,5,1}};
    Solution s_s;

    vector<long long> dis2 = s_s.dijkstra(roads, 1);
    vector<int> dis = s_s.dijkstra2(roads, 1, 6);

    cout << "--- classic dijkstra all min dis : ";
    for (int d : dis) cout << d << " " ;
    cout << endl;

    cout << "--- heap dijkstra all min dis : ";
    for (int i = 1; i < dis2.size(); ++i) cout << dis2[i] << " ";
    cout << endl;
    return 0;
}

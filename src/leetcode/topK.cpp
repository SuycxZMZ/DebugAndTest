//
// Created by yuan su on 24-4-26.
//
#include <bits/stdc++.h>

using namespace std;

struct cmpp {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
};

class Solution
{
public:
    using PII = pair<int, int>;
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> umap;
        for (int n : nums) umap[n]++;
        priority_queue<PII, vector<PII>, cmpp> pq;
        for (auto &p : umap) {
            pq.push(p);
            if (pq.size() > k) pq.pop();
        }

        vector<int> ans(k);
        for (int i = 0; i < k; ++i) {
            ans[i] = pq.top().first;
            pq.pop();
        }
        return ans;
    }  

    // 快排优化
    template <typename T, typename Compare = std::less<T>>
};


int main() {

    return 0;
}
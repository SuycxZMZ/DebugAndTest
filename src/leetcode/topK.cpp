//
// Created by yuan su on 24-4-26.
//
#include <queue>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution
{
    //          单词 -- 频次
    typedef pair<string,int> PSI;
public:
    /**
     * @brief 最小堆
     * @param words
     * @param k
     * @return
     */
    vector<string> topKFrequent(vector<string>& words, int k) {
        // 1. 统计一下每个单词的频次
        unordered_map<string,int> hash;
        for(auto& s : words) hash[s]++;

        vector<string> ret(k);
        // 2. 创建k个数的小堆
        // decltype是用来推导lambda表达式的类型，通常两者结合来使用
        priority_queue<PSI,vector<PSI>,decltype([](const PSI& a,const PSI& b)->bool {
            if(a.second == b.second) // 频次相同，字典序按照大根堆的方式排列
                return a.first < b.first;
            return a.second > b.second;
            })> heap;
        // 3. TOPK的主逻辑
        for(auto& psi : hash)
        {
            heap.push(psi);
            if(heap.size() > k) heap.pop();
        }
        for(int i = k-1;i >= 0;i--)
        {
            ret[i] = heap.top().first;
            heap.pop();
        }
        return ret;
    }

    /**
     * @brief 快排优化
     * @details [FIX ME]
     * @param words
     * @param k
     * @return
     */
    vector<string> topKFrequent2(vector<string>& words, int k) {
        // 1. 统计一下每个单词的频次
        unordered_map<string,int> hash;
        for(auto& s : words) hash[s]++;
        vector<PSI> allwords(hash.size());
        int i = 0;
        for (auto &[w, f] : hash) {
            allwords[i++] = {w, f};
        }


        auto cmp = [](const PSI &a, const PSI &b)->bool {
            if (a.second == b.second) {
                return a.first < b.first;
            }
            return a.second > b.second;
        };
        function<void(vector<PSI>& v, int left, int right, int k, vector<PSI> &ans)> qqsort = [&](vector<PSI>& v,
                                                                                          int left,
                                                                                          int right,
                                                                                          int k,
                                                                                          vector<PSI> &ans)->void
        {
            if (k == 0) return;
            // 快排
            int i = left, j = right;
            int privotidx = (i + j) / 2;
            PSI privot = v[privotidx];
            while (i <= j) {
                while (cmp(v[i], privot)) ++i;
                while (cmp(privot, v[j])) --j;
                if (i <= j) {
                    swap(v[i++], v[j--]);
                }
            }

            if (j >= left && j - left + 1 > k) {
                qqsort(v, left, j, k, ans);
            } else if (j >= left && j - left + 1 <= k) {
                for (int m = left; m <= j; ++m) {
                    ans.push_back(v[m]);
                }
                qqsort(v, j + 1, right, k - (j - left + 1), ans);
            }
        };

        // ans 已经求出
        vector<PSI> ret;
        qqsort(allwords, 0, allwords.size() - 1, k, ret);
        // std::cout << "ret.size = " << ret.size() << std::endl;
        std::sort(ret.begin(), ret.end(), cmp);
        vector<string> result(k);
        i = 0;
        for (auto &[w, _] : ret) result[i++] = w;
        return result;
    }
};


int main() {

    std::vector<std::string> words = {"the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"};
    Solution s_s;
    std::cout << "--------------heap-------------" << std::endl;
    std::vector<std::string> ans = s_s.topKFrequent(words, 4);
    for (auto & w : ans) std::cout << w << " ";
    std::cout << std::endl;
    std::cout << "--------------qsort-------------" << std::endl;
    std::vector<std::string> ans2 = s_s.topKFrequent2(words, 4);
    for (auto & w : ans2) std::cout << w << " ";
    return 0;
}
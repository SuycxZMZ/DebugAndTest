//
// Created by yuan su on 24-4-26.
//
#include <list>
#include <iostream>

/**
 * @brief LRUCache
 * @brief get put O(1)
 */
class LRUCache {
private:
    int m_capacity = 0;
    std::list<std::pair<int, int>> m_list;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> m_map;
public:
    LRUCache(int capacity) : m_capacity(capacity)
    {
    }

    int get(int key) {
        auto it = m_map.find(key);
        if (m_map.end() == it) return -1;
        // 更新list
        int ans = it->second->second;
        m_list.erase(it->second);
        m_list.emplace_front(key, ans);
        // 更新map
        m_map[key] = m_list.begin();
        return ans;
    }

    void put(int key, int value) {
        auto it = m_map.find(key);
        if (m_map.end() == it) {
            if (m_map.size() == m_capacity) {
                m_map.erase(m_list.back().first);
                m_list.pop_back();
            }
            m_list.emplace_front(key, value);
            m_map.emplace(key, m_list.begin());
        } else {
            m_list.erase(it->second);
            m_list.emplace_front(key, value);
            m_map[key] = m_list.begin();
        }
    }
};

int main() {

    LRUCache lru_cache(5);

    lru_cache.put(2, 3);
    lru_cache.put(4, 5);
    lru_cache.put(6, 7);
    lru_cache.put(8, 9);
    lru_cache.put(10, 11);

    int ans1 = lru_cache.get(6);
    lru_cache.put(4, 6);
    int ans2 = lru_cache.get(4);

    return 0;
}
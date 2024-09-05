//
// Created by yuan su on 24-4-26.
//
#include <list>
#include <iostream>
#include <unordered_map>

using namespace std;

/**
 * @brief LRUCache
 * @brief get put O(1)
 */
class LRUCache {
public:
    using PII = pair<int, int>;
private:
    int _capacity = 0;
    std::list<PII> _list;
    unordered_map<int, std::list<PII>::iterator> _map;
public:
    LRUCache(int capacity) : _capacity(capacity)
    {
    }

    int get(int key) {
        auto it = _map.find(key);
        if (_map.end() == it) {
            return -1;
        } else { // 找到了，要把这个 移到链表前面
            int val = it->second->second;
            _list.erase(it->second);
            _list.emplace_front(key, val);
            it->second = _list.begin();
            return val;
        }
    }

    void put(int key, int value) {
        auto it = _map.find(key);
        if (_map.end() == it) { // 没找到
            if (_map.size() == _capacity) { // 要移除链表内的最后一个元素
                _map.erase(_list.back().first);
                _list.pop_back();
            }
            _list.emplace_front(key, value); // 在前面添加，最近刚使用过
            _map.emplace(key, _list.begin());
        } else { // 找到了，那么就要往前移，并且把value改掉
            _list.erase(it->second);
            _list.emplace_front(key, value);
            it->second = _list.begin();
        }
    }
};


class LFUCache {
private:
    int _capacity;
    int _minFreq;
    using ListIter = std::list<pair<int, int>>::iterator;
    // 存缓存的键值对    (K, (V, 位置))
    unordered_map<int, pair<int, ListIter>> _keyTable;
    // 存储每个频率对应的双向链表  (频率 --> list<K, V>)
    unordered_map<int, list<pair<int, int>>> _freqTable;
    // 存储每个元素对应的频率
    unordered_map<int, int> _freq;

public:
    LFUCache(int capacity) : _capacity(capacity), _minFreq(0) {
    }
    
    int get(int key) {
        auto it = _keyTable.find(key);
        if (_keyTable.end() == it) return -1;

        // 最近使用了，要增加该key的频率
        int val = _keyTable[key].first;
        int f = _freq[key];
        _freqTable[f].erase(_keyTable[key].second); // 要增加，就先移除

        if (_freqTable[f].empty()) {
            _freqTable.erase(f);
            if (_minFreq == f) ++_minFreq;  // 试图更新一下最小使用频率
        }

        ++_freq[key];
        _freqTable[f + 1].emplace_front(key, val);
        _keyTable[key].second = _freqTable[f + 1].begin();
        return val;
    }
    
    void put(int key, int value) {
        if (_capacity == 0) return;
        // 已经有了
        if (_keyTable.find(key) != _keyTable.end()) {
            _keyTable[key].first = value;
            get(key);
            return;
        }

        // 已经满了，要删除一个
        if (_keyTable.size() == _capacity) {
            int eK = _freqTable[_minFreq].back().first;
            _freqTable[_minFreq].pop_back();
            if (_freqTable[_minFreq].empty()) _freqTable.erase(_minFreq);
            // 开始删
            _keyTable.erase(eK);
            _freq.erase(eK);
        }

        // 插入,新的，频率要等于1
        _minFreq = 1;
        _freq[key] = 1;
        _freqTable[1].emplace_front(key, value);
        _keyTable[key] = {value, _freqTable[1].begin()};
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
#include <iostream>
#include <string>

using namespace std;

// next数组
void getNext(const string& needle, vector<int>& next) {
    next[0] = 0;
    int j = 0;
    size_t n = needle.size();
    for (int i = 1; i < n; ++i) {
        while (j > 0 && needle[j] != needle[i]) j = next[j - 1];
        if (needle[j] == needle[i]) ++j;
        next[i] = j;
    }
}

int KMP(const string& pattern, const string& needle) {
    vector<int> next(needle.size(), 0);
    getNext(needle, next);
    int j = 0;
    for (int i = 0; i < pattern.size(); ++i) {
        while (j > 0 && needle[j] != pattern[i]) j = next[j - 1];
        if (needle[j] == pattern[i]) ++j;
        if (j == needle.size()) {
            return i - j + 1;
        }
    }
    return -1;
}

class UnionFind {
private:
    vector<int> _father;
public:
    explicit UnionFind(int size) : _father(size) {
        for (int i = 0; i < size; ++i) _father[i] = i;
    }

    int find(int u) {
        if (_father[u] != u) {
            return _father[u] = find(_father[u]);
        } else {
            return u;
        }
    }

    bool isSameRoot(int u, int v) {
        u = find(u);
        v = find(v);
        return u == v;
    }

    void join(int u, int v) {
        u = find(u);
        v = find(v);
        _father[v] = u;
    }
};


int main() {
    cout << "------------------ KMP-TEST ------------------" << endl;
    string pattern = "mymymymyy";
    string needle = "mymyy";
    int ans = KMP(pattern, needle);
    cout << ans << endl;

    cout << "------------------ UnionFind ------------------" << endl;
    UnionFind uf(10);  // 初始化 10 个元素的并查集
    uf.join(1, 2);     // 合并 1 和 2
    uf.join(3, 4);     // 合并 3 和 4
    uf.join(1, 4);     // 合并 1 和 4, 现在 1, 2, 3, 4 在同一集合
    // 测试同一个集合
    cout << uf.isSameRoot(1, 2) << endl;  // 输出 1 (true)
    cout << uf.isSameRoot(1, 3) << endl;  // 输出 1 (true)
    cout << uf.isSameRoot(1, 5) << endl;  // 输出 0 (false)

    return 0;
}
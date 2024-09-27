#include <iostream>
#include <string>
#include <list>

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

// 大数加法, 假定没有前缀0
string bigNumSum(string& num1, string& num2) {
    if (num1.size() < num2.size()) {
        swap(num1, num2);  // 保证num1长度大于或等于num2
    }
    int n1 = num1.size(), n2 = num2.size();
    int carry = 0;
    string ans = "";
    // 从后往前逐位相加
    for (int i = 0; i < n2; ++i) {
        int idx1 = n1 - 1 - i;
        int idx2 = n2 - 1 - i;
        int cur = (num1[idx1] - '0') + (num2[idx2] - '0') + carry;
        ans += to_string(cur % 10);  // 当前位结果
        carry = cur / 10;            // 进位
    }
    // 如果num1有剩余位数
    for (int i = n2; i < n1; ++i) {
        int idx1 = n1 - 1 - i;
        int cur = (num1[idx1] - '0') + carry;
        ans += to_string(cur % 10);
        carry = cur / 10;
    }
    // 如果最终有进位
    if (carry != 0) {
        ans += to_string(carry);
    }
    reverse(ans.begin(), ans.end());  // 反转字符串得到正确结果
    return ans;
}

// 大数减法，假设两个正数相减，且没有前导0
string bigNumSub(string& num1, string& num2) {
    // 标记结果正负
    bool positive = true;
    if (num1.size() < num2.size() || (num1.size() == num2.size() && num1 < num2)) {
        positive = false;
        swap(num1, num2);
    }
    // 借位
    int carry = 0;
    string ans = "";
    int n1 = num1.size(), n2 = num2.size();
    // 从低位到高位逐位相减
    for (int i = 0; i < n2; ++i) {
        int idx1 = n1 - 1 - i;
        int idx2 = n2 - 1 - i;
        int cur = (num1[idx1] - '0') - (num2[idx2] - '0') + carry;

        if (cur < 0) {
            cur += 10;
            carry = -1;
        } else {
            carry = 0;
        }
        ans += (cur + '0');
    }
    // 处理剩余的num1部分
    for (int i = n2; i < n1; ++i) {
        int idx1 = n1 - 1 - i;
        int cur = (num1[idx1] - '0') + carry;
        if (cur < 0) {
            cur += 10;
            carry = -1;
        } else {
            carry = 0;
        }
        ans += (cur + '0');
    }
    // 去除前导0
    while (ans.size() > 1 && ans.back() == '0') {
        ans.pop_back();
    }
    // 处理符号
    if (!positive) {
        ans += '-';
    }
    // 反转结果字符串
    reverse(ans.begin(), ans.end());
    return ans;
}
// 乘法
string bigNumMul(string& num1, string& num2) {
    int n1 = num1.size(), n2 = num2.size();
    if (num1 == "0" || num2 == "0") return "0";
    vector<int> res(n1 + n2, 0);
    // 从个位开始逐位相乘
    for (int i = n1 - 1; i >= 0; --i) {
        for (int j = n2 - 1; j >= 0; --j) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int p1 = i + j, p2 = i + j + 1;

            int sum = mul + res[p2];
            res[p2] = sum % 10;  // 当前位
            res[p1] += sum / 10; // 进位
        }
    }
    // 将结果转换成字符串
    string ans = "";
    for (int num : res) {
        if (!(ans.empty() && num == 0)) {  // 跳过前导0
            ans += to_string(num);
        }
    }
    return ans.empty() ? "0" : ans;
}

// 除法

// LRU
class LRUCache {
public:
    using LI = std::list<int>;
    using LIR = std::list<int>::iterator;
    using PIR = pair<int, LIR>;
private:
    int _cap;
    LI _list;
    unordered_map<int, pair<int, LIR>> _mp;
public:
    LRUCache(int capacity) : _cap(capacity) {
    }

    int get(int key) {
        // 找到索引
        auto it = _mp.find(key);
        if (it == _mp.end()) return -1;
        // 移除
        int x = it->first;
        int ans = it->second.first;
        auto lit = it->second.second;
        _list.erase(lit);
        _mp.erase(it);
        // 加到链表头
        _list.push_front(x);
        _mp.emplace(pair<int, PIR>(x, {ans, _list.begin()}));
        return ans;
    }

    void put(int key, int value) {
        auto it = _mp.find(key);
        if (it != _mp.end()) { // key已经存在
            auto lit = it->second.second;
            _list.erase(lit);
            _mp.erase(it);
            // 添加
            _list.push_front(key);
            _mp.emplace(pair<int, PIR>(key, {value, _list.begin()}));
        } else { // key不存在
            if (_mp.size() < _cap) {
                _list.push_front(key);
                _mp.emplace(pair<int, PIR>(key, {value, _list.begin()}));
            } else {
                // 要删除
                int ek = _list.back();
                _list.pop_back();
                _mp.erase(ek);
                _list.push_front(key);
                _mp.emplace(pair<int, PIR>(key, {value, _list.begin()}));
            }
        }
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

    cout << "------------------ LRUCache ------------------" << endl;
    LRUCache cache(2);  // 设置容量为2
    // 执行操作
    cache.put(1, 1);
    cache.put(2, 2);
    cout << "get(1): " << cache.get(1) << endl;  // 返回 1
    cache.put(3, 3);    // 移除 key 2
    cout << "get(2): " << cache.get(2) << endl;  // 返回 -1 (未找到)
    cache.put(4, 4);    // 移除 key 1
    cout << "get(1): " << cache.get(1) << endl;  // 返回 -1 (未找到)
    cout << "get(3): " << cache.get(3) << endl;  // 返回 3
    cout << "get(4): " << cache.get(4) << endl;  // 返回 4

    cout << "------------------ bigNumSum ------------------" << endl;
    // 测试用例
    string num1 = "9876543210123456789";
    string num2 = "1234567899876543211";
    string result = bigNumSum(num1, num2);
    cout << "Result: " << result << endl;  // 期望输出: 11111111110000000000
    // 边界测试: 极大数
    string num3 = "999999999999999999999999999999999999999999999999999";
    string num4 = "1";
    string result2 = bigNumSum(num3, num4);
    cout << "Result: " << result2 << endl;  // 期望输出: 1000000000000000000000000000000000000000000000000000

    cout << "------------------ bigNumSub ------------------" << endl;
    // 测试用例
    string num5 = "9876543210123456789";
    string num6 = "1234567899876543211";
    string result3 = bigNumSub(num5, num6);
    cout << "Result: " << result3 << endl;  // 期望输出: 8641975310246913578
    // 边界测试: 小数减大数
    string num7 = "123456789";
    string num8 = "987654321";
    string result4 = bigNumSub(num7, num8);
    cout << "Result: " << result4 << endl;  // 期望输出: -864197532
    // 测试: 两个相等的数
    string num9 = "1000000000000";
    string num10 = "1000000000000";
    string result5 = bigNumSub(num9, num10);
    cout << "Result: " << result5 << endl;  // 期望输出: 0

    cout << "------------------ bigNumMul ------------------" << endl;
    // 测试用例
    string num11 = "123456789";
    string num12 = "987654321";
    string result6 = bigNumMul(num11, num12);
    cout << "Result: " << result6 << endl;  // 期望输出: 121932631112635269

    return 0;
}
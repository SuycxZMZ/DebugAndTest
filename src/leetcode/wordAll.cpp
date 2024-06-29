//
// Created by yuan su on 24-6-28.
//
#include <vector>
#include <unordered_set>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    // 单词拆分：给你一个字符串 s 和一个字符串列表 wordDict 作为字典。
    // 如果可以利用字典中出现的一个或多个单词拼接出 s 则返回 true。
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> uset(wordDict.begin(), wordDict.end());
        // 长度为i  且从0开始的字符串是否合法
        vector<bool> f(s.size() + 1, false);
        // 遍历长度
        f[0] = true;
        string tmp = "";
        for (int i = 1; i <= s.size(); ++i) {
            // 切分，如果前半部分合法且后半部分在集合，则本轮的合法
            for (int j = 0; j < i; ++j) {
                tmp = s.substr(j, i - j);
                if (f[j] && uset.find(tmp) != uset.end()) {
                    f[i] = true;
                    break;
                }
            }
        }
        return f[s.size()];
    }

    // 最长回文子串
    // 中心扩散，从每一个位置开始，向左右各自扩散到与当前位置不想等，然后比较左右，直到再次不想等
    string longestPalindrome(string s) {
        if (s.size() <= 1) return s;
        int sl = s.size();
        int l = 0, r = 0, len = 1, maxStart = 0, maxLen = 0;
        // 枚举中心位置
        for (int i = 0; i < sl; ++i) {
            l = i - 1, r = i + 1; // 左右指针位置
            while (l >= 0 && s[l] == s[i]) {
                ++len;
                --l;
            }
            while (r < sl && s[r] == s[i]) {
                ++len;
                ++r;
            }
            while (l >= 0 && r < sl && s[l] == s[r]) {
                len += 2;
                --l; ++r;
            }
            if (len > maxLen) {
                maxLen = len;
                maxStart = l;
            }
            len = 1;
        }
        return s.substr(maxStart + 1, maxLen);
    }
    // dp，记录状态 f[l][r] 表示 l-->r 是否回文
    string longestPalindrome2(string s) {
        if (s.size() <= 1) return s;
        int sl = s.size(), maxStart = 0, maxLen = 1;
        vector<vector<bool>> f(sl, vector<bool>(sl, false));
        for (int r = 1; r < sl; ++r) {
            for (int l = 0; l < r; ++l) {
                if (s[l] == s[r] && (r - l <= 2 || f[l + 1][r - 1])) {
                    f[l][r] = true;
                    if (r - l + 1 > maxLen) {
                        maxLen = r - l + 1;
                        maxStart = l;
                    }
                }
            }
        }
        return s.substr(maxStart, maxLen);
    }
};

int main() {
    string s = "leetcodebook";
    vector<string> wordDict = {"lee", "t", "code", "book"};
    bool res = Solution().wordBreak(s, wordDict);
    cout << "res:" << res << endl;
    return 0;
}
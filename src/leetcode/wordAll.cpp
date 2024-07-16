//
// Created by yuan su on 24-6-28.
//
#include <vector>
#include <unordered_set>
#include <iostream>
#include <string>
#include <cstdint>

using namespace std;

// 1:单词拆分
// 2:最长回文子串，中心扩散写法
// 3:最长回文子串，动态规划写法
// 4:不同子序列，动态规划。第一道是，t是否是s的子序列，第二道是t在s的子序列中出现了几次
// 5:编辑距离，动态规划

class Solution {
public:
    // 1.单词拆分：给你一个字符串 s 和一个字符串列表 wordDict 作为字典。
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

    // 2.最长回文子串
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
    // 3.dp，记录状态 f[l][r] 表示 l-->r 是否回文
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

    // 4.t是否是s的子序列
    bool isSubsequence(string t, string s) {
        int tl = t.size(), sl = s.size();
        if (tl == 0) return true;
        vector<vector<bool>> f(sl + 1, vector<bool>(tl + 1, false));
        for (int i = 0; i <= sl; ++i) f[i][0] = true;
        for (int i = 1; i <= sl; ++i) {
            for (int j = 1; j <= tl; ++j) {
                if (s[i - 1] == t[j - 1]) {
                    f[i][j] = f[i - 1][j - 1] | f[i - 1][j];
                } else {
                    f[i][j] = f[i - 1][j];
                }
            }
        }
        return f[sl][tl];
    }
    // 4.不同子序列，给你两个字符串 s 和 t ，统计并返回在 s 的 子序列 中 t 出现的个数
    int numDistinct(string s, string t) {
        // f[i][j] 代表 以 i - 1 为结尾的 s 中有多少个以 j - 1 结尾的 t
        int sl = s.size(), tl = t.size();
        if (tl > sl) return 0;

        vector<vector<uint64_t>> f(sl + 1, vector<uint64_t>(tl + 1, 0));
        for (int i = 1; i <= sl; ++i) f[i][0] = 1;
        f[0][0] = 1;
        for (int i = 1; i <= sl; ++i) {
            for (int j = 1; j <= tl; ++j) {
                // 递推，如果相等，那么就是相等与不相等的和
                if (s[i - 1] == t[j - 1]) {
                    f[i][j] = f[i - 1][j - 1] + f[i - 1][j];
                } else {
                    // 如果不相等，i就往前退一位
                    f[i][j] = f[i - 1][j];
                }
            }
        }
        return f[sl][tl] % 1000000007;
    }

    // 5.编辑距离
    int minDistance(string s, string t) {
        int sl = s.size(), tl = t.size();
        vector<vector<int>> f(sl + 1, vector<int>(tl + 1, 0));
        for (int i = 0; i <= sl; ++i) f[i][0] = i;
        for (int i = 0; i <= tl; ++i) f[0][i] = i;

        for (int i = 1; i <= sl; ++i) {
            for (int j = 1; j <= tl; ++j) {
                if (s[i - 1] == t[j - 1]) {
                    f[i][j] = f[i - 1][j - 1];
                } else {
                    f[i][j] = min(min(f[i - 1][j], f[i][j - 1]) + 1, f[i - 1][j - 1] + 1);
                }
            }
        }
        return f[sl][tl];
    }
};

int main() {
    string s = "leetcodebook";
    vector<string> wordDict = {"lee", "t", "code", "book"};
    bool res = Solution().wordBreak(s, wordDict);
    cout << "res:" << res << endl;
    return 0;
}
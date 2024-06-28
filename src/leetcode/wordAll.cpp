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
};

int main() {
    string s = "leetcodebook";
    vector<string> wordDict = {"lee", "t", "code", "book"};
    bool res = Solution().wordBreak(s, wordDict);
    cout << "res:" << res << endl;
    return 0;
}
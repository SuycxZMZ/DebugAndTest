#include <vector>
#include <iostream>

using namespace std;

class Solution 
{
private:
    /**
     * @brief 求最长相等前后缀
     * @details i 作为后缀末尾，j作为前缀末尾
     * @param next 最长相等前后缀数组
     * @param needle 模式串
     */
    void getnext(std::vector<int>& next, std::string needle) {
        int len = needle.size();
        // 最长相等前后缀长度
        int j = 0;
        next[0] = 0;
        // 枚举后缀
        for (int i = 1; i < len; ++i) {
            // 回退
            while (j > 0 && needle[j] != needle[i]) j = next[j - 1];
            if (needle[i] == needle[j]) ++j;
            next[i] = j;
        }
    }

public:
    /**
     * @details KMP
     * @param basic_s 主串
     * @param needle_s 模式串
     * @return 第一个匹配索引,没匹配到，返回-1
     */
    int mystrStr(std::string basic_s, std::string needle_s) {
        vector<int> next(needle_s.size(), 0);
        getnext(next, needle_s);
        int j = 0;
        for (int i = 0; i < basic_s.size(); ++i) {
            while (j > 0 && basic_s[i] != needle_s[j]) j = next[j - 1];
            if (basic_s[i] == needle_s[j]) ++j;
            // 结果
            if (j == next.size()) {
                return (i - j + 1);
            }
        }
        return -1;
    }

    /**
     * @brief 匹配所有索引
     * @details 每次得到一个匹配之后收结果集，进行模式串回退
     * @param haystack 主串
     * @param needle 模式串
     * @return 返回所有索引的vector
     */
    vector<int> strStr_all(string haystack, string needle)
    {
        vector<int> next(needle.size(), 0);
        vector<int> ans;
        getnext(next, needle);
        int j = 0;
        for (int i = 0; i < haystack.size(); ++i) {
            while (j > 0 && haystack[i] != needle[j]) j = next[j - 1];
            if (haystack[i] == needle[j]) ++j;

            if (j == next.size()) {
                ans.emplace_back(i - j + 1);
                // 回退，继续找
                j = next[j - 1];
            }
        }
        return ans;
    }
};


int main()
{

    Solution s_s;
    // std::string haystack = "ababcababcabcabc";
    // std::string needle = "abc";

    std::string haystack = "mymymhellomymymym";
    std::string needle = "bccabcaac";
    vector<int> result = s_s.strStr_all(haystack, needle);
    int res = s_s.mystrStr(haystack, "mymymym");
    for (auto & idx : result)
    {
        std::cout << idx << ' ';
    }
    std::cout << std::endl;
    std::cout << res << std::endl;
    return 0;
}
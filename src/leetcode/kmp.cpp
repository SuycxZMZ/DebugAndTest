#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
#include <cmath>

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
    void getnext2(std::vector<int>& next, std::string needle) {
        next[0] = 0;
        int j = 0;
        for (int i = 0; i < next.size(); ++i) {
            // j 回退
            while (j > 0 && needle[j] != needle[i]) {
                j = next[j - 1];
            }
            if (needle[j] == needle[i]) ++j;
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
        int len1 = basic_s.length(), len2 = needle_s.length();
        vector<int> next(len2, 0);
        getnext2(next, needle_s);
        // 开始KMP匹配
        int j = 0;
        for (int i = 0; i < len1; ++i) {
            while (j > 0 && basic_s[i] != needle_s[j]) {
                j = next[j - 1];
            }
            if (basic_s[i] == needle_s[j]) ++j;
            if (j == next.size()) {
                return (i - next.size() + 1);
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
        if (needle.size() == 0) return vector<int>{};
        vector<int> next(needle.size(), 0);
        getnext2(next, needle);

        vector<int> result;
        // 开始主串匹配
        int j = 0;
        for (int i = 0; i < haystack.size(); ++i)
        {
            while (j > 0 && haystack[i] != needle[j])
            {
                j = next[j - 1];
            }
            if (haystack[i] == needle[j]) ++j;
            // 收结果
            if (j == needle.size())
            {
                result.push_back(i - needle.size() + 1);
                // 重新开始下一轮
                j = next[j - 1];  // 重置 j，继续查找下一个匹配
            }
        }
        return result;
    }
};


int main()
{

    Solution s_s;
    // std::string haystack = "ababcababcabcabc";
    // std::string needle = "abc";

    std::string haystack = "mymymhellomymymym";
    std::string needle = "mym";
    vector<int> result = s_s.strStr_all(haystack, needle);
    int res = s_s.mystrStr(haystack, "hello");
    for (auto & idx : result)
    {
        std::cout << idx << ' ';
    }
    std::cout << std::endl;
    std::cout << res << std::endl;
    return 0;
}
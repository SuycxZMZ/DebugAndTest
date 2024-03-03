#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

class Solution 
{
private:
    // next 数组 第 i 位表示 0--i 最长相等前后缀长度
    void getNext(vector<int>& next, string needle)
    {
        if (next.size() != needle.length())
        {
            cout << "error input !!!" << endl;
            return;
        }
        int j = 0;
        next[0] = 0;
        for (int i = 1; i < needle.size(); ++i)
        {
            while (j > 0 && needle[j] != needle[i])
            {
                j = next[j - 1];
            }
            if (needle[i] == needle[j]) ++j;
            next[i] = j;
        }
    }

public:
    // ******************* 匹配第一个索引 ******************* //
    int strStr(string haystack, string needle) 
    {
        if (needle.size() == 0) return 0;
        vector<int> next(needle.size(), 0);
        getNext(next, needle);

        // 开始主串匹配
        int j = 0;
        for (int i = 0; i < haystack.size(); ++i)
        {
            while (j > 0 && haystack[i] != needle[j]) 
            {
                j = next[j - 1];
            }
            if (haystack[i] == needle[j]) ++j;
            if (j == needle.size())
            {
                // 匹配到一个就直接退出
                return (i - needle.size() + 1);
            }
        }
        return -1;
    }

    // ******************* 匹配所有索引 ******************* //
    vector<int> strStr_all(string haystack, string needle) 
    {
        if (needle.size() == 0) return vector<int>{};
        vector<int> next(needle.size(), 0);
        getNext(next, needle);

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
    int res = s_s.strStr(haystack, needle);
    for (auto & idx : result)
    {
        std::cout << idx << ' ';
    }
    std::cout << std::endl;
    std::cout << res << std::endl;
    return 0;
}
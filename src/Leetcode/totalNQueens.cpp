//
// Created by yuan su on 24-6-21.
//
#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

class Solution {
public:
    using US = unordered_set<int>;
private:
    int backtrack(int n, int rows, US& cols, US& diag1, US& diag2) {
        if (rows == n) return 1;
        else {
            int cnt = 0;
            for (int i = 0; i < n; ++i) { // n 列依次遍历
                if (cols.find(i) != cols.end()) { // 同一列
                    continue;
                }
                // 左上
                int di1 = rows - i;
                if (diag1.find(di1) != diag1.end()) {
                    continue;
                }
                // 右上
                int di2 = rows + i;
                if (diag2.find(di2) != diag2.end()) {
                    continue;
                }
                // -------- 这个位置 (rows, i) 可以放一个
                cols.emplace(i);
                diag1.emplace(di1);
                diag2.emplace(di2);
                // 下一行
                cnt += backtrack(n, rows + 1, cols, diag1, diag2);
                // (rows, i)的所有位置找完了，开始回溯
                cols.erase(i);
                diag1.erase(di1);
                diag2.erase(di2);
            }
            return cnt;
        }
    }
public:
    int totalNQueens(int n) {
        unordered_set<int> cols, diag1, diag2;
        return backtrack(n, 0, cols, diag1, diag2);
    }
};

int main() {
    int result = Solution().totalNQueens(8);
    std::cout << "8 皇后有 " << result << " 种解法" << std::endl;
    return 0;
}
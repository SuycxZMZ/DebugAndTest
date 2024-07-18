//
// Created by yuan su on 24-5-24.
//
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <unordered_map>
#include <numeric>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) { }
    TreeNode(int value) : val(value), left(nullptr), right(nullptr) { }
    TreeNode(int value, TreeNode* l, TreeNode* r) : val(value), left(l), right(r) { }
};

class Solution {
public:
    /**
     * @brief 前 + 中
    */
    TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
        int n = preorder.size();
        std::unordered_map<int, int> pos;
        for (int i = 0; i < n; ++i) pos[inorder[i]] = i;
        /**
         * @brief [a, b]
         * */
        std::function<TreeNode*(int, int, int, int)> dfs = [&](int a, int b, int c, int d) -> TreeNode* {
            if (a > b) return nullptr;
            TreeNode* root = new TreeNode(preorder[a]);
            if (a == b) return root;
            int i = pos[preorder[a]];
            // 两边长度
            int l_len = i - c;
            root->left = dfs(a + 1, a + l_len, c, i - 1);
            root->right = dfs(a + l_len + 1, b, i + 1, d);
            return root;
        };
        return dfs(0, n - 1, 0, n - 1);
    }
};

int main() {


    return 0;
}

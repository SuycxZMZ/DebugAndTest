//
// Created by 28329 on 24-7-15.
//
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int _val) : val(_val), right(nullptr), left(nullptr) {}
};

// 模板
TreeNode* buildTree(vector<string>& nodes, string strnull) {
    if (nodes.empty() || nodes[0] == strnull) return 0;
    TreeNode* root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode*> q;
    q.emplace(root);
    int i = 1;

    while (i < nodes.size() && !q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        if (i < nodes.size() && nodes[i] != strnull) {
            node->left = new TreeNode(stoi(nodes[i]));
            q.emplace(node->left);
        }
        ++i;
        if (i < nodes.size() && nodes[i] != strnull) {
            node->right = new TreeNode(stoi(nodes[i]));
            q.emplace(node->right);
        }
        ++i;
    }
    return root;
}

int ans = 0;
// 以节点root开始的最长相等路径
int maxBtreeLength(TreeNode* root) {
    if (!root) return 0;

    int left = maxBtreeLength(root->left);
    int right = maxBtreeLength(root->right);
    int lPath = 0, rPath = 0;
    if (root->left && root->left->val == root->val) lPath += (left + 1);
    if (root->right && root->right->val == root->val) rPath += (right + 1);
    ans = max(ans, lPath + rPath);
    return max(lPath, rPath);
}

int main() {
    int N = 0;
    cin >> N;
    vector<string> nodeVec(N);
    for (int i = 0; i < N; ++i) {
        cin >> nodeVec[i];
    }

    TreeNode* root = buildTree(nodeVec, "null");
    maxBtreeLength(root);
    cout << ans << endl;

    return 0;
}
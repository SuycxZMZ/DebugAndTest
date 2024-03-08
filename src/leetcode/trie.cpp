#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Trie {
private:
    bool isEnd;
    Trie* child[26];
public:
    Trie() 
    {
        isEnd = false;
        memset(child, 0, sizeof(child));
    }
    
    void insert(string word) 
    {
        Trie* node = this;
        for (char c : word)
        {
            if (node->child[c - 'a'] == NULL) node->child[c - 'a'] = new Trie();
            node = node->child[c - 'a'];
        }
        node->isEnd = true;
    }
    
    bool search(string word) 
    {
        Trie* node = this;
        for (char c : word)
        {
            if (node->child[c - 'a'] == NULL) return false;
            node = node->child[c - 'a'];
        }
        return node->isEnd;
    }
    
    bool startsWith(string prefix) 
    {
        Trie* node = this;
        for (char c : prefix)
        {
            if (node->child[c - 'a'] == NULL) return false;
            node = node->child[c - 'a'];
        }
        return true;
    }
};

// 字符串 borad 搜索单词
class Solution 
{
private:
    vector<int> dx = {1, -1, 0, 0};
    vector<int> dy = {0, 0, 1, -1};
    int m = 0;
    int n = 0;
    vector<string> ans;
    unordered_set<string> uset;
    class TrieNode
    {
    public:
        TrieNode* child[26];
        bool isEnd;
        TrieNode()
        {
            isEnd = false;
            memset(child, 0, sizeof(child));
        }
    };

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words)
    {
        // build trie tree
        TrieNode *root = new TrieNode();
        for (auto & word : words)
        {
            TrieNode *p = root;
            for (char c : word)
            {
                int idx = c - 'a';
                if (p->child[idx] == NULL) p->child[idx] = new TrieNode();
                p = p->child[idx];
            }
            p->isEnd = true;
        }

        m = board.size();
        n = board[0].size();

        queue<pair<int, int>> Q;
        vector<vector<int>> visited(m, vector<int>(n, 0));

        string word = "";
        for (int i = 0; i < m; i++) 
        {
            for (int j = 0; j < n; j++) 
            {
                // 从 i j 开始dfs合法字符串
                dfs(i, j, board, root, word);
            }
        }
     
        for (auto s: uset) 
        {
            ans.emplace_back(s);
        }

        return ans;
    }

    void dfs(int i, int j, vector<vector<char>>& board, TrieNode* root, string& word)
    {
        char c = board[i][j];
        int index = c - 'a';

        if (root->child[index] == NULL) return;
        // 访问标记
        if (c == '0') return;
        board[i][j] = '0';
        word += c;
        if (root->child[index]->isEnd) uset.emplace(word);

        for (int d = 0; d < 4; d++) 
        {
            int y = i + dy[d];
            int x = j + dx[d];
            if (x < 0 || y < 0 || x >= n || y >= m) continue;
            if (board[y][x] == '0') continue;
            dfs(y, x, board, root->child[index], word);
        }

        // 回溯
        word.pop_back();
        board[i][j] = c;
    }
};

int main()
{
    Trie trie;
    
    // Insert some words into the Trie
    trie.insert("apple");
    trie.insert("banana");
    trie.insert("orange");
    
    // Test searching for existing and non-existing words
    cout << "Searching for 'apple': " << (trie.search("apple") ? "Found" : "Not found") << endl;
    cout << "Searching for 'grape': " << (trie.search("grape") ? "Found" : "Not found") << endl;
    
    // Test startsWith function
    cout << "Does Trie contain words starting with 'or'? " << (trie.startsWith("or") ? "Yes" : "No") << endl;
    cout << "Does Trie contain words starting with 'pea'? " << (trie.startsWith("pea") ? "Yes" : "No") << endl;

    return 0;
}
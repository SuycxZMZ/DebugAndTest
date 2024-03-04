#include <iostream>
#include <vector>
#include <string>
#include <cstring>
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
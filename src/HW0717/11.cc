///  输入
///  / / / home usr
///  home opt env usr 1.log
///  home

///  输出
///  home usr 1.log

#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<string> father;
    vector<string> child;
    string s1, s2, s3;
    string tmp;
    getline(cin, s1);
    getline(cin, s2);
    getline(cin, s3);

    stringstream ss1(s1);
    while (getline(ss1, tmp, ' ')) {
        father.push_back(tmp);
    }
    stringstream ss2(s2);
    while (getline(ss2, tmp, ' ')) {
        child.push_back(tmp);
    }

    unordered_map<string, vector<string>> umap;
    for (int i = 0; i < father.size(); ++i) {
        umap[father[i]].push_back(child[i]);
    }

    vector<string> ans = {s3};
    queue<string> q;
    q.push(s3);
    while (!q.empty()) {
        tmp = q.front();
        q.pop();
        if (umap.find(tmp) != umap.end()) {
            for (auto & ranges : umap[tmp]) {
                q.push(ranges);
                ans.push_back(ranges);
            }
        }
    }

    for (int i = 0; i < ans.size(); ++i) {
        if (i != ans.size() - 1) {
            cout << ans[i] << " ";
        } else {
            cout << ans[i];
        }
    }
    cout << endl;
    return 0;
}
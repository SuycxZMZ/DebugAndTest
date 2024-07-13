//
// Created by SuycxZMZ on 24-7-13.
//
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    string ans;
    int yb = 0;
    string s = "";
    string s2 = "";
    while (true) {
        cin >> s;
        if (s.empty() || s == "end") break;
        if (s == "copy") {
            ans.insert(yb, ans.substr(0, yb));
            continue;
        }

        cin >> s2;
        int tmpn = 0;

        if (s == "insert") {
            ans.insert(yb, s2);
            yb += s2.size();
        } else if (s == "move") {
            tmpn = stoi(s2) + yb;
            if (tmpn >= 0 && tmpn <= ans.size()) yb = tmpn;
        } else if (s == "delete") {
            tmpn = stoi(s2);
            if (tmpn <= 0 || yb - tmpn < 0) continue;
            ans.erase(yb - tmpn, tmpn);
            yb -= tmpn;
        }
    }

    if (ans.empty()) {
        cout << "|" << endl;
    } else {
        ans.insert(yb, "|");
        cout << ans << endl;
    }

    return 0;
}
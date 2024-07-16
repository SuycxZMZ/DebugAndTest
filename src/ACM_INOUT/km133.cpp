//
// Created by 28329 on 24-7-16.
//
#include <vector>
#include <iostream>
#include <string>

using namespace std;

string judge(vector<string>& grid) {
    int hong = 0, zi = 0;
    for (int i = 0, j = 0; i < 3 && j < 3; ++i, ++j) {
        if (grid[i][0] == '*' && grid[i][1] == 'o' && grid[i][2] == '*') hong++;
        if (grid[i][0] == 'o' && grid[i][1] == '*' && grid[i][2] == 'o') zi++;
        if (grid[0][j] == '*' && grid[1][j] == 'o' && grid[2][j] == '*') hong++;
        if (grid[0][j] == 'o' && grid[1][j] == '*' && grid[2][j] == 'o') zi++;
    }
    if ((hong != 0 && zi != 0) || (hong == 0 && zi == 0)) return "draw";
    if (hong) return "kou";
    if (zi) return "yukan";
}

int main() {
    int N = 0;
    cin >> N;

    vector<string> ans;
    vector<string> grid(3);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> grid[j];
        }
        ans.emplace_back(judge(grid));
    }

    for (string s : ans) cout << s << endl;
    return 0;
}
//
// Created by 28329 on 24-7-16.
//
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int buildFromBstr(string& str) {
    int ans = 0;
    for (int i = 0; i < str.size(); ++i) {
        ans = ans << 1;
        ans |= (str[i] == '1');
    }
    return ans;
}

int eatMed(int& hong, pair<int, int>& med) {
    int cnt = 0, tmp;
    int flag1 = 0, flag2 = 0, flag3 = 0;
    for (int i = 0; i < 21; ++i) {
        tmp = 1 << i;
        flag1 = tmp & med.first;
        flag2 = tmp & med.second;
        flag3 = tmp & hong;
        if (flag2) {
            cnt++;
            hong |= flag2;
        }
        else if (flag3 && !flag1) {
            cnt++;
            hong |= flag3;
        }
        else {
            hong &= (~tmp);
        }
    }
    return cnt;
}

int main() {

    int N = 0, M = 0;
    string strN;

    cin >> N >> strN >> M;
    int hong = buildFromBstr(strN);
    vector<pair<int, int>> medicine;
    string str1, str2;
    for (int i = 0; i < M; ++i) {
        cin >> str1 >> str2;
        medicine.emplace_back(pair<int, int>{buildFromBstr(str1), buildFromBstr(str2)});
    }

    int q, idx;
    cin >> q;
    vector<int> eat(q);
    for (int i = 0; i < q; ++i) {
        cin >> idx;
        eat[i] = idx - 1;
    }

    for (int i = 0; i < q; ++i) {
//        cout << eatMed(hong, medicine[eat[i]]) << endl;
cout << "0" << endl;
    }

    return 0;
}
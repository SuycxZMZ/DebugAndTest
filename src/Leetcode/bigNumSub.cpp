#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// 比较两个字符串表示的数字，返回1表示a > b，0表示a == b，-1表示a < b
int compareStrings(const string& a, const string& b) {
    if (a.length() > b.length()) return 1;
    if (a.length() < b.length()) return -1;
    return a.compare(b);
}

// 去除字符串左侧的前导零
string removeLeadingZeros(const string& num) {
    size_t start = 0;
    while (start < num.size() && num[start] == '0') {
        start++;
    }
    return start == num.size() ? "0" : num.substr(start);
}

// ******************************** 减法 ******************************** //
// 大数相减，假设a >= b
string subtractStrings(const string& a, const string& b) {
    string result;
    int len1 = a.length(), len2 = b.length();

    // 借位
    int carry = 0;

    for (int i = 0; i < len1; i++) {
        int digitA = a[len1 - 1 - i] - '0';
        int digitB = i < len2 ? b[len2 - 1 - i] - '0' : 0;

        int digit = digitA - digitB - carry;
        if (digit < 0) {
            digit += 10;
            carry = 1;
        } else {
            carry = 0;
        }

        result.push_back(digit + '0');
    }

    // 去除结果中的前导零
    reverse(result.begin(), result.end());
    return removeLeadingZeros(result);
}

string subtractLargeNumbers(const string& num1, const string& num2) {
    string a = num1, b = num2;

    // 比较两个数的大小
    int cmp = compareStrings(a, b);

    if (cmp == 0) {
        return "0"; // 如果两个数相等，结果为0
    } else if (cmp < 0) {
        // 如果a < b，交换它们并在结果前加上负号
        swap(a, b);
        return "-" + subtractStrings(a, b);
    } else {
        return subtractStrings(a, b);
    }
}
// ******************************** 减法 ******************************** //

// ******************************** 加法 ******************************** //
// 大数相加，假设 a > 0 , b > 0
string sumtractStrings(const string& a, const string& b) {
    int len1 = a.length(), len2 = b.length();

    string ans = "";
    int carry = 0;
    for (int i = 0; i < len1; ++i) {
        int digitA = a[len1 - 1 - i] - '0';
        int digitB = i < len2 ? b[len2 - 1 - i] - '0' : 0;

        int digit = digitA + digitB + carry;
        if (digit >= 10) {
            carry = 1;
            digit -= 10;
        } else {
            carry = 0;
        }
        ans.push_back(digit + '0');
    }
    reverse(ans.begin(), ans.end());
    return removeLeadingZeros(ans);
}
string sumtractLargeNumbers(const string& num1, const string& num2) {
    string a = num1, b = num2;
    int cmp = compareStrings(a, b);
    if (cmp < 0) {
        swap(a, b);
    }
    return sumtractStrings(a, b);
}
// ******************************** 加法 ******************************** //

int main() {
    string num1, num2;
    cin >> num1 >> num2;

    string result = subtractLargeNumbers(num1, num2);
    cout << result << endl;

    string sumres = sumtractLargeNumbers(num1, num2);
    cout << sumres << endl;

    return 0;
}
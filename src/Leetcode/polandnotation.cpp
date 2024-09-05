#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>
using namespace std;

// 利用逆波兰表达式求值
class polandNotation
{
public:
    int calculate(string s) 
    {
        int n = s.size();
        // 删除所有空格
        int i = 0;
        for (int j = 0; j < n; j++) 
        {
            if (s[j] != ' ') s[i++] = s[j];
        }
        // 处理形如 (-2) 的特殊情况
        string new_str;
        for(int k = 0; k < i; k++)
        {
            if(s[k] == '-' && (k == 0 || s[k - 1] == '('))
            {
                new_str += "0-";
            } 
            else 
            {
                new_str += s[k];
            }
        }
        cout << "inorder : " << new_str << endl;
        // 中缀转后缀
        stack<char> stk;
        vector<string> res;
        for (int k = 0; k < new_str.size(); k++) 
        {
            // 符号
            if (!(new_str[k] >= '0' && new_str[k] <= '9')) 
            {
                if (stk.empty()) 
                {
                    stk.push(new_str[k]);
                } 
                // + - 优先级最低，要把优先级更高的符号栈中符号加入后缀结果集
                else if (new_str[k] == '+' || new_str[k] == '-') 
                {
                    while (!stk.empty() && stk.top() != '(') 
                    {
                        res.push_back(string(1,stk.top())); stk.pop();
                    }
                    stk.push(new_str[k]);
                } 
                // * / 优先级高于 + - 在碰到 + - 的时候可以直接入结果集
                else if (new_str[k] == '*' || new_str[k] == '/') 
                {
                    while (!stk.empty() && (stk.top() == '*' || stk.top() == '/')) 
                    {
                        res.push_back(string(1,stk.top())); stk.pop();
                    }
                    stk.push(new_str[k]);
                } 
                else if (new_str[k] == '(' ) 
                {
                    // 直接压栈
                    stk.push(new_str[k]);
                } 
                else if (new_str[k] == ')') 
                {
                    while (!stk.empty() && stk.top() != '(') 
                    {
                        res.push_back(string(1,stk.top())); stk.pop();
                    }
                    if(stk.top() == '(')
                    {
                        stk.pop();
                    }
                }
            } 
            // 数字
            else 
            {
                string cur;
                while (k < new_str.size() && new_str[k] >= '0' && new_str[k] <= '9') 
                {
                    cur += new_str[k];
                    k++;
                }
                k--;
                res.push_back(cur);
            }
        }
        if (!stk.empty()) 
        {
            res.push_back(string(1,stk.top()));
            stk.pop();
        }
        cout << "postorder : ";
        for (auto &it : res) cout << it << " ";
        cout << endl;
        // 后缀表达式求值
        stack<int> sta;
        for (int k = 0; k < res.size(); k++) 
        {
            if (res[k] == "+" || res[k] == "-" || res[k] == "*" ||
                res[k] == "/") 
            {
                int a = sta.top(); sta.pop();
                int b = sta.top(); sta.pop();
                int c = 0;
                if (res[k] == "+") {
                    c = b + a;
                } else if (res[k] == "-") {
                    c = b - a;
                } else if (res[k] == "*") {
                    c = b * a;
                } else if (res[k] == "/") {
                    c = b / a;
                }
                sta.push(c);
            } 
            else 
            {
                sta.push(stoi(res[k]));
            }
        }
        int ans = sta.top();
        return ans;
    }
};

int main()
{
    string s = " (1+(4+5  +2)   +( - 1)  -3)+(6+8) ";
    polandNotation s_s;
    int res = s_s.calculate(s);
    cout << "result : " << res << endl;
    return 0;
}
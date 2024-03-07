#include <iostream>
#include <vector>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

namespace suy
{
	class string
	{
	public:
		// typedef char* iterator; 
        using iterator = char*;
		iterator begin()
		{
			return _str;
		}
 
		iterator end()
		{
			return _str + _size;
		}
 
		string(const char* str = "")
			:_size(strlen(str))
			, _capacity(_size)
		{
			//cout << "string(char* str)" << endl;
 
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}
 
		// s1.swap(s2)
		void swap(string& s)
		{
			::swap(_str, s._str);
			::swap(_size, s._size);
			::swap(_capacity, s._capacity);
		}
 
		// 拷贝构造
		string(const string& s)
		{
			cout << "string(const string& s) -- 深拷贝" << endl;
 
			string tmp(s._str);
			swap(tmp);
		}
 
		// 赋值重载
		string& operator=(const string& s)
		{
			cout << "string& operator=(string s) -- 深拷贝" << endl;
			string tmp(s);
			swap(tmp);
 
			return *this;
		}
 
		// 移动构造
		string(string&& s)
		{
			cout << "string(const string& s) -- 移动拷贝" << endl;
 
			swap(s);
		}
 
		// 移动赋值
		string& operator=(string&& s)
		{
			cout << "string& operator=(string s) -- 移动赋值" << endl;
			swap(s);
 
			return *this;
		}
	
 
		~string()
		{
			delete[] _str;
			_str = nullptr;
		}
 
		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}
 
		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;
				_str = tmp;
 
				_capacity = n;
			}
		}
 
		void push_back(char ch)
		{
			if (_size >= _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(newcapacity);
			}
 
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}
 
		//string operator+=(char ch)
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}
 
		const char* c_str() const
		{
			return _str;
		}
	private:
		char* _str = nullptr;
		size_t _size = 0;
		size_t _capacity = 0; // 不包含最后做标识的\0
	};
 
	string to_string(int value)
	{
		bool flag = true;
		if (value < 0)
		{
			flag = false;
			value = 0 - value;
		}
 
		suy::string str;
		while (value > 0)
		{
			int x = value % 10;
			value /= 10;
 
			str += ('0' + x);
		}
 
		if (flag == false)
		{
			str += '-';
		}
 
		std::reverse(str.begin(), str.end());
		return str;
	}
};
 
int main()
{
    //拷贝构造
    suy::string ret1=suy::to_string(-1234567);

    //赋值拷贝
    suy::string ret2;
    ret2=suy::to_string(-1234567);
 
    return 0;
}

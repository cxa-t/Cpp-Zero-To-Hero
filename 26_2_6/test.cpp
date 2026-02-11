#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
using namespace std;

namespace csa
{
	class string
	{
	public:
		void swap(string& s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}

		//string(const char* str = "")
		//{
		//	_size = strlen(str);
		//	_capacity = _size;
		//	_str = new char[_capacity + 1];
		//	strcpy(_str, str);
		//}

		// 短小频繁调用的函数，可以直接定义到类里面，默认是inline
		string(const char* str = "")
		{
			_size = strlen(str);
			// _capacity不包含\0
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		string(const string& s)
		{
			string tmp(s._str);
			swap(tmp);
		}

		string& operator=(string tmp)
		{
			swap(tmp);
			return *this;
		}

	private:
		char* _str;
		size_t _size;
		size_t _capacity;

		static const size_t npos;
	};
}

int main()
{
	//char str[] = "牛马";
	//char16_t str16[] = u"牛马";
	//char32_t str32[] = U"牛马";
	//wchar_t wstr[] = L"牛马";

	//cout << sizeof(str) << endl;
	//cout << sizeof(str16) << endl;
	//cout << sizeof(str32) << endl;
	//cout << sizeof(wstr) << endl;

	std::string s1("1111111111111");
	std::string s2(s1);

	cout << (void*)&s1 << endl;
	cout << (void*)&s2 << endl;

	return 0;
}


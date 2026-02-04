#pragma once

#include <iostream>
#include <string.h>
#include <string>
#include <assert.h>

using namespace std;

namespace csa
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin()
		{
			return _str;
		}
		const_iterator begin() const
		{
			return _str;
		}

		//指向 \0 的位置
		iterator end()
		{
			return _str+_size;
		}

		const_iterator end() const
		{
			return _str + _size;
		}

		string(const char* str="")
		{
			_size = strlen(str);
			_capacity = _size;//capacity不包含\0
			_str = new char[_capacity + 1];
			strcpy(_str, str);//strcpy 会拷贝\0
		}
		
		//深拷贝
		string(const string& s)
		{
			_str = new char[s._capacity + 1];
			_size = s._size;
			_capacity = s._capacity;
			strcpy(_str, s.c_str());
		}
		
		string& operator=(const string& s)
		{
			if (this != &s)
			{
				//因为改变了当前的str，对当前str进行了深拷贝，但是之前对str初始化时的空间也是new出来的
				delete[] _str;

				_str = new char[s._capacity + 1];
				_size = s._size;
				_capacity = s._capacity;
				strcpy(_str, s.c_str());
			}
			return *this;
		}

		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		const char* c_str() const
		{
			return _str;
		}

		size_t capacity() const
		{
			return _capacity;
		}
		size_t size() const
		{
			return _size;
		}

		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}

		char& operator[](size_t pos)
		{
			assert(pos < _size && pos >= 0);
			return _str[pos];
		}

		const char& operator[](size_t pos) const
		{
			assert(pos < _size && pos >= 0);
			return _str[pos];
		}

		void reserve(size_t n);
		void push_back(char ch);
		void append(const char* str);
		string& operator+=(char ch);
		string& operator+=(const char* str);

		void insert(size_t pos, char ch);
		void insert(size_t pos, const char* str);
		void erase(size_t pos, size_t len = npos);

		size_t find(char ch, size_t pos = 0);
		size_t find(const char* str, size_t pos = 0);
		string substr(size_t pos = 0, size_t len = npos);

	private:
		char* _str;
		size_t _size;
		size_t _capacity;

		static const size_t npos;
	};
}

#define _CRT_SECURE_NO_WARNINGS 1

#include "string.h"

namespace csa
{
	const size_t string::npos = -1;

	void string::reserve(size_t n)
	{
		if (n > _capacity)
		{
			//每次需要多开一个存储 \0 capacity不包含 \0
			char* tmp = new char[n+1];
			strcpy(tmp, _str);
			delete[] _str;
			_str = tmp;
			_capacity = n;
		}
	}

	void string::push_back(char ch)
	{
		if (_size == _capacity)
			reserve(_capacity == 0 ? 4 : 2 * _capacity);

		_str[_size] = ch;
		++_size;
		_str[_size] = '\0';
	}

	string& string::operator+=(char ch)
	{
		push_back(ch);
		return *this;
	}

	void string::append(const char* str)
	{
		size_t len = strlen(str);
		if (len + _size > _capacity)
			reserve(_size + len > 2 * _capacity ? _size + len : 2 * _capacity);//太多的话需要多少扩多少，否则进行对齐
		
		strcpy(_str+_size,str);
		_size += len;
	}

	string& string::operator+=(const char* str)
	{
		append(str);
		return *this;
	}

	void string::insert(size_t pos, char ch)
	{
		assert(pos <= _size);

		if (_size == _capacity)
			reserve(_capacity == 0 ? 4 : 2 * _capacity);

		for (size_t i = _size + 1; i > pos; i--)
			_str[i] = _str[i - 1];

		_str[pos] = ch;
		_size++;
	}

	void string::insert(size_t pos, const char* str)
	{
		assert(pos <= _size);
		size_t len = strlen(str);

		if (len + _size > _capacity)
			reserve(_size + len > 2 * _capacity ? _size + len : 2 * _capacity);//太多的话需要多少扩多少，否则进行对齐

		size_t end = _size + len;
		while (end > pos + len - 1)
		{
			_str[end] = _str[end - len];
			--end;
		}

		for (size_t i = 0; i < len; i++)
			_str[pos + i] = str[i];

		_size += len;
	}

	/*void string::insert(size_t pos, const char* str)
	{
		assert(pos <= _size);
		size_t len = strlen(str);

		size_t total = _size + len;

		if (total > _capacity)
			total = total > 2 * _capacity ? total : 2 * _capacity;

		char* tmp = new char[total+1] {0};
		size_t k = 0;
		size_t i = 0;
		size_t j = 0;

		for ( i = 0; i < _size + len; ++i)
		{
			if (i >= pos && i < pos + len)
				tmp[i] = str[k++];
			else
				tmp[i] = _str[j++];
		}

		delete[] _str;
		_str = tmp;
		_capacity = total;
		_size += len;
	}*/

	void string::erase(size_t pos, size_t len)
	{
		assert(pos < _size);
		if (len >= _size - pos)
		{
			_str[pos] = '\0';
			_size = pos;
		}
		else
		{
			for (size_t i = pos + len; i <= _size; ++i)
			{
				_str[i - len] = _str[i];
			}
			_size -= len;
		}
	}

	size_t string::find(char ch, size_t pos)
	{
		assert(pos < _size);
		for (size_t i = pos; i < _size; i++)
		{
			if (_str[i] == ch)
				return i;
		}
		return npos;
	}

	size_t string::find(const char* str, size_t pos)
	{
		assert(pos < _size);
		char* tmp = strstr(_str + pos, str);
		if (tmp == nullptr)
			return npos;
		else
			return tmp - _str;
	}

	string string::substr(size_t pos, size_t len)
	{
		assert(pos < _size);
		if (len > _size - pos)
			len = _size - pos;
		string sub;
		sub.reserve(len);
		for (size_t i = 0; i < len; i++)
		{
			sub += _str[pos + i];
		}
		return sub;
	}

	bool operator<(const string& s1, const string& s2)
	{
		return strcmp(s1.c_str(), s2.c_str()) < 0;
	}
	bool operator==(const string& s1, const string& s2)
	{
		return strcmp(s1.c_str(), s2.c_str()) == 0;
	}
	bool operator<=(const string& s1, const string& s2)
	{
		return s1 < s2 || s1 == s2;
	}
	bool operator>(const string& s1, const string& s2)
	{
		return !(s1 <= s2);
	}
	bool operator>=(const string& s1, const string& s2)
	{
		return !(s1 < s2);
	}
	bool operator!=(const string& s1, const string& s2)
	{
		return !(s1 == s2);
	}

	ostream& operator<<(ostream& out, const string& s)
	{
		for (auto ch : s)
		{
			out << ch;
		}
		return out;
	}

	istream& operator>>(istream& in, string& s)
	{
		//s.clear();
		//char ch;
		////cin提取不到空格换行 所以需要一个字符一个字符提取
		//ch = in.get();
		//while (ch != ' ' && ch != '\n')
		//{
		//	s += ch;
		//	ch = in.get();
		//}
		//return in;

		s.clear();
		const int N = 256;
		char buff[N];
		char ch;
		int i = 0;
		ch = in.get();

		while (ch == ' ' || ch == '\n') 
		{
			ch = in.get(); // 跳过开头的空格和换行
		}

		while (ch != ' ' && ch != '\n')
		{
			buff[i++] = ch;
			if (i == N - 1)
			{
				buff[i] = '\0';
				s += buff;
				i = 0;
			}
			ch = in.get();
		}
		if (i > 0)
		{
			buff[i] = '\0';
			s += buff;
		}
		return in;
	}
}
#pragma once
#include <assert.h>

namespace csa
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		
		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator begin() const
		{
			return _start;
		}

		const_iterator end() const
		{
			return _finish;
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t old_size = size();
				T* tmp = new T[n];
				memcpy(tmp, _start, sizeof(T) * size());
				delete[] _start;
				
				//
				_start = tmp;
				_finish = tmp + old_size;
				_end_of_storage = tmp + n;
			}
		}

		size_t size()
		{
			return _finish - _start;
		}

		size_t capacity()
		{
			return _end_of_storage - _start;
		}

		T& operator[](size_t i)
		{
			assert(i < size());
			return _start[i];
		}

		void push_back(const T& x)
		{
			if (_finish == _end_of_storage)
				reserve(capacity() == 0 ? 4 : 2 * capacity());
			*_finish = x;
			_finish++;
		}

		bool empty() const
		{
			return begin() == end();
		}

		void pop_back()
		{
			assert(!empty());
			--_finish;
		}
		
		/*void insert(iterator pos, const T& x)
		{
			if (_finish == _end_of_storage)
			{
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : 2 * capacity());
				pos = _start + len;
			}
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end+1) = *end;
				end--;
			}
			*pos = x;
			_finish++;
		}*/

		iterator insert(iterator pos, const T& x)
		{
			if (_finish == _end_of_storage)
			{
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : 2 * capacity());
				pos = _start + len;
			}
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				end--;
			}
			*pos = x;
			_finish++;
			return pos;
		}

	private:
		iterator  _start = nullptr;
		iterator  _finish = nullptr;
		iterator  _end_of_storage = nullptr;
	};
	
	template<class T>
	void printVector(const vector<T>& v)
	{
		//auto it = v.begin();
		//没有实例化的类模板里面去取东西，编译器不知道这个const_iterator是类型还是静态成员变量
		//vector<T>::const_iterator it = v.begin();
		typename vector<T>::const_iterator it = v.begin();

		while (it != v.end())
		{
			cout << *it << " ";
			it++;
		}
		cout << endl;

		for (auto& e : v)
		{
			cout << e << " ";
		}
		cout << endl;
	}
}

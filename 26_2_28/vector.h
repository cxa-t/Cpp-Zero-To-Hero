#pragma once

#include <iostream>
#include <assert.h>
using namespace std;
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

		iterator insert(iterator pos, const T& x)
		{
			assert(pos >= _start && pos <= _finish);
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

		iterator erase(iterator pos)
		{
			// 1. 检查合法性：pos 不能越界
			assert(pos >= _start);
			assert(pos < _finish);
			// 2. 将 pos 之后的所有元素向前挪动
			iterator it = pos + 1;
			while (it != _finish)
			{
				*(it - 1) = *it;
				++it;
			}
			// 3. 有效元素个数减 1
			--_finish;
			// 4. 返回删除点位置的迭代器（STL 标准规定）
			// 虽然 pos 的数值没变，但它现在指向的是原先 pos+1 的元素
			return pos;
		}

		void resize(size_t n,T val = T())
		{
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				reserve(n);
				while (_finish < _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}
		}

	private:
		iterator  _start = nullptr;
		iterator  _finish = nullptr;
		iterator  _end_of_storage = nullptr;
	};

	template<class T>
	void printVector(const vector<T>& v)
	{
		auto it = v.begin();
		while (it != v.end())
		{
			std::cout << *it << " ";
			it++;
		}
		std::cout << std::endl;
	}


	void testCsaVector1()
	{
		vector<int> v1;
		v1.push_back(0);
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);

		printVector(v1);

		vector<double> v2;
		v2.push_back(1.1);
		v2.push_back(1.2);
		v2.push_back(2.1);
		v2.push_back(3.1);
		v2.push_back(4.1);
		printVector(v2);
		v2.pop_back();
		printVector(v2);
		cout << v2.empty() << endl;
	}

	void testCsaVector2()
	{
		vector<int> v1;
		v1.push_back(0);
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		//v1.push_back(4);
		printVector(v1);
		//v1.insert(v1.begin(), 30);
		//printVector(v1);

		int x;
		cin >> x;
		auto p = find(v1.begin(), v1.end(), x);
		if (p != v1.end())
		{
			//v1.insert(p, 99);
			//(*p) *= 10;

			p = v1.insert(p, 99);
			(*(p + 1)) *= 10;
		}
		printVector(v1);
	}

	void testCsaVector3()
	{
		vector<int> v;

		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		//v.push_back(4);
		//v.push_back(5);
		printVector(v);

		auto it = v.begin();
		while (it != v.end())
		{
			if (*it % 2 == 0)
			{
				v.erase(it);
			}
			it++;
		}
		printVector(v);
	}

	void testCsaVector4()
	{
		vector<int> v;
		v.resize(10, 1);
		v.reserve(20);

		printVector(v);
		cout << v.size() << endl;
		cout << v.capacity() << endl;

		v.resize(15, 2);
		printVector(v);

		v.resize(25, 3);
		printVector(v);

		v.resize(5);
		printVector(v);
	}

	void testCsaVector5()
	{
		vector<int> v;

		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);

		printVector(v);

		vector<int> v1 = v;
		printVector(v1);
	}
}

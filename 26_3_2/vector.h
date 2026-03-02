#pragma once

#include <iostream>
#include <assert.h> 
#include <vector>
#include <algorithm>
#include <list>
#include <string>
using std::cout;
using std::endl;
using std::cin;

namespace csa
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		//vector()
		//	:_start(nullptr)
		//	,_finish(nullptr)
		//	,_end_of_storage(nullptr)
		//{ }

		vector() = default;

		//拷贝构造
		vector(const vector<T>& v)
		{
			reserve(v.size());
			for (auto& e : v)
			{
				push_back(e);
			}
		}

		~vector()
		{
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}

		void clear()
		{
			_finish = _start;
		}

		//// v1 = v3
		//vector<T>& operator=(const vector<T>& v)
		//{
		//	if (this != &v)
		//	{
		//		clear();
		//		reserve(v.size());
		//		for (auto& e : v)
		//		{
		//			push_back(e);
		//		}
		//	}
		//	return *this;
		//}

		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_of_storage, v._end_of_storage);
		}

		vector<T>& operator=(vector<T>& v)
		{
			swap(v);
			return *this;
		}

		//类模板的成员函数可以是函数模板
		//迭代器区间构造
		template<class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}
		vector(size_t n, const T& val = T())
		{
			reserve(n);
			for (size_t i = 0; i < n; i++)
				push_back(val);
		}
		vector(int n, const T& val = T())
		{
			reserve(n);
			for (int i = 0; i < n; i++)
				push_back(val);
		}

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

		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _end_of_storage - _start;
		}

		T& operator[](size_t i)
		{
			assert(i < size());
			return _start[i];
		}

		const T& operator[](size_t i) const
		{
			assert(i < size());
			return _start[i];
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t old_size = size();
				T* tmp = new T[n];
				//memcpy(tmp, _start, sizeof(T) * size());
				for (size_t i = 0; i < old_size; i++)
				{
					tmp[i] = _start[i];
				}
				delete[] _start;

				_start = tmp;
				_finish = _start + old_size;
				_end_of_storage = _start + n;
			}
		}

		void resize(size_t n, T val = T())
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
					_finish++;
				}
			}
		}

		void push_back(const T& x)
		{
			if (_finish == _end_of_storage)
				reserve(capacity() == 0 ? 4 : capacity() * 2);
			*_finish = x;
			_finish++;
		}

		bool isempty()
		{
			return _finish == _end_of_storage;
		}

		void pop_back()
		{
			assert(!isempty());
			--_finish;
		}

		iterator insert(iterator pos, const T& x)
		{
			assert(pos >= begin());
			assert(pos < end());

			if (_finish == _end_of_storage)
			{
				size_t n = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				pos = _start + n;
			}

			iterator end = _finish - 1;
			while (end != pos)
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
			assert(pos >= begin());
			assert(pos < end());

			auto it = pos + 1;
			while (it != end())
			{
				*(it - 1) = *it;
				it++;
			}
			--_finish;
			return pos;
		}

	private:
		T* _start = nullptr;
		T* _finish = nullptr;
		T* _end_of_storage = nullptr;
	};

	template<class Container>
	void printVector(Container& v)
	{
		for (auto& e : v)
			cout << e << " ";
		cout << endl;
	}

	void test1()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		printVector(v);
	}
	
	void test2()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		printVector(v);
		cout << v.size() << " ";
		cout << v.capacity() << endl;

		v.reserve(20);
		printVector(v);
		cout << v.size() << " ";
		cout << v.capacity() << endl;

		v.resize(5,2);
		printVector(v);
		cout << v.size() << " ";
		cout << v.capacity() << endl;

		v.resize(10, 3);
		printVector(v);
		cout << v.size() << " ";
		cout << v.capacity() << endl;

		v.resize(3);
		printVector(v);
		cout << v.size() << " ";
		cout << v.capacity() << endl;

		cout << v.isempty() << endl;
	}

	void test3()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);

		printVector(v);

		/*v.insert(v.begin() + 2, 30);
		printVector(v);*/

		int x;
		cin >> x;
		auto p = std::find(v.begin(), v.end(), x);
		if (p != v.end())
		{
			p = v.insert(p, 40);
			(*(p + 1)) *= 10;
		}
		printVector(v);
	}

	void test4()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(4);
		v.push_back(5);

		auto it = v.begin();
		while (it != v.end())
		{
			if ((*it) % 2 == 0)
			{
				v.erase(it);
			}
			else
				it++;
		}
		printVector(v);
	}

	void test5()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		printVector(v);

		vector<int> v1;
		v1 = v;
		printVector(v1);
	}

	void test6()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);

		vector<int> v2(v.begin(), v.begin() + 3);
		printVector(v2);
	}

	void test7()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(4);
		v1.push_back(4);

		vector<int> v2(v1.begin(), v1.begin() + 3);
		printVector(v1);
		printVector(v2);

		std::list<int> lt;
		lt.push_back(10);
		lt.push_back(10);
		lt.push_back(10);
		lt.push_back(10);
		vector<int> v3(lt.begin(), lt.end());
		printVector(lt);
		printVector(v2);

		vector<std::string> v4(10, "1111111");
		printVector(v4);

		vector<int> v5(10);
		printVector(v5);

		vector<int> v6(10u, 1);
		printVector(v6);

		vector<int> v7(10, 1);
		printVector(v7);
	}

	void test8()
	{
		vector<std::string> v;
		v.push_back("11111111111111111111");
		v.push_back("11111111111111111111");
		v.push_back("11111111111111111111");
		v.push_back("11111111111111111111");
		printVector(v);

		v.push_back("11111111111111111111");
		printVector(v);
	}
}

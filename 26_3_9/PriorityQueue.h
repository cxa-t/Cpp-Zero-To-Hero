#pragma once

#include <vector>

template <class T>
class Less
{
public:
	bool operator()(const T& x,const T& y)
	{
		return x < y;
	}
};

template <class T>
class Greater
{
public:
	bool operator()(const T& x, const T& y)
	{
		return x > y;
	}
};

namespace csa
{
	template<class T, class Container = vector<T>,class Compare = Less<T>>
	class priority_queue
	{
	public:

		void AdjustUp(size_t child)
		{
			Compare com;
			size_t parent = (child - 1) / 2;
			while (child)
			{
				if (com( _con[parent], _con[child]))
				{
					std::swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;	
				}
			}
		}

		void push(const T& x)
		{
			_con.push_back(x);
			AdjustUp(_con.size() - 1);
		}

		void AdjustDown(size_t parent)
		{
			size_t child = 2 * parent + 1;
			Compare com;
			while (child < _con.size())
			{
				if (child + 1 < _con.size() && com( _con[child],_con[child + 1] ))
					child++;
				if (com(_con[parent] , _con[child]))
				{
					std::swap(_con[child], _con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}

		void pop()
		{
			std::swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			AdjustDown(0);
		}

		const T& top() const
		{
			return _con[0];
		}

		bool empty() const
		{
			return _con.empty();
		}

		size_t size() const
		{
			return _con.size();
		}
	private:
		Container _con;
	};
}

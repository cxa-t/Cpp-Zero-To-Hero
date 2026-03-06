#pragma once

#include <iostream>
#include <assert.h>
using std::cout;
using std::cin;
using std::endl;

namespace csa
{
	//链表节点模板
	template<class T>
	struct list_node
	{
		T _data;
		list_node<T>* _next;
		list_node<T>* _prev;

		list_node(const T& data = T())
			:_data(data)
			,_next(nullptr)
			,_prev(nullptr)
		{ }
	};

	template<class T>
	struct list_iterator
	{
		typedef list_node<T> Node;
		typedef list_iterator<T> Self;
		
		Node* _node;

		list_iterator(Node* node)
			:_node(node)
		{ }

		T& operator*()
		{
			return _node->_data;
		}

		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		Self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		Self operator++(int)
		{
			Self tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		Self operator--(int)
		{
			Self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}

		bool operator!=(const Self& it) const
		{
			return _node != it._node;
		}

		bool operator==(const Self& it) const
		{
			return _node == it._node;
		}

		T* operator->()
		{
			return &_node->_data;
		}
	};

	template<class T>
	struct list_const_iterator
	{
		typedef list_node<T> Node;
		typedef list_const_iterator<T> Self;

		Node* _node;

		list_const_iterator(Node* node)
			:_node(node)
		{
		}

		const T& operator*()
		{
			return _node->_data;
		}

		const T* operator->()
		{
			return &_node->_data;
		}

		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		Self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		Self operator++(int)
		{
			Self tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		Self operator--(int)
		{
			Self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}

		bool operator!=(const Self& it) const
		{
			return _node != it._node;
		}

		bool operator==(const Self& it) const
		{
			return _node == it._node;
		}
	};

	//链表模板
	template<class T>
	class list
	{
	private:
		typedef list_node<T> Node;
	public:
		typedef list_iterator<T> iterator;
		typedef list_const_iterator<T> const_iterator;

		iterator begin() //返回的是第一个数据节点指针
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_head);
		}

		// 无参构造初始化
		list()
		{
			_head = new Node(T());
			_head->_next = _head;
			_head->_prev = _head;
			_size = 0;
		}

		void insert(iterator pos, const T& val)
		{
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* newnode = new Node(val);

			newnode->_next = cur;
			cur->_prev = newnode;
			prev->_next = newnode;
			newnode->_prev = prev;
			++_size;
		}

		void push_back(const T& x)
		{
			//Node* tail = _head->_prev;
			//Node* newnode = new Node(x);
			//tail->_next = newnode;
			//newnode->_prev = tail;
			//newnode->_next = _head;
			//_head->_prev = newnode;
			//++_size;
			insert(end(), x);
		}

		void push_front(const T& x)
		{
			insert(begin(), x);
		}

		void erase(iterator pos)
		{
			assert(pos != end());
			Node* prev = pos._node->_prev;
			Node* next = pos._node->_next;

			prev->_next = next;
			next->_prev = prev;
			delete pos._node;

			--_size;
		}

		void pop_back()
		{
			erase(--end());
		}

		void pop_front()
		{
			erase(begin());
		}

		size_t size()const
		{
			return _size;
		}

		bool empty() const
		{
			return _size == 0;
		}

	private:
		Node* _head;
		size_t _size;
	};

	template<class Container>
	void PrintContainer(const Container& con)
	{
		typename Container::const_iterator it = con.begin();
		while (it != con.end())
		{
			//*it += 10;
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}

	struct AA
	{
		int _a1 = 1;
		int _a2 = 1;
	};

	void test_list1()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_front(10);

		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;

		lt.insert(++lt.begin(), 20);
		for (auto& e : lt)
			cout << e << " ";
		cout << endl;

		lt.pop_back();
		lt.pop_front();
		for (auto& e : lt)
			cout << e << " ";
		cout << endl;

		lt.erase(++lt.begin());
		for (auto& e : lt)
			cout << e << " ";
		cout << endl;

		list<AA> lta;
		lta.push_back(AA());
		lta.push_back(AA());
		lta.push_back(AA());
		lta.push_back(AA());
		list<AA>::iterator ita = lta.begin();
		while (ita != lta.end())
		{
			// 特殊处理，本来应该是两个->才合理，为了可读性，省略了一个->
			// cout << ita->_a1 << ":" << ita->_a2 << endl;
			cout << ita.operator->()->_a1 << ":" << ita.operator->()->_a2 << endl;
			++ita;
		}
		cout << endl;

		PrintContainer(lt);
	}
}
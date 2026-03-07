#pragma once

#include <iostream>
#include <assert.h>
#include <list>
#include <initializer_list>
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
			, _next(nullptr)
			, _prev(nullptr)
		{ }
	};

	template<class T ,class Ref,class Ptr>
	struct list_iterator
	{
		typedef list_node<T> Node; 
		typedef list_iterator<T, Ref, Ptr> Self;

		Node* _node;

		list_iterator(Node* node)
			:_node(node)
		{ }

		Ref operator*()
		{
			return _node->_data;
		}

		Ptr operator->()
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

	/*template<class T>
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
	};*/

	//链表模板
	template<class T>
	class list
	{
	private:
		typedef list_node<T> Node;
	public:
		typedef list_iterator<T, T&, T*> iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;

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

		void empty_init()
		{
			_head = new Node(T());
			_head->_next = _head;
			_head->_prev = _head;
			_size = 0;
		}

		// 无参构造初始化
		list()
		{
			empty_init();
		}

		list(const list<T>& lt)
		{
			empty_init();
			for (auto& e : lt)
				push_back(e);
		}

		list(std::initializer_list<T> il)
		{
			empty_init();
			for (auto& e : il)
				push_back(e);
		}

		void clear()
		{
			auto it = begin();
			while (it != end())
				it = erase(it);//会自动指向下一个元素
		}

		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		void swap(list<T>& lt)
		{
			std::swap(_head, lt._head);
			std::swap(_size, lt._size);
		}

		list<T>& operator=(list<T> lt)
		{
			swap(lt);
			return *this;
		}

		iterator insert(iterator pos, const T& val)
		{
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* newnode = new Node(val);

			newnode->_next = cur;
			cur->_prev = newnode;
			prev->_next = newnode;
			newnode->_prev = prev;
			++_size;
			return iterator(newnode);
		}

		void push_back(const T& x)
		{
			insert(end(), x);
		}

		void push_front(const T& x)
		{
			insert(begin(), x);
		}

		iterator erase(iterator pos)
		{
			assert(pos != end());
			Node* prev = pos._node->_prev;
			Node* next = pos._node->_next;

			prev->_next = next;
			next->_prev = prev;
			delete pos._node;

			--_size;
			return iterator(next);
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
			cout << ita.operator->()->_a1 << ":" << ita.operator->()->_a2 << endl;
			++ita;
		}
		cout << endl;

		PrintContainer(lt);
	}

	void test_list2()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);	
		auto it = lt.begin();   // 指向1
		lt.push_front(10);      // list:10 1 2 3 4
		*it += 1;             // list:10 101 2 3 4
		PrintContainer(lt);     // 10 101 2 3 4

		it = lt.begin();
		while (it != lt.end())
		{
			if (*it % 2 == 0)
				it = lt.erase(it);   
			else
				it++;               
		}
		PrintContainer(lt);
	}

	void test_list3()
	{
		list<int> lt1;
		lt1.push_back(1);
		lt1.push_back(2);
		lt1.push_back(3);
		lt1.push_back(4);
		PrintContainer(lt1);
		list<int> lt2(lt1);
		PrintContainer(lt2);
		lt2.push_back(110);
		lt2.push_back(120);
		lt2.push_back(130);
		lt2.push_back(140);
		PrintContainer(lt2);
		lt1 = lt2;
		PrintContainer(lt1);
	}

	void func(const list<int>& lt)
	{
		PrintContainer(lt);
	}

	void test_list4()
	{
		// 直接构造
		list<int> lt0({ 1,2,3,4,5,6 });
		// 隐式类型转换
		list<int> lt1 = { 1,2,3,4,5,6,7,8 };
		const list<int>& lt3 = { 1,2,3,4,5,6,7,8 };

		func(lt0);
		func({ 1,2,3,4,5,6 });

		PrintContainer(lt1);

		//auto il = { 10, 20, 30 };
		std::initializer_list<int> il = { 10, 20, 30 };
		cout << typeid(il).name() << endl;
		cout << sizeof(il) << endl;
	}
}
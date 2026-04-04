#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;

enum State { EXIST, EMPTY, DELETE };

template <class K, class V>
struct HashData
{
	pair<K, V> _kv;
	State _state = EMPTY;
};

template<class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};

template<>
struct HashFunc<string>
{
	size_t operator()(const string& s)
	{
		size_t hash = 0;
		for (auto ch : s)
		{
			hash += ch;
			hash *= 131;
		}
		return hash;
	}
};

inline unsigned long __stl_next_prime(unsigned long n)
{
	// Note: assumes long is at least 32 bits.
	static const int __stl_num_primes = 28;
	static const unsigned long __stl_prime_list[__stl_num_primes] = {
		53, 97, 193, 389, 769,
		1543, 3079, 6151, 12289, 24593,
		49157, 98317, 196613, 393241, 786433,
		1572869, 3145739, 6291469, 12582917, 25165843,
		50331653, 100663319, 201326611, 402653189, 805306457,
		1610612741, 3221225473, 4294967291
	};
	const unsigned long* first = __stl_prime_list;
	const unsigned long* last = __stl_prime_list + __stl_num_primes;
	const unsigned long* pos = lower_bound(first, last, n);
	return pos == last ? *(last - 1) : *pos;
}

//namespace open_address
//{
//	template <class K, class V, class Hash = HashFunc<K>>
//	class HashTable
//	{
//	public:
//		HashTable()
//			:_tables(__stl_next_prime(0))
//			, _n(0)
//		{
//		}
//
//		bool Insert(const pair<K, V>& kv)
//		{
//			if (Find(kv.first))
//				return false;
//
//			//负载因子>=0.7 扩容
//			if (_n * 10 / _tables.size() >= 7)
//			{
//				HashTable<K, V, Hash> newht;
//				newht._tables.resize(__stl_next_prime(_tables.size() + 1));
//				for (auto& data : _tables)
//				{
//					//旧表数据映射到新表
//					if (data._state == EXIST)
//					{
//						newht.Insert(data._kv);
//					}
//				}
//				_tables.swap(newht._tables);
//			}
//			Hash hash;
//			size_t hash0 = hash(kv.first) % _tables.size();
//			size_t hashi = hash0;
//			size_t i = 1;
//			int flag = 1;
//			while (_tables[hashi]._state == EXIST)
//			{
//				////线性探测
//				//hashi = (hash0 + i) % _tables.size();
//				//i++;
//
//				//二次探测
//				hashi = (hash0 + (i * i * flag)) % _tables.size();
//				if (hashi < _tables.size())
//					hashi += _tables.size();
//				if (flag == 1)
//					flag = -1;
//				else
//				{
//					++i;
//					flag = 1;
//				}
//			}
//			_tables[hashi]._kv = kv;
//			_tables[hashi]._state = EXIST;
//			++_n;
//
//			return true;
//		}
//
//		HashData<K, V>* Find(const K& key)
//		{
//			Hash hash;
//			size_t hash0 = hash(key) % _tables.size();
//			size_t hashi = hash0;
//			size_t i = 1;
//			while (_tables[hashi]._state != EMPTY)
//			{
//				if (_tables[hashi]._kv.first == key && _tables[hashi]._state != DELETE)
//					return &_tables[hashi];
//
//				//线性探测
//				hashi = (hash0 + i) % _tables.size();
//				i++;
//			}
//			return nullptr;
//		}
//
//		bool Erase(const K& key)
//		{
//			HashData<K, V>* ret = Find(key);
//			if (ret)
//			{
//				ret->_state = DELETE;
//				return true;
//			}
//			else
//				return false;
//		}
//	private:
//		vector<HashData<K, V>> _tables;
//		size_t _n;
//	};
//}

namespace hash_bucket
{
	template<class T>
	struct HashNode
	{
		T _data;
		HashNode<T>* _next;
		HashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{ }
	};

	//前置声明
	template<class K, class T, class KeyOfT, class Hash>
	class HashTable;

	template<class K, class T, class Ref, class Ptr, class KeyOfT, class Hash>
	struct HTIterator
	{
		using Node = HashNode<T>;
		using HT = HashTable<K, T, KeyOfT, Hash>;
		using Self = HTIterator<K, T, Ref, Ptr, KeyOfT, Hash>;

		Node* _node;
		const HT* _ht;

		HTIterator(Node* node, const HT* ht)
			:_node(node)
			, _ht(ht)
		{ }

		Ref operator*()
		{
			return _node->_data;
		}

		Ptr operator->()
		{
			return &_node->_data;
		}

		bool operator!=(const Self& s)
		{
			return _node != s._node;
		}

		Self& operator++()
		{
			if (_node->_next)
			{
				_node = _node->_next;
			}
			else
			{
				KeyOfT kot;
				Hash hash;
				size_t hashi = hash(kot(_node->_data)) % _ht->_tables.size();
				++hashi;
				while (hashi < _ht->_tables.size())
				{
					_node = _ht->_tables[hashi];
					if (_node)
						break;
					else
						++hashi;
				}
				if(hashi == _ht->_tables.size())
					_node = nullptr;
			}
			return *this;
		}
	};

	template<class K, class T, class KeyOfT, class Hash>
	class HashTable
	{
		//友元声明
		template<class K, class T, class Ref, class Ptr, class KeyOfT, class Hash>
		friend struct HTIterator;

		using Node = HashNode<T>;

	public:
		HashTable()
			:_tables(__stl_next_prime(0))
			,_n(0)
		{ }

		~HashTable()
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					--_n;
					cur = next;
				}
				_tables[i] = nullptr;
			}
		}

		using Iterator = HTIterator<K, T, T&, T*, KeyOfT, Hash>;
		using ConstIterator = HTIterator<K, T, const T&, const T*, KeyOfT, Hash>;

		Iterator Begin()
		{
			if (_n == 0)
				return End();
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				if (cur)
					return Iterator(cur, this);
			}
			return End();
		}

		Iterator End()
		{
			return Iterator(nullptr, this);
		}

		ConstIterator Begin() const
		{
			if (_n == 0)
				return End();
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				if (cur)
					return ConstIterator(cur, this);
			}
			return End();
		}

		ConstIterator End() const
		{
			return ConstIterator(nullptr, this);
		}

		pair<Iterator, bool> Insert(const T& data)
		{
			KeyOfT kot;
			Iterator it = Find(kot(data));
			if (it != End())
				return {it,false};

			Hash hash;
			if (_n == _tables.size())
			{
				vector<Node*> newtable(__stl_next_prime(_tables.size() + 1));
				//vector<Node*> newtable(_tables.size() * 2);
				for (size_t i = 0; i < _tables.size(); i++)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						//直接拿下来
						Node* next = cur->_next;
						size_t hashi = hash(kot(cur->_data)) % newtable.size();
						cur->_next = newtable[hashi];
						newtable[hashi] = cur;
						cur = next;
					}
					_tables[i] = nullptr;
				}
				_tables.swap(newtable);
			}

			size_t hashi = hash(kot(data)) % _tables.size();
			Node* newnode = new Node(data);
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			++_n;
			return { Iterator{newnode,this}, true };
		}

		Iterator Find(const K& key)
		{
			KeyOfT kot;
			Hash hash;
			size_t hashi = hash(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (kot(cur->_data) == key)
					return Iterator{ cur, this };
				cur = cur->_next;
			}
			return End();
		}

		bool Erase(const K& key)
		{
			KeyOfT kot;
			Hash hash;
			size_t hashi = hash(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					if (prev == nullptr)
					{
						_tables[hashi] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}
					delete cur;
					cur = nullptr;
					--_n;
					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}
			return false;
		}

	private:
		vector<Node*> _tables;
		size_t _n = 0;
	};
}
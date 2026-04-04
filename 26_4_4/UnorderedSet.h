#pragma once
#include"HashTable.h"


namespace csa
{
	template<class K, class Hash = HashFunc<K>>
	class unordered_set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		using iterator = typename hash_bucket::HashTable<K, const K, SetKeyOfT, Hash>::Iterator;
		using const_iterator = typename hash_bucket::HashTable<K, const K, SetKeyOfT, Hash>::ConstIterator;

		iterator begin()
		{
			return _ht.Begin();
		}

		iterator end()
		{
			return _ht.End();
		}

		const_iterator begin() const
		{
			return _ht.Begin();
		}

		const_iterator end() const
		{
			return _ht.End();
		}

		pair<iterator, bool> insert(const K& key)
		{
			return _ht.Insert(key);
		}

		iterator Find(const K& key)
		{
			return _ht.Find(key);
		}

		bool Erase(const K& key)
		{
			return _ht.Erase(key);
		}

	private:
		hash_bucket::HashTable<K, const K, SetKeyOfT,Hash> _ht;
	};

	void Print(const unordered_set<int>& s)
	{
		unordered_set<int>::const_iterator it = s.begin();
		while (it != s.end())
		{
			//*it = 1;
			cout << *it << " ";
			++it;
		}
		cout << endl;

		for (auto e : s)
		{
			cout << e << " ";
		}
		cout << endl;
	}

	void test_set1()
	{
		int a[] = { 3,11,86,7,88,82,1,881,5,6,7,6 };
		unordered_set<int> s;
		for (auto e : a)
		{
			s.insert(e);
		}
		unordered_set<int>::iterator it = s.begin();
		while (it != s.end())
		{
			//*it = 1;
			cout << *it << " ";
			++it;
		}
		cout << endl;

		for (auto e : s)
		{
			cout << e << " ";
		}
		cout << endl;

		Print(s);
	}
}
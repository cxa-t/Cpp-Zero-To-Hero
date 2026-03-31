#pragma once

#include"RBTree.h"

namespace csa
{
	template<class K, class V>
	class map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		using iterator = typename RBTree<K, pair<const K, V>, MapKeyOfT>::Iterator;
		using const_iterator = typename RBTree<K, pair<const K, V>, MapKeyOfT>::ConstIterator;

		iterator begin()
		{
			return _t.Begin();
		}

		iterator end()
		{
			return _t.End();
		}

		const_iterator begin() const
		{
			return _t.Begin();
		}

		const_iterator end()  const
		{
			return _t.End();
		}

		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return _t.Insert(kv);
		}

		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = insert({ key,V() });
			return ret.first->second;
		}

		iterator find(const K & key)
		{
			return _t.Find(key);
		}
	private:
		RBTree<K, pair<const K, V>, MapKeyOfT> _t;
	};
}
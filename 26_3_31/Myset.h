#pragma once

#include"RBTree.h"

namespace csa
{
	template<class K>
	class set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		using iterator = typename RBTree<K, const K, SetKeyOfT>::Iterator;
		using const_iterator = typename RBTree<K, const K, SetKeyOfT>::ConstIterator;

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

		pair<iterator, bool> insert(const K& key)
		{
			return _t.Insert(key);
		}

		iterator find(const K & key)
		{
			return _t.Find(key);
		}

	private:
		RBTree<K, const K, SetKeyOfT> _t;
	};
}
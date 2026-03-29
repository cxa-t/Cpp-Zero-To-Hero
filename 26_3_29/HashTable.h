#pragma once

#include<vector>

enum State { EXIST, EMPTY, DELETE};

template<class K, class V>
struct HashData
{
	pair<K, V> _kv;
	State _state = EMPTY;
};

template<class K, class V>
class HashTable
{
public:
	HashTable()
		:_tables(11)
		, _n(0)
	{ }

private:
	vector<HashData<K, V>> _tables;
	size_t _n;
};
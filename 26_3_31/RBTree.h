#pragma once

#include<iostream>
using namespace std;

enum Colour { RED, BLACK };

template<class T>
struct RBTNode
{
	T _data;
	RBTNode<T>* _left;
	RBTNode<T>* _right;
	RBTNode<T>* _parent;
	Colour _col;

	RBTNode(const T& data)
		:_data(data)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{ }
};

template<class T, class Ref, class Ptr>
struct RBTreeIterator
{
	using Node = RBTNode<T>;
	using Self = RBTreeIterator<T, Ref, Ptr>;

	Node* _node;
	Node* _root;

	RBTreeIterator(Node* node, Node* root)
		:_node(node)
		,_root(root)
	{ }

	Self& operator++()
	{
		if (_node->_right)
		{
			Node* min = _node->_right;
			while (min->_left)
				min = min->_left;
			_node = min;
		}
		else
		{
			Node* cur = _node;
			Node* parent = _node->_parent;
			while (parent && cur == parent->_right)
			{
				cur = parent;
				parent = cur->_parent;
			}
			_node = parent;
		}
		return *this;
	}

	Self& operator--()
	{
		if (_node == nullptr)
		{
			Node* rightmost = _root;
			while (rightmost && rightmost->_right)
				rightmost = rightmost->_right;
			_node = rightmost;
		}
		else if (_node->_left)
		{
			Node* rightmax = _node->_left;
			while (rightmax->_right)
				rightmax = rightmax->_right;
			_node = rightmax;
		}
		else
		{
			Node* cur = _node;
			Node* parent = _node->_parent;
			while (parent && cur == parent->_left)
			{
				cur = parent;
				parent = cur->_parent;
			}
			_node = parent;
		}
		return *this;
	}

	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &(_node->_data);
	}

	bool operator!=(const Self& s) const
	{
		return _node != s._node;
	}

	bool operator==(const Self& s) const
	{
		return _node == s._node;
	}
};

template<class K, class T, class KeyOfT>
class RBTree
{
	using Node = RBTNode<T>;
public:
	using Iterator = RBTreeIterator<T, T&, T*>;
	using ConstIterator = RBTreeIterator<T, const T&, const T*>;

	Iterator Begin()
	{
		Node* cur = _root;
		while (cur && cur->_left)
			cur = cur->_left;
		return Iterator(cur, _root);
	}

	Iterator End()
	{
		return Iterator(nullptr, _root);
	}

	ConstIterator Begin() const
	{
		Node* cur = _root;
		while (cur && cur->_left)
			cur = cur->_left;
		return ConstIterator(cur, _root);
	}

	ConstIterator End() const
	{
		return ConstIterator(nullptr, _root);
	}

	RBTree() = default;

	~RBTree()
	{
		Destroy(_root);
		_root = nullptr;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		Node* pParent = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;
		if (pParent == nullptr)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (pParent->_left == parent)
			{
				pParent->_left = subL;
			}
			else
				pParent->_right = subL;
			subL->_parent = pParent;
		}
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		Node* pParent = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;
		if (pParent == nullptr)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (pParent->_left == parent)
				pParent->_left = subR;
			else
				pParent->_right = subR;
			subR->_parent = pParent;
		}
	}

	pair<Iterator, bool> Insert(const T& data)
	{
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;
			return pair<Iterator, bool>(Iterator(_root, _root), true);
		}

		KeyOfT kot;
		Node* cur = _root;
		Node* parent = cur->_parent;

		while (cur)
		{
			if (kot(cur->_data) < kot(data))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (kot(data) < kot(cur->_data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return pair<Iterator, bool>(Iterator(cur, _root), false);
		}

		cur = new Node(data);
		Node* newnode = cur;
		if (kot(parent->_data) < kot(data))
			parent->_right = cur;
		else
			parent->_left = cur;
		
		cur->_parent = parent;
		cur->_col = RED;

		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					//        g
					//      p    u
					//    c
					if (parent->_left == cur)
					{
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//        g
						//      p    u
						//        c
						RotateL(parent);
						RotateR(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_col == RED)
				{
					//    g
					//  u    p
					//         c
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if (parent->_right == cur)
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//    g
						//  u    p
						//     c
						RotateR(parent);
						RotateL(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
		}
		_root->_col = BLACK;
		return { Iterator(newnode, _root), true };
	}

	Iterator Find(const K& key)
	{
		KeyOfT kot;
		Node * cur = _root;
		while (cur)
		{
			if (kot(cur->_data) < key)
			{
				cur = cur->_right;
			}
			else if (kot(cur->_data) > key)
			{
				cur = cur->_left;
			}
			else
			{
				return Iterator(cur, _root);
			}
		}
		return End();
	}

	int Height()
	{
		return _Height(_root);
	}

	int Size()
	{
		return _Size(_root);
	}

private:
	void Destroy(Node * root)
	{
		if (root == nullptr)
			return;
		Destroy(root->_left);
		Destroy(root->_right);
		delete root;
	}

	int _Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
	}

	int _Size(Node* root)
	{
		if (root == nullptr)
			return 0;
		return _Size(root->_left) + _Size(root->_right) + 1;
	}

private:
	Node* _root = nullptr;
};

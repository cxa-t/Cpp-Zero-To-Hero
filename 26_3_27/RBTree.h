#pragma once

#include<iostream>
using namespace std;

enum Colour { RED, BLACK };

template<class K, class V>
struct RBTNode
{
	pair<K, V> _kv;
	RBTNode<K, V>* _left;
	RBTNode<K, V>* _right;
	RBTNode<K, V>* _parent;
	Colour _col;

	RBTNode(const pair<K, V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{ }
};

template<class K, class V>
class RBTree
{
	using Node = RBTNode<K, V>;
public:
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

	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}
		Node* cur = _root;
		Node* parent = cur->_parent;

		while (cur)
		{
			if (kv.first > cur->_kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (kv.first < cur->_kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return false;
		}

		cur = new Node(kv);
		if (parent->_kv.first < kv.first)
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
		return true;
	}

	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < key)
				cur = cur->_right;
			else if (cur->_kv.first > key)
				cur = cur->_left;
			else
				return cur;
		}
		return nullptr;
	}

	void InOrder()
	{
		_Inorder(_root);
		cout << endl;
	}

	int Height()
	{
		return _Height(_root);
	}

	int Size()
	{
		return _Size(_root);
	}

	bool IsBalance()
	{
		if (_root == nullptr)
			return true;

		if (_root->_col == RED)
			return false;

		Node* cur = _root;
		int refNum = 0;
		while (cur)
		{
			if (cur->_col == BLACK)
				refNum++;
			cur = cur->_left;
		}
		return Check(_root, 0, refNum);
	}

private:
	void _Inorder(Node* root)
	{
		if (root == nullptr)
			return;

		_Inorder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << "---" << root->_col << endl;
		_Inorder(root->_right);
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

	//bool Check(Node* root, int blackNum, const int refNum)
	//{
	//	if (root == nullptr)
	//	{
	//		// 前序遍历走到空时，意味着一条路径走完了
	//		//cout << blackNum << endl;
	//		if (refNum != blackNum)
	//		{
	//			cout << "存在黑色结点的数量不相等的路径" << endl;
	//			return false;
	//		}
	//		return true;
	//	}
	//	// 检查孩子不太方便，因为孩子有两个，且不一定存在，反过来检查父亲就方便多了
	//	if (root->_col == RED && root->_parent->_col == RED)
	//	{
	//		cout << root->_kv.first << "存在连续的红色结点" << endl;
	//		return false;
	//	}
	//	if (root->_col == BLACK)
	//	{
	//		blackNum++;
	//	}
	//	return Check(root->_left, blackNum, refNum) && Check(root->_right, blackNum, refNum);
	//}

	bool Check(Node* root, int blackNum, const int refNum)
	{
		if (root == nullptr)
		{
			if (blackNum != refNum)
				return false;
			return true;
		}

		if (root->_col == RED && root->_parent->_col == RED)
			return false;

		if (root->_col == BLACK)
			blackNum++;

		return Check(root->_left, blackNum, refNum) && Check(root->_right, blackNum, refNum);
	}

private:
	Node* _root = nullptr;
};

#pragma once

#include <iostream>

using namespace std;

namespace csa
{
	template<class K>
	struct BSTNode
	{
		K _val;
		BSTNode<K>* _left;
		BSTNode<K>* _right;

		BSTNode(const K& x)
			:_val(x)
			, _left(nullptr)
			, _right(nullptr)
		{ }
	};

	template <class K>
	class BSTree
	{
		//typedef BSTNode<K> Node;
		using Node = BSTNode<K>;
	public:
		bool Insert(const K& x)
		{
			if (_root == nullptr)
			{
				_root = new Node(x);
				return true;
			}

			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (x > cur->_val)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (x < cur->_val)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					return false;
				}
			}
			cur = new Node(x);
			if (x > parent->_val)
				parent->_right = cur;
			else
				parent->_left = cur;
			return true;
		}

		bool find(const K& x)
		{
			Node* cur = _root;
			while (cur)
			{
				if (x > cur->_val)
				{
					cur = cur->_right;
				}
				else if (x < cur->_val)
				{
					cur = cur->_left;
				}
				else
					return true;
			}
			return false;
		}

		bool Erase(const K& x)
		{
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (x > cur->_val)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (x < cur->_val)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					//左孩子为空
					if (cur->_left == nullptr)
					{
						if (cur == _root)
						{
							_root = cur->_right;
						}
						else
						{
							if (parent->_left == cur)
							{
								parent->_left = cur->_right;
							}
							else if (parent->_right == cur)
							{
								parent->_right = cur->_right;
							}
						}
						delete cur;
						return true;
					}
					else if (cur->_right == nullptr)//右孩子为空
					{
						if (cur == _root)
						{
							_root = cur->_left;
						}
						else
						{
							if (parent->_left == cur)
							{
								parent->_left = cur->_left;
							}
							else if (parent->_right == cur)
							{
								parent->_right = cur->_left;
							}
						}
						delete cur;
						return true;
					}
					else//常规情况
					{
						//左右都不为空
						//替换删除：找右子树最左节点
						Node* replaceparent = cur;
						Node* replace = cur->_right;
						while (replace->_left)
						{
							replaceparent = replace;
							replace = replace->_left;
						}
						cur->_val = replace->_val;

						if (replaceparent->_left == replace)
						{
							replaceparent->_left = replace->_right;
						}
						else if (replaceparent->_right == replace)
						{
							replaceparent->_right = replace->_right;
						}
						delete replace;
						return true;
					}
				}
			}
			return false;
		}

		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}

	private:
		void _InOrder(Node* _root)
		{
			if (_root == nullptr)
				return;
			_InOrder(_root->_left);
			cout << _root->_val << ' ';
			_InOrder(_root->_right);
		}
	private:
		Node* _root = nullptr;
	};
}

namespace key_value
{
	template<class K, class V>
	struct BSTNode
	{
		K _val;
		V _value;

		BSTNode<K, V>* _left;
		BSTNode<K, V>* _right;

		BSTNode(const K& key, const V& value)
			:_val(key)
			, _value(value)
			, _left(nullptr)
			, _right(nullptr)
		{ }
	};

	template <class K, class V>
	class BSTree
	{
		//typedef BSTNode<K> Node;
		using Node = BSTNode<K,V>;
	public:
		BSTree() = default;

		BSTree(const BSTree& t)
		{
			_root = Copy(t._root);
		}

		~BSTree()
		{
			Destroy(_root);
			_root = nullptr;
		}

		BSTree& operator=(BSTree tmp)
		{
			swap(_root, tmp._root);
			return *this;
		}

		bool Insert(const K& key, const V& value)
		{
			if (_root == nullptr)
			{
				_root = new Node(key, value);
				return true;
			}

			Node* parent = nullptr;
			Node* cur = _root;

			while (cur)
			{
				if (cur->_val < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_val > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					return false;
				}
			}

			cur = new Node(key, value);
			if (parent->_val < key)
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}

			return true;
		}

		Node* Find(const K& x)
		{
			Node* cur = _root;
			while (cur)
			{
				if (x > cur->_val)
				{
					cur = cur->_right;
				}
				else if (x < cur->_val)
				{
					cur = cur->_left;
				}
				else
					return cur;
			}
			return nullptr;
		}

		bool Erase(const K& x)
		{
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (x > cur->_val)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (x < cur->_val)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					//左孩子为空
					if (cur->_left == nullptr)
					{
						if (cur == _root)
						{
							_root = cur->_right;
						}
						else
						{
							if (parent->_left == cur)
							{
								parent->_left = cur->_right;
							}
							else if (parent->_right == cur)
							{
								parent->_right = cur->_right;
							}
						}
						delete cur;
						return true;
					}
					else if (cur->_right == nullptr)//右孩子为空
					{
						if (cur == _root)
						{
							_root = cur->_left;
						}
						else
						{
							if (parent->_left == cur)
							{
								parent->_left = cur->_left;
							}
							else if (parent->_right == cur)
							{
								parent->_right = cur->_left;
							}
						}
						delete cur;
						return true;
					}
					else//常规情况
					{
						//左右都不为空
						//替换删除：找右子树最左节点
						Node* replaceparent = cur;
						Node* replace = cur->_right;
						while (replace->_left)
						{
							replaceparent = replace;
							replace = replace->_left;
						}
						cur->_val = replace->_val;

						if (replaceparent->_left == replace)
						{
							replaceparent->_left = replace->_right;
						}
						else if (replaceparent->_right == replace)
						{
							replaceparent->_right = replace->_right;
						}
						delete replace;
						return true;
					}
				}
			}
			return false;
		}

		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}

	private:

		void Destroy(Node* root)
		{
			if (root == nullptr)
				return;

			Destroy(root->_left);
			Destroy(root->_right);
			delete root;
		}


		Node* Copy(Node* root)
		{
			if (root == nullptr)
				return nullptr;
			Node* newroot = new Node(root->_val, root->_value);
			newroot->_left = Copy(root->_left);
			newroot->_right = Copy(root->_right);
			return newroot;
		}

		void _InOrder(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}

			_InOrder(root->_left);
			cout << root->_val << ":" << root->_value << endl;
			_InOrder(root->_right);
		}
	private:
		Node* _root = nullptr;
	};
}

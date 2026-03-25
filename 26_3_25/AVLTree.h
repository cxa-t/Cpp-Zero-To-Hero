#pragma once

#include <iostream>
#include<assert.h>
using namespace std;

namespace csa
{
	template<class K, class V>
	struct AVLTreeNode
	{
		pair<K, V> _kv;
		
		AVLTreeNode<K, V>* _left;
		AVLTreeNode<K, V>* _right;
		// 需要parent指针，后续更新平衡因子需要用到
		AVLTreeNode<K, V>* _parent;
		int _bf;

		AVLTreeNode(const pair<K, V>& kv)
			:_kv(kv)
			, _left(nullptr)
			, _right(nullptr)
			, _parent(nullptr)
			, _bf(0)
		{ }
	};


	template<class K, class V>
	class AVLTree
	{
		using Node = AVLTreeNode<K, V>;
	public:

		bool Insert(const pair<K, V>& kv)
		{
			if (_root == nullptr)
			{
				_root = new Node(kv);
				return true;
			}

			Node* cur = _root;
			Node* parent = nullptr;
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
					return false;//不允许重复值插入
			}
			//插入
			cur = new Node(kv);
			if (kv.first > parent->_kv.first)
				parent->_right = cur;
			else
				parent->_left = cur;
			//三叉链表需要更新祖先节点的指针
			cur->_parent = parent;

			//更新平衡因子
			while (parent)
			{
				if (cur == parent->_left)
					parent->_bf--;
				else
					parent->_bf++;

				// 更新结束 或者不需要继续向上更新
				if (parent->_bf == 0)
					break;
				else if (parent->_bf == -1 || parent->_bf == 1)
				{
					//继续向上更新
					cur = cur->_parent;
					parent = parent->_parent;
				}
				else if (parent->_bf == -2 || parent->_bf == 2)
				{
					// 开始旋转
					if (parent->_bf == -2 && cur->_bf == -1)
					{
						RotateR(parent);
					}
					else if (parent->_bf == 2 && cur->_bf == 1)
					{
						RotateL(parent);
					}
					else if (parent->_bf == -2 && cur->_bf == 1)
					{
						RotateLR(parent);
					}
					else if (parent->_bf == 2 && cur->_bf == -1)
					{
						RotateRL(parent);
					}
					else
					{
						assert(false);
					}
					break;
				}
				else
				{
					cout << "平衡因子出现绝对值大于2的情况" << endl;
					assert(false);// 这里表示出现了绝对值大于2的情况，插入前一定是AVLTree 所以一定有问题，直接断言出去
				}
			}
			return true;
		}

		void RotateR(Node* parent)
		{
			// 实际操作节点：不平衡节点的左节点
			// 修改子树挂在哪？修改的是实际操作节点的右孩子
			Node* subL = parent->_left;
			Node* subLR = subL->_right;

			parent->_left = subLR;
			//修改父节点指针
			if(subLR)
				subLR->_parent = parent;

			//如果修改parent 不知道parent是否为根节点
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
					pParent->_left = subL;
				else
					pParent->_right = subL;
				subL->_parent = pParent;
			}
			subL->_bf = parent->_bf = 0;
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
			subR->_bf = parent->_bf = 0;
		}

		void RotateLR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;

			int bf = subLR->_bf;

			RotateL(subL);
			RotateR(parent);

			if (bf == -1)
			{
				subL->_bf = 0;
				subLR->_bf = 0;
				parent->_bf = 1;
			}
			else if (bf == 1)
			{
				subLR->_bf = 0;
				parent->_bf = 0;
				subL->_bf = -1;
			}
			else if (bf == 0)
			{
				subLR->_bf = 0;
				parent->_bf = 0;
				subL->_bf = 0;
			}
			else
			{
				cout << "旋转前非平衡（bf为3/-3）" << endl;
				assert(false);
			}
		}

		void RotateRL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;

			int bf = subRL->_bf;

			RotateR(subR);
			RotateL(parent);

			if (bf == -1)
			{
				subR->_bf = 1;
				subRL->_bf = 0;
				parent->_bf = 0;
			}
			else if (bf == 1)
			{
				subR->_bf = 0;
				subRL->_bf = 0;
				parent->_bf = -1;
			}
			else if (bf == 0)
			{
				subR->_bf = 0;
				subRL->_bf = 0;
				parent->_bf = 0;
			}
			else
			{
				cout << "旋转前非平衡（bf为3/-3）" << endl;
				assert(false);
			}
		}

		Node* Find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (key > cur->_kv.first)
					cur = cur->_right;
				else if (key < cur->_kv.first)
					cur = cur->_left;
				else
					return cur;
			}
			return nullptr;
		}

		void InOrder()
		{
			_InOrder(_root);
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

		bool IsBalanceTree()
		{
			return _IsBalanceTree(_root);
		}

	private:
		void _InOrder(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}

			_InOrder(root->_left);
			cout << root->_kv.first << ":" << root->_kv.second << endl;
			_InOrder(root->_right);
		}

		int _Size(Node* root)
		{
			if (root == nullptr)
				return 0;

			return _Size(root->_left) + _Size(root->_right) + 1;
		}

		int _Height(Node* root)
		{
			if (root == nullptr)
				return 0;
			int leftHeight = _Height(root->_left);
			int rightHeight = _Height(root->_right);
			return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
		}

		bool _IsBalanceTree(Node* root)
		{
			if (root == nullptr)
				return true;
			int leftheight = _Height(root->_left);
			int rightheight = _Height(root->_right);
			int diff = rightheight - leftheight;

			// 如果计算出的平衡因子与pRoot的平衡因子不相等，或者
			// pRoot平衡因子的绝对值超过1，则一定不是AVL树
			if (abs(diff) >= 2)
			{
				cout << root->_kv.first << "高度差异常" << endl;
				return false;
			}

			if (root->_bf != diff)
			{
				cout << root->_kv.first << "平衡因子异常" << endl;
				return false;
			}

			// pRoot的左和右如果都是AVL树，则该树一定是AVL树
			return _IsBalanceTree(root->_left) && _IsBalanceTree(root->_right);
		}


		bool IsBalanceTreeOpt()
		{
			return _CheckHeightAndBalance(_root) != -1;
		}

		int _CheckHeightAndBalance(Node* root)
		{
			if (root == nullptr)
				return 0;

			int leftHeight = _CheckHeightAndBalance(root->_left);
			if (leftHeight == -1)
				return -1;

			int rightHeight = _CheckHeightAndBalance(root->_right);
			if (rightHeight == -1)
				return -1;

			int diff = rightHeight - leftHeight;

			if (abs(diff) >= 2)
			{
				cout << "节点 " << root->_kv.first << " 高度差异常 (真实高度差: " << diff << ")" << endl;
				return -1;
			}

			if (root->_bf != diff)
			{
				cout << "节点 " << root->_kv.first << " 平衡因子异常 (记录的_bf: " << root->_bf << ", 真实的差值: " << diff << ")" << endl;
				assert(false);
			}

			return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
		}

	private:
		Node* _root = nullptr;
	};
}

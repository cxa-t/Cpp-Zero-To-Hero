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
					// 这里并不是跳出  而是目前没实现旋转的代码
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

		//void RotateR(Node* parent)
		//{
		//	Node* subL = parent->_left;
		//	Node* subLR = subL->_right;

		//	parent->_left = subLR;
		//	if (subLR)
		//		subLR->_parent = parent;

		//	Node* pParent = parent->_parent;

		//	subL->_right = parent;
		//	parent->_parent = subL;

		//	if (parent == _root)
		//	{
		//		_root = subL;
		//		subL->_parent = nullptr;
		//	}
		//	else
		//	{
		//		if (pParent->_left == parent)
		//		{
		//			pParent->_left = subL;
		//		}
		//		else
		//		{
		//			pParent->_right = subL;
		//		}

		//		subL->_parent = pParent;
		//	}

		//	subL->_bf = 0;
		//	parent->_bf = 0;
		//}

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

			if (parent == _root)
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
			if (pParent == _root)
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

	private:
		Node* _root = nullptr;
	};
}

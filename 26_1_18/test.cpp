#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

//void Test()
//{
//	// 1.malloc/calloc/realloc的区别是什么？
//	int* p2 = (int*)calloc(4, sizeof(int));
//	int* p3 = (int*)realloc(p2, sizeof(int) * 10);
//	
//	// 这里需要free(p2)吗？
//	free(p3);
//}

//void Test()
//{
//	// 动态申请一个int类型的空间
//	int* ptr1 = new int;
//	// 动态申请一个int类型的空间并初始化为10
//	int* ptr2 = new int(10);
//	// 动态申请10个int类型的空间
//	int* ptr3 = new int[10];
//	// 动态申请10个int类型的空间并部分初始化，其余默认为0
//	int* ptr4 = new int[10] {1,2,3,4,5};
//	
//	delete ptr1;
//	delete ptr2;
//	delete[] ptr3;
//	delete[] ptr4;
//}

//struct ListNode
//{
//	int val;
//	ListNode* next;
//
//	ListNode(int x)
//		:val(x)
//		, next(nullptr)
//	{ }
//
//};
//
//int main()
//{
//	ListNode* n1 = new ListNode(1);
//	ListNode* n2 = new ListNode(1);
//	ListNode* n3 = new ListNode(1);
//	ListNode* n4 = new ListNode(1);
//	n1->next = n2;
//	n2->next = n3;
//	n3->next = n4;
//
//	// 释放链表内存 必须遍历释放，不能只 delete n1，否则后面三个节点会内存泄漏
//	ListNode* cur = n1;
//	cur = n1;
//	while (cur != nullptr)
//	{
//		ListNode* nextNode = cur->next; // 先保存下一个节点的地址
//		delete cur;                     // 释放当前节点
//		cur = nextNode;                 // 移动到下一个
//	}
//	
//	// 指针置空，防止悬空指针
//	n1 = n2 = n3 = n4 = nullptr;
//	return 0;
//}

class A
{
public:
	A(int a1 = 0, int a2 = 0)
		:_a1(a1)
		, _a2(a2)
	{ cout << "A(int a1 = 0, int a2 = 0)" << endl; }
	A(const A& aa)
		:_a1(aa._a1)
	{ cout << "A(const A& aa)" << endl;}
	~A()
	{ cout << "~A()" << endl;}
private:
	int _a1 = 1;
	int _a2 = 1;
};

//int main()
//{
//	// 1. 标准的单个对象 new
//	// 调用构造函数 A(1, 0)
//	A* p1 = new A(1);
//	// 调用构造函数 A(2, 2)
//	A* p2 = new A(2, 2);
//	cout << endl;
//
//	// 准备三个已存在的对象
//	A aa1(1, 1);
//	A aa2(2, 2);
//	A aa3(3, 3);
//	// 2. new 对象数组 - 使用【拷贝构造】初始化
//	// 语法：new A[3]{对象1, 对象2, 对象3}
//	// 这里的数组元素是利用 aa1, aa2, aa3 【拷贝构造】出来的
//	// 结果：调用 3 次拷贝构造函数
//	A* p3 = new A[3]{ aa1, aa2, aa3 };
//	cout << endl;
//
//	// 3. new 对象数组 - 使用【匿名对象】初始化
//	// 语法：手动构造 3 个匿名对象 A(1,1)...
//	// 这里的逻辑是：先构造匿名对象，再拷贝构造给数组元素（编译器会优化掉拷贝，直接构造）
//	A* p4 = new A[3]{ A(1,1), A(2,2), A(3,3) };
//	cout << endl;
//
//	// 4. new 对象数组 - 使用【隐式类型转换/列表初始化】 (C++11 最推荐写法)
//	// 语法：{1,1} 会自动匹配构造函数 A(int, int)
//	// 这里的 {1,1} 等价于 A(1,1)，但这是一种隐式类型转换
//	// 结果：编译器直接调用构造函数初始化数组里的每个元素，代码最简洁
//	A* p5 = new A[3]{ {1,1}, {2,2}, {3,3} };
//	cout << endl;
//
//
//	// 内存释放部分 (不要忘记释放数组指针需要用 delete[])
//	delete p1;
//	delete p2;
//	delete[] p3; // 释放 p3 指向的数组，会调用 3 次析构
//	delete[] p4; // 释放 p4 指向的数组，会调用 3 次析构
//	delete[] p5; // 释放 p5 指向的数组，会调用 3 次析构
//
//	return 0;
//}

//int main()
//{
//	// new/delete 和 malloc/free最大区别是 new/delete对于【自定义类型】除了开空间还会调用构造函数和析构函数
//	A* p1 = (A*)malloc(sizeof(A));
//	A* p2 = new A(1);
//	free(p1);
//	delete p2;
//
//	// 内置类型是几乎是一样的
//	int* p3 = (int*)malloc(sizeof(int)); // C
//	int* p4 = new int;
//	free(p3);
//	delete p4;
//
//	A* p5 = (A*)malloc(sizeof(A) * 10);
//	A* p6 = new A[10];
//	free(p5);
//	delete[] p6;
//
//	return 0;
//}

//int main()
//{
//	try
//	{
//		// throw try/catch 
//		void* p1 = new char[1024 * 1024 * 1024];
//		cout << p1 << endl;
//
//		void* p2 = new char[1024 * 1024 * 1024];
//		cout << p2 << endl;
//
//		void* p3 = new char[1024 * 1024 * 1024];
//		cout << p3 << endl;
//	}
//	catch (const exception& e)
//	{
//		cout << e.what() << endl;
//	}
//
//	return 0;
//}

///*
//operator new：该函数实际通过malloc来申请空间，当malloc申请空间成功时直接返回；申请空间
//失败，尝试执行空间不足应对措施，如果改应对措施用户设置了，则继续申请，否则抛异常。
//*/
//void* __CRTDECL operator new(size_t size) _THROW1(_STD bad_alloc)
//{
//	// try to allocate size bytes
//	void* p;
//	while ((p = malloc(size)) == 0)
//	{
//		if (_callnewh(size) == 0)
//		{
//			// report no memory
//			// 如果申请内存失败了，这里会抛出bad_alloc 类型异常
//			static const std::bad_alloc nomem;
//			_RAISE(nomem);
//		}
//	}
//	return (p);
//}

///*
//operator delete: 该函数最终是通过free来释放空间的
//*/
//void operator delete(void* pUserData)
//{
//	_CrtMemBlockHeader* pHead;
//	RTCCALLBACK(_RTC_Free_hook, (pUserData, 0));
//	if (pUserData == NULL)
//		return;
//	_mlock(_HEAP_LOCK); /* block other threads */
//	__TRY
//		/* get a pointer to memory block header */
//		pHead = pHdr(pUserData);
//		/* verify block type */
//		_ASSERTE(_BLOCK_TYPE_IS_VALID(pHead->nBlockUse));
//		_free_dbg(pUserData, pHead->nBlockUse);
//	__FINALLY
//		_munlock(_HEAP_LOCK); /* release other threads */
//	__END_TRY_FINALLY
//	
//	return;
//}

//#define free(p) _free_dbg(p, _NORMAL_BLOCK)

//int main()
//{
//	// 标准的单个对象 new
//	A* p1 = new A[5];
//	delete[] p1;
//
//	return 0;
//}

//int main()
//{
//	int* p1 = new int;
//	free(p1);
//	//delete p1;
//
//	A* p2 = new A;
//	//free(p2);
//	delete p2;
//
//	return 0;
//}

class B
{
public:
private:
	int _b1 = 2;
	int _b2 = 2;
};

int main()
{
	B* p2 = new B[10];
	

	A* p3 = new A[10];
	delete p2;
	delete p3;

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

//class A
//{
//public:
//	A()
//	{
//		++_scount;
//	}
//	A(const A& t)
//	{
//		++_scount;
//	}
//	~A()
//	{
//		--_scount;
//	}
//
//	static int GetACount()
//	{
//		//_a++;
//		return _scount;
//	}
//
//	void func()
//	{
//		cout << _scount << endl;
//		cout << GetACount() << endl;
//	}
//
//private:
//	// 类里面声明
//	static int _scount;
//	//int _a = 1;
//};
//
//// 类外面初始化
//int A::_scount = 0;
//
//int main()
//{
//	//cout << A::_scount << endl;
//	//cout << sizeof(A) << endl;
//	cout << A::GetACount() << endl;
//	A a1, a2;
//
//	{
//		A a3(a1);
//		cout << A::GetACount() << endl;
//	}
//
//	cout << A::GetACount() << endl;
//	//cout << a1.GetACount() << endl;
//	a1.func();
//	return 0;
//}

//class A
//{
//	// 友元声明
//	friend void func(const A& aa, const B& bb);
//private:
//	int _a1 = 1;
//	int _a2 = 2;
//};
//class B
//{
//	// 友元声明
//	friend void func(const A& aa, const B& bb);
//private:
//	int _b1 = 3;
//	int _b2 = 4;
//};
//void func(const A& aa, const B& bb)
//{
//	cout << aa._a1 << endl;
//	cout << bb._b1 << endl;
//}

//int main()
//{
//	A aa;
//	B bb;
//	func(aa, bb);
//
//	return 0;
//}

//// 前置声明，都则A的友元函数声明编译器不认识B
//class B;
//class A
//{
//	// 友元声明
//	friend class B;
//private:
//	int _a1 = 1;
//	int _a2 = 2;
//};
//
//class B
//{
//public:
//	void func1(const A& aa)
//	{
//		cout << aa._a1 << endl;
//		cout << _b1 << endl;
//	}
//	void func2(const A& aa)
//	{
//		cout << aa._a2 << endl;
//		cout << _b2 << endl;
//	}
//private:
//	int _b1 = 3;
//	int _b2 = 4;
//};
//
//int main()
//{
//	return 0;
//}

//class A
//{
//public:
//	class B // B默认就是A的友元
//	{
//	public:
//		void foo(const A& a)
//		{
//			cout << _k << endl; 
//			cout << a._h << endl; 
//		}
//	private:
//		int _b = 1;
//	};
//
//private:
//	static int _k;
//	int _h = 1;
//};
//int A::_k = 1;
//
//int main()
//{
//	cout << sizeof(A) << endl;
//	A::B b;
//
//	A aa;
//	b.foo(aa);
//	return 0;
//}

//class A
//{
//public:
//    A() { cout << "构造 A" << endl; }
//    ~A() { cout << "析构 ~A" << endl; }
//};
//int main()
//{
//    // === 场景 1：有名对象 ===
//    cout << "--- 有名对象开始 ---" << endl;
//    {
//        A a1;
//        cout << "11111" << endl;
//    } // a1 在这里（出了花括号）才死
//    cout << "--- 有名对象结束 ---" << endl << endl;
//
//    // === 场景 2：匿名对象 ===
//    cout << "--- 匿名对象开始 ---" << endl;
//
//    A(); // 这一行：创建 -> 构造 -> 这里的语句结束 -> 立即析构
//
//    cout << "22222" << endl; // 此时对象早就没了
//    cout << "--- 匿名对象结束 ---" << endl;
//
//    return 0;
//}

//class A
//{
//public:
//	A(int a1 = 0, int a2 = 0)
//		:_a1(a1)
//		, _a2(a2)
//	{
//		cout << "A(int a1 = 0, int a2 = 0)" << endl;
//	}
//
//	A(const A& aa)
//		:_a1(aa._a1)
//	{
//		cout << "A(const A& aa)" << endl;
//	}
//
//	~A()
//	{
//		cout << "~A()" << endl;
//	}
//private:
//	int _a1 = 1;
//	int _a2 = 1;
//};
//
//int main()
//{
//	A aa1 = 1;
//	const A& aa2 = 1;
//
//	return 0;
//}


class A
{
public:
	A(int a1 = 0, int a2 = 0)
		:_a1(a1)
		, _a2(a2)
	{
		cout << "A(int a1 = 0, int a2 = 0)" << endl;
	}

	A(const A& aa)
		:_a1(aa._a1)
	{
		cout << "A(const A& aa)" << endl;
	}

	A& operator=(const A& aa)
	{
		cout << "A& operator=(const A& aa)" << endl;
		if (this != &aa)
		{
			_a1 = aa._a1;
		}
		return *this;
	}

	~A()
	{
		//delete _ptr;
		cout << "~A()" << endl;
	}

	void Print()
	{
		cout << "A::Print->" << _a1 << endl;
	}

	A& operator++()
	{
		_a1 += 100;

		return *this;
	}
private:
	int _a1 = 1;
	int _a2 = 1;
};

//int main()
//{
//	A aa1 = 1;
//	const A& aa2 = 1;
//
//	return 0;
//}

//void func(A x) // 参数是值传递
//{
//	// ...
//}
//
//int main()
//{
//	func(A(1)); // 传一个匿名对象过去
//	return 0;
//}

//A f2()
//{
//	A aa(1);
//	++aa;
//	return aa;
//}
//
//int main()
//{
//	f2().Print();
//	cout <<"*********"<< endl << endl;
//	return 0;
//}

//A f2()
//{
//	A aa(1);
//	++aa;
//	return aa;
//}
//
//int main()
//{
//	A ret = f2();
//	ret.Print();
//	cout << "*********" << endl << endl;
//	return 0;
//}

A f2()
{
	A aa(1);
	++aa;
	cout << "##########" << endl;
	return aa;
}

int main()
{
	A ret;
	ret = f2();
	ret.Print();
	cout << "*********" << endl << endl;
	return 0;
}

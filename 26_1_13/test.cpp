#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

//struct ListNode
//{
//public:
//	void Init(int x)
//	{
//		next = nullptr;
//		val = x;
//	}
//private:
//	ListNode* next;
//	int val;
//};
//
//class Stack
//{
//public:
//	// 成员函数
//	void Init(int n = 4);
//private:
//	// 成员变量
//	int* array;
//	int capacity;
//	int top;
//};
//
//// 声明和定义分离，需要指定类域
//void Stack::Init(int n)
//{
//	array = (int*)malloc(sizeof(int) * n);
//	if (nullptr == array)
//	{
//		perror("malloc");
//		exit(-1);
//	}
//	capacity = n;
//	top = 0;
//}

//class Date
//{
//public:
//	//void Init(int year, int month, int day)
//	//{
//	//	_year = year;
//	//	_month = month;
//	//	_day = day;
//	//}
//
//	//// 1.无参构造
//	//Date()
//	//{
//	//	_year = 1960;
//	//	_month = 1;
//	//	_day = 1;
//	//}
//
//	////2.带参数构造
//	//Date(int year, int month, int day)
//	//{
//	//	_year = year;
//	//	_month = month;
//	//	_day = day;
//	//}
//
//	////3.全缺省构造
//	//Date(int year = 1, int month = 1, int day = 1)
//	//{
//	//	_year = year;
//	//	_month = month;
//	//	_day = day;
//	//}
//
//	void Print()
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//
//	//void Print()
//	//{
//	//	cout << this->_year << "-" << this->_month << "-" << this->_day << endl;
//	//}
//
//private:
//	int _year;
//	int _month;
//	int _day;
//};

//typedef int STDataType;
//class Stack
//{
//public:
//	Stack(int n = 4)
//	{
//		_a = (STDataType*)malloc(sizeof(STDataType) * n);
//		if (nullptr == _a)
//		{
//			perror("malloc申请空间失败");
//			return;
//		}
//		_capacity = n;
//		_top = 0;
//	}
//
//	~Stack()
//	{
//		free(_a);
//		_a = nullptr;
//		_capacity = _top = 0;
//	}
//
//	// ...
//private:
//	STDataType * _a;
//	size_t _capacity;
//	size_t _top;
//};
//
//// 两个Stack实现队列
//class MyQueue
//{
//public:
//	//编译器默认生成MyQueue的构造函数调用了Stack的构造，完成了两个成员的初始化
//private:
//	Stack pushst;
//	Stack popst;
//	//int size;
//};

//int main()
//{
//	//Date d1;
//	//Date d2;
//
//	//d1.Print();
//	//d2.Print();
//
//	return 0;
//}

//int main()
//{
//	//MyQueue q1;
//
//	Stack s1;
//	Stack s2;
//
//	return 0;
//}

class Date
{
public:
	Date(int year = 1, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	void Print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	Date(const Date& d)
	{
		cout << "Date(const Date& d)" << endl;
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

private:
	int _year;
	int _month;
	int _day;
};
//
//void func(Date d)
//{
//	cout << "void func(Date d)" << endl;
//}
//
//int main()
//{
//	Date d(2026, 1, 14);
//	func(d);
//	return 0;
//}

//typedef int STDataType;
//class Stack
//{
//public:
//	Stack(int n = 4)
//	{
//		_a = (STDataType*)malloc(sizeof(STDataType) * n);
//		if (nullptr == _a)
//		{
//			perror("malloc申请空间失败");
//			return;
//		}
//		_capacity = n;
//		_top = 0;
//	}
//
//	~Stack()
//	{
//		free(_a);
//		_a = nullptr;
//		_capacity = _top = 0;
//	}
//	
//	void Push(STDataType x)
//	{
//		 if (_top == _capacity)
//		 {
//			 int newcapacity = _capacity * 2;
//			 STDataType * tmp = (STDataType*)realloc(_a, newcapacity * sizeof(STDataType));
//			 if (tmp == NULL)
//			 {
//				 perror("realloc");
//				 exit(-1);
//			 }
//			 _a = tmp;
//			 _capacity = newcapacity;
//		 }
//		 _a[_top++] = x;
//	}
//	Stack(const Stack& st)
//	{
//		_a = (STDataType*)malloc(sizeof(STDataType) * st._capacity);
//		if (nullptr == _a)
//		{
//			perror("malloc");
//			exit(-1);
//		}
//		memcpy(_a, st._a, sizeof(STDataType) * st._top);
//		_top = st._top;
//		_capacity = st._capacity;
//	}
//
//	// ...
//private:
//	STDataType * _a;
//	size_t _capacity;
//	size_t _top;
//};
//
//int main()
//{
//	Stack s1;
//	Stack s2(s1);
//	return 0;
//}

//class A
//{
//public:
//	void func()
//	{
//		cout << "A::func()" << endl;
//	}
//};
//
//typedef void(A::* PF)(); //成员函数指针类型
//
//int main()
//{
//	A aa;
//	// C++规定成员函数要加&才能取到函数指针
//	// 对象调⽤成员函数指针时，使⽤.*运算符
//	PF pf = &A::func;
//	(aa.*pf)();
//	return 0;
//}

int main()
{
	int i, j, k;
	i = j = k = 0;

	Date d1(2026, 1, 14);
	Date d4(2028, 7, 1);
	Date d2(d1);
	Date d3 = d1;

	d2 = d3 = d4;

	return 0;
}
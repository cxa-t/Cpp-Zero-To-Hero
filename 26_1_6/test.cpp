#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
using namespace std;

//class Date
//{
//public:
//	// void Init(Date* const this, int year, int month, int day)
//	void Init(int year, int month, int day)
//	{
//		this->_year = year;
//		this->_month = month;
//		this->_day = day;
//	}
//
//	// void Print(Date* const this)
//	void Print()
//	{
//		cout << this->_year << "/" << this->_month << "/" << _day << endl;
//	}
//
//private:
//	// 这里只是声明，没有开空间
//	int _year;
//	int _month;
//	int _day;
//};
//
//class B
//{
//public:
//	void Print()
//	{
//		//...
//	}
//};
//class C
//{};
//
//int main()
//{
//	// Date类实例化出对象d1和d2
//	Date d1;
//	Date d2;
//
//	// d1.Init(&d1, 2024, 3, 31);
//	d1.Init(2024, 3, 31);
//	// d1.Print(&d1);
//	d1.Print();
//
//	// d2.Init(&d2, 2024, 7, 5);
//	d2.Init(2024, 7, 5);
//	// d2.Print(&d2);
//	d2.Print();
//
//	//A a;
//	//B b;
//	//C c;
//	////cout << sizeof(a) << endl;
//	//cout << &b << endl;
//	//cout << sizeof(b) << endl;
//	//cout << sizeof(c) << endl;
//
//	return 0;
//}

//#include<iostream>
//using namespace std;
//
//class A
//{
//public:
//	void Print()
//	{
//		cout << this << endl;
//		cout << "A::Print()" << endl;
//	}
//private:
//	int _a;
//};
//
//int main()
//{
//	A* p = nullptr;
//	            // mov ecx  p
//	p->Print(); // call  地址
//	//p->_a = 1;
//
//	A aa;
//
//	return 0;
//}

//class Date
//{
//public:
//	// 1.无参构造函数
//	/*Date()
//	{
//		_year = 1;
//		_month = 1;
//		_day = 1;
//	}*/
//  
//
//	// 2.带参构造函数
//	/*Date(int year, int month, int day)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}*/
//
//	// 3.全缺省构造函数
//	/*Date(int year = 1, int month = 1, int day = 1)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}*/
//
//	void Print()
//	{
//		cout << _year << "/" << _month << "/" << _day << endl;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//int main()
//{
//	Date d1;
//	d1.Print();
//
//	/*Date d2(2024, 7, 10);
//	d2.Print();*/
//
//	/*Date d3(2024);
//	d3.Print();*/
//
//	//Date func();
//	//func.Print();
//
//	return 0;
//}

//#include<iostream>
//using namespace std;
//
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
//	// ...
//
//	~Stack()
//	{
//		free(_a);
//		_a = nullptr;
//		_top = _capacity = 0;
//	}
//private:
//	STDataType* _a;
//	size_t _capacity;
//	size_t _top;
//};
//
//// 两个Stack实现队列
//class MyQueue
//{
//public:
//	// 编译器默认生成MyQueue的构造函数调用了Stack的构造，完成了两个成员的初始化
//	// 编译器默认生成MyQueue的析构函数调用了Stack的析构，释放的Stack内部的资源
//	// 显示写析构，也会自动调用Stack的析构
//	~MyQueue()
//	{
//		cout << "~MyQueue()" << endl;
//	}
//private:
//	Stack pushst;
//	Stack popst;
//	//int size;
//};
//
////int main()
////{
////	MyQueue mq;
////	//Stack st1;
////	//Stack st2;
////
////	return 0;
////}
//
//#include<iostream>
//using namespace std;
//// 用最新加了构造和析构的C++版本Stack实现
//bool isValid(const char* s) {
//	Stack st;
//	while (*s)
//	{
//		if (*s == '[' || *s == '(' || *s == '{')
//		{
//			st.Push(*s);
//		}
//		else
//		{
//			// 右括号比左括号多，数量匹配问题
//			if (st.Empty())
//			{
//				return false;
//			}
//			// 栈里面取左括号
//			char top = st.Top();
//			st.Pop();
//
//			// 顺序不匹配
//			if ((*s == ']' && top != '[')
//				|| (*s == '}' && top != '{')
//				|| (*s == ')' && top != '('))
//			{
//				return false;
//			}
//		}
//		++s;
//	}
//	// 栈为空，返回真，说明数量都匹配 左括号多，右括号少匹配问题
//	return st.Empty();
//}
//
//// 用之前C版本Stack实现
//bool isValid(const char* s) {
//	ST st;
//	STInit(&st);
//	while (*s)
//	{
//		// 左括号入栈
//		if (*s == '(' || *s == '[' || *s == '{')
//		{
//			STPush(&st, *s);
//		}
//		else // 右括号取栈顶左括号尝试匹配
//		{
//			if (STEmpty(&st))
//			{
//				STDestroy(&st);
//				return false;
//			}
//			char top = STTop(&st);
//			// 不匹配
//			if ((top == '(' && *s != ')')
//				|| (top == '{' && *s != '}')
//				|| (top == '[' && *s != ']'))
//			{
//				STDestroy(&st);
//				return false;
//			}
//		}
//		++s;
//	}
//
//	// [[[[]]
//	// 栈不为空，说明左括号比右括号多，数量不匹配
//	bool ret = STEmpty(&st);
//	STDestroy(&st);
//
//	return ret;
//}
//
//int main()
//{
//	cout << isValid("[()][]") << endl;
//	cout << isValid("[(])[]") << endl;
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
		cout << _year << "/" << _month << "/" << _day << endl;
	}

	/*int GetYear()
	{
		return _year;
	}*/

	bool operator==(Date d2)
	{
		return _year == d2._year
			&& _month == d2._month
			&& _day == d2._day;
	}

private:
	int _year;
	int _month;
	int _day;

	//int _hour;
};


//bool operator<(Date d1, Date d2)
//{
//
//}

//bool operator==(Date d1, Date d2)
//{
//	return d1._year == d2._year
//		&& d1._month == d2._month
//		&& d1._day == d2._day;
//}

int main()
{
	Date x1(2024, 7, 10);
	Date x2(2024, 7, 11);

	//operator==(x1, x2);
	//x1 == x2;

	x1.operator==(x2);
	x1 == x2;

	return 0;
}
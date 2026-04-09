#define _CRT_SECURE_NO_WARNINGS 1

#include<vector>
#include<iostream>
#include<map>
#include<string>
#include<assert.h>
#include<list>
#include"List.h"
#include<algorithm>

using namespace std;

namespace csa
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		const_iterator begin() const
		{
			return _str;
		}

		const_iterator end() const
		{
			return _str + _size;
		}

		string(const char* str = "")
			:_size(strlen(str))
			, _capacity(_size)
		{
			cout << "string(char* str)-构造" << endl;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		// 拷贝构造
		string(const string& s)
			:_str(nullptr)
		{
			cout << "string(const string& s) -- 拷贝构造" << endl;
			reserve(s._capacity);
			for (auto ch : s)
			{
				push_back(ch);
			}
		}

		void swap(string& ss)
		{
			::swap(_str, ss._str);
			::swap(_size, ss._size);
			::swap(_capacity, ss._capacity);
		}

		// 移动构造
		string(string&& s)
		{
			cout << "string(string&& s) -- 移动构造" << endl;
			// 转移掠夺你的资源
			swap(s);
		}

		string& operator=(const string& s)
		{
			cout << "string& operator=(const string& s) -- 拷贝赋值" <<
				endl;
			if (this != &s)
			{
				_str[0] = '\0';
				_size = 0;
				reserve(s._capacity);
				for (auto ch : s)
				{
					push_back(ch);
				}
			}
			return *this;
		}

		// 移动赋值
		string& operator=(string&& s)
		{
			cout << "string& operator=(string&& s) -- 移动赋值" << endl;
			swap(s);
			return *this;
		}

		~string()
		{
			//cout << "~string() -- 析构" << endl;
			delete[] _str;
			_str = nullptr;
		}

		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}

		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				if (_str)
				{
					strcpy(tmp, _str);
					delete[] _str;
				}
				_str = tmp;
				_capacity = n;
			}
		}

		void push_back(char ch)
		{
			if (_size >= _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity *
					2;
				reserve(newcapacity);
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}

		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}

		const char* c_str() const
		{
			return _str;
		}

		size_t size() const
		{
			return _size;
		}
	private:
		char* _str = nullptr;
		size_t _size = 0;
		size_t _capacity = 0;
	};
}

int y = 0;

auto func2 = []()
	{
		y++;
	};

//int main()
//{
//	// 只能用当前lambda局部域和捕捉的对象和全局对象
//	int a = 0, b = 1, c = 2, d = 3;
//	auto func1 = [a, &b](int x)mutable
//	{
//		// 值捕捉的变量不能修改，引用捕捉的变量可以修改
//		a++;
//		b++;
//		int ret = a + b + x + y;
//		return ret;
//	};
//
//	cout << func1(1) << endl;
//	//func2();
//
//	// 隐式值捕捉
//	// 用了哪些变量就捕捉哪些变量
//	auto func2 = [=]
//	{
//		int ret = a + b + c;
//		return ret;
//	};
//	cout << func2() << endl;
//
//	// 隐式引用捕捉
//	// 用了哪些变量就捕捉哪些变量
//	auto func3 = [&]
//	{
//		a++;
//		c++;
//		//d++;
//	};
//
//	func3();
//	cout << a << " " << b << " " << c << " " << d << endl;
//
//	// 混合捕捉1
//	auto func4 = [&, a, b]
//	{
//		//a++;
//		//b++;
//		c++;
//		d++;
//		return a + b + c + d;
//	};
//
//	func4();
//	cout << a << " " << b << " " << c << " " << d << endl;
//
//	return 0;
//}

class Rate
{
public:
	Rate(double rate)
		: _rate(rate)
	{ }
	double operator()(double money, int year)
	{
		return money * _rate * year;
	}
private:
	double _rate;
};

//int main()
//{
//	double rate = 0.49;
//
//	// lambda
//	auto r2 = [rate](double money, int year) {
//		return money * rate * year;
//	};
//
//	// 函数对象
//	Rate r1(rate);
//	r1(10000, 2);
//	r2(10000, 2);
//
//	auto func1 = [] {
//		cout << "hello world" << endl;
//	};
//
//	func1();
//
//	return 0;
//}

class Person
{
public:
	Person(const char* name = "张三", int age = 1)
		:_name(name)
		, _age(age)
	{ }

	Person(const Person& p) = default;
	Person(Person&& p) = default;

	~Person()
	{ }
private:
	csa::string _name;
	int _age;
};

void func(ostream& out)
{
}

//int main()
//{
//	Person s1;
//	Person s2 = s1;
//	Person s3 = std::move(s1);
//
//	Person s4;
//	//s4 = std::move(s2);
//
//	func(cout);
//
//	return 0;
//}

#include<functional>

int f(int a, int b)
{
	return a + b;
}

struct Functor
{
public:
	int operator() (int a, int b)
	{
		return a + b;
	}
};

class Plus
{
public:
	Plus(int n = 10)
		:_n(n)
	{
	}

	static int plusi(int a, int b)
	{
		return a + b;
	}

	double plusd(double a, double b)
	{
		return (a + b) * _n;
	}

private:
	int _n;
};

//int main()
//{
//	// 包装各种可调用对象
//	function<int(int, int)> f1 = f;
//	function<int(int, int)> f2 = Functor();
//	function<int(int, int)> f3 = [](int a, int b) {return a + b; };
//	cout << f1(1, 1) << endl;
//	cout << f2(1, 1) << endl;
//	cout << f3(1, 1) << endl;
//
//	//(*Fptr)(1, 2);
//
//	// 包装静态成员函数
//	// 成员函数要指定类域并且前面加&才能获取地址
//	function<int(int, int)> f4 = &Plus::plusi;
//	cout << f4(1, 1) << endl;
//
//	function<double(Plus*, double, double)> f5 = &Plus::plusd;
//	Plus pl;
//	cout << f5(&pl, 1.111, 1.1) << endl;
//
//	function<double(Plus, double, double)> f6 = &Plus::plusd;
//	cout << f6(pl, 1.1, 1.1) << endl;
//	cout << f6(Plus(), 1.1, 1.1) << endl;
//
//	function<double(Plus&&, double, double)> f7 = &Plus::plusd;
//	cout << f7(move(pl), 1.1, 1.1) << endl;
//	cout << f7(Plus(), 1.1, 1.1) << endl;
//
//	map<string, function<int(int, int)>> opFuncMap = {
//		{"+", [](int x, int y) {return x + y; }},
//		{"-", [](int x, int y) {return x - y; }},
//		{"*", [](int x, int y) {return x * y; }},
//		{"/", [](int x, int y) {return x / y; }},
//		{"&", [](int x, int y) {return x + y; }},
//		{"|", [](int x, int y) {return x | y; }},
//		{"^", [](int x, int y) {return x ^ y; }}
//	};
//
//	return 0;
//}

using placeholders::_1;
using placeholders::_2;
using placeholders::_3;

int Sub(int a, int b)
{
	return (a - b) * 10;
}

int SubX(int a, int b, int c)
{
	return (a - b - c) * 10;
}

int main()
{
	//auto sub1 = bind(Sub, _1, _2);
	//cout << sub1(10, 5) << endl;

	//auto sub2 = bind(Sub, _2, _1);
	//cout << sub2(10, 5) << endl;

	//// 调整参数个数 （常用）
	//auto sub3 = bind(Sub, 100, _1);
	//cout << sub3(5) << endl;

	//auto sub4 = bind(Sub, _1, 100);
	//cout << sub4(5) << endl;

	//// 分别绑死第123个参数
	//auto sub5 = bind(SubX, 100, _1, _2);
	//cout << sub5(5, 1) << endl;
	//auto sub6 = bind(SubX, _1, 100, _2);
	//cout << sub6(5, 1) << endl;
	//auto sub7 = bind(SubX, _1, _2, 100);
	//cout << sub7(5, 1) << endl;

	//// 成员函数对象进行绑死，就不需要每次都传递了
	///*function<double(Plus&&, double, double)> f6 = &Plus::plusd;
	//Plus pd;
	//cout << f6(move(pd), 1.1, 1.1) << endl;
	//cout << f6(Plus(), 1.1, 1.1) << endl;*/

	//function<double(double, double)> f6 = bind(&Plus::plusd, Plus(), _1, _2);
	//cout << f6(1.1, 1.1) << endl;

	// 计算复利的lambda
	// 复利前一年的利息变成第二年本金
	// (10000*0.02 + 10000)*0.02 + 10000*0.02 + 10000
	// 利率  本金  年限
	auto func1 = [](double rate, double money, int year)->double
		{
			double ret = money;
			for (int i = 0; i < year; i++)
			{
				ret += ret * rate;
			}
			return ret - money;
		};

	//cout << func1(0.05, 10000000, 30) << endl;

	// 绑死一些参数，实现出支持不同年华利率，不同金额和不同年份计算出复利的结算利息
	function<double(double)> func3_1_5 = bind(func1, 0.015, _1, 3);
	function<double(double)> func5_1_5 = bind(func1, 0.015, _1, 5);
	function<double(double)> func10_1_5 = bind(func1, 0.015, _1, 10);

	function<double(double)> func3_2_5 = bind(func1, 0.025, _1, 3);
	function<double(double)> func5_2_5 = bind(func1, 0.025, _1, 5);
	function<double(double)> func10_2_5 = bind(func1, 0.025, _1, 10);

	cout << func3_1_5(1000000) << endl;
	cout << func5_1_5(1000000) << endl;
	cout << func10_1_5(1000000) << endl;

	cout << func3_2_5(1000000) << endl;
	cout << func5_2_5(1000000) << endl;
	cout << func10_2_5(1000000) << endl;

	return 0;
}

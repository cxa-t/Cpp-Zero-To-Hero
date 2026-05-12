#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<list>
#include <assert.h>
using namespace std;

namespace csa
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin() { return _str; }

		iterator end() { return _str + _size; }

		const_iterator begin() const { return _str; }

		const_iterator end() const { return _str + _size; }

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
			cout << "string& operator=(const string& s) -- 拷贝赋值" << endl;
			if (this != &s)
			{
				_str[0] = '\0';
				_size = 0;
				reserve(s._capacity);
				for (auto ch : s)
					push_back(ch);
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
		char* _str = new char('\0');
		size_t _size = 0;
		size_t _capacity = 0;
	};
}

//void ShowList();
//
//template<class T, class ...Args>
//void ShowList(T x, Args&&... args);

//// 0 - N 个参数
//template<class ...Args>
//void Print(Args&&... args)
//{
//	////不支持
//	//for (size_t i = 0; i < sizeof...(args); i++)
//	//{
//	//	cout << args[i] << ' ';
//	//}
//	//cout << endl;
//	ShowList(args...);
//}

////包扩展
////参数包为0个时，匹配这个
//void ShowList()
//{
//	cout << endl;
//}
//
//template<class T, class ...Args>
//void ShowList(T x, Args&&... args)
//{
//	//if (sizeof...(args) == 0)
//	//	return;
//	cout << x << ' ';
//	//args是N个参数的参数包
//	//调用ShowList，第一个参数传给x，剩下N-1个参数传给第二个参数包
//	ShowList(args...);
//}

//void Print()
//{
//	//...
//}
//
//template<class T1>
//void Print(T1&& x1)
//{
//	//...
//}
//
//template<class T1, class T2>
//void Print(T1&& x1, T2&& x2)
//{
//	//...
//}
//
//template<class T1, class T2, class T3>
//void Print(T1&& x1, T2&& x2, T3&& x3)
//{
//	//...
//}
//
//void Print();
//void Print(int&& arg1);
//void Print(int&& arg1, double&& arg2);
//void Print(int&& arg1, string& arg2, double&& arg3);
//void Print(int&& arg1, string&& arg2, double& arg3);

//void ShowList(double x)
//{
//	cout << x << ' ';
//	ShowList();
//}
//void ShowList(string x, double z)
//{
//	cout << x << ' ';
//	ShowList(z);
//}
//void ShowList(int x, string y, double z)
//{
//	cout << x << ' ';
//	ShowList(y,z);
//}
//void Print(int x, string y, double z)
//{
//	ShowList(x, y, z);
//}
//void ShowList()
//{
//	cout << endl;
//}
//template<class T, class ...Args>
//void ShowList(T x, Args&&... args)
//{
//	cout << x << ' ';
//	ShowList(args...);
//}
////编译时递归推导解析参数
//template<class ...Args>
//void Print(Args&&... args)
//{
//	//args是N个参数的参数包
//	//调用ShowList，第一个参数传给x
//	//剩下N-1个参数传给第二个参数包
//	ShowList(args...);
//}


// 包扩展
//template <class T>
//const T& GetArg(const T& x)
//{
//	cout << x << " ";
//	return x;
//}

//template <class T>
//int GetArg(const T& x)
//{
//	cout << x << " ";
//	return 0;
//}
//
//template <class ...Args>
//void Arguments(Args... args)
//{ }
//
//template <class ...Args>
//void Print(Args... args)
//{
//	// 注意GetArg必须返回或者到的对象，这样才能组成参数包给Arguments
//	//Arguments(GetArg(args)...);
//	int a[] = { (GetArg(args),0)... };
//	for (size_t i = 0; i < sizeof...(args); i++)
//	{
//		cout << a[i] << ' ';
//	}
//	cout << endl;
//}

//template <class T>
//void GetArg(const T& x)
//{
//	cout << x << " ";
//}
//
//template <class ...Args>
//void Print(Args... args)
//{
//	int a[sizeof...(args)] = { (GetArg(args),0)... };
//	for (size_t i = 0; i < sizeof...(args); i++)
//	{
//		cout << a[i] << ' ';
//	}
//	cout << endl;
//}

//int main()
//{
//	double x = 2.2;
//	//Print();                   //包里0个参数
//	//Print(1);                  //包里1个参数
//	//Print(1,1.1);              //包里2个参数
//	//Print(1, "csa", 3.3);      //包里3个参数
//	Print(1, string("csa"), x);//包里3个参数
//	Print(1, string("csa"), 2.2);
//	return 0;
//}

//int main()
//{
//	list<csa::string> lt;
//	// 传左值，跟push_back一样，走拷贝构造
//	csa::string s1("111111111111");
//	csa::string s2("111111111111");
//
//	//lt.emplace_back(s1);
//	//cout << "*********************************" << endl;
//	//lt.push_back(s1);
//	//cout << "*********************************" << endl;
//
//	//// 右值，跟push_back一样，走移动构造
//	//lt.emplace_back(move(s1));
//	//cout << "*********************************" << endl;
//	//lt.push_back(move(s2));
//	//cout << "*********************************" << endl;
//	
//	lt.emplace_back("111111111111");
//	cout << "*********************************" << endl;
//	// 直接传参，隐式类型转换
//	lt.push_back("111111111111");
//	cout << "*********************************" << endl;
//
//	return 0;
//}

#include"List.h"

//int main()
//{
//	csa::list<pair<csa::string, int>> lt1;
//	
//	// 构造pair + 拷贝/移动构造pair到list的节点中data上
//	pair<csa::string, int> kv("苹果", 1);
//	
//	//// 跟push_back一样
//	//lt1.emplace_back(kv);
//	//cout << "*********************************" << endl;
//	//lt1.push_back(kv);
//	//cout << "*********************************" << endl;
//	
//	//pair<csa::string, int> kv1("苹果", 2);
//	//// 跟push_back一样
//	//lt1.emplace_back(move(kv));
//	//cout << "*********************************" << endl;
//	//lt1.emplace_back(move(kv1));
//	//cout << "*********************************" << endl;
//
//	// 这里达到的效果是push_back做不到的
//	//lt1.emplace_back({ "苹果", 1 }); // 不支持
//	lt1.emplace_back("苹果", 1 ); // 
//	cout << "*********************************" << endl;
//	lt1.push_back({ "苹果", 1 });
//	cout << "*********************************" << endl;
//
//	return 0;
//}

#include<vector>
#include<algorithm>
#include <functional>

//struct Goods
//{
//	string _name;
//	float _price;
//	int _extent;
//};
//
//int main()
//{
//	//auto add1 = [](int x, int y)->int {return x + y; };
//	//cout << add1(1, 2) << endl;
//	////捕捉列表为空也不能省略
//	////参数为空可以省略
//	////返回值可以省略，可以通过返回对象自己推导
//	////函数体不能省略
//
//
//	//vector<Goods> v = { {"banana",19.1,3}, {"apple", 6.666,1}, {"lemon",33.4,2} };
//	//auto funcprice = [](const Goods& a, const  Goods& b)->bool {return a._price > b._price; };
//	//sort(v.begin(), v.end(), funcprice);
//	//auto funcname = [](const Goods& a, const Goods& b)->bool {return a._name < b._name; };
//	//sort(v.begin(), v.end(), funcname);
//
//	//sort(v.begin(), v.end(), [](const Goods& a, const Goods& b) {return a._extent < b._extent; });
//
//	auto func = [] { cout << "hello csa" << endl; };
//	auto func = [] () { cout << "hello csa" << endl; };
//	func();
//	return 0;
//}

//int y = 0;
//
//int main()
//{
//	//// 只能用当前lambda局部域和捕捉的对象和全局对象
//	//int a = 0, b = 1, c = 2, d = 3;
//	////平时编译器编译一个函数的时候，只会向上找，不会向下找
//	//auto func1 = [a, &b](int x)
//	//{
//	//	// 值捕捉的变量不能修改，引用捕捉的变量可以修改
//	//	//a++;//这里是值捕捉，可以认为是被const修饰的，所以不可以进行修改
//	//	b++;//引用捕捉可以进行修改原数据 此时外部的b变成2
//	//	int ret = a + b + x;//值捕捉正常使用是没问题的
//	//	int count = y;//全局域的变量可以直接使用，不捕捉也能用
//	//	return ret;
//	//};
//	//cout << func1(1) << endl;
//
//	int a = 0, b = 1, c = 2, d = 3;
//	auto functest = [&]()
//		{
//			a++; 
//			b++;
//		};
//	functest();
//	cout << "a=" << a << " " << "b=" << b << " " << "c=" << c << " " << "d=" << d << endl;
//	return 0;
//}

//class Rate
//{
//public:
//	Rate(double rate)
//		: _rate(rate)
//	{ }
//	double operator()(double money, int year) { return money * _rate * year; }
//private:
//	double _rate;
//};
//
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
//	return 0;
//}

//class Person
//{
//public:
//	Person(const char* name = "张三", int age = 1)
//		:_name(name)
//		, _age(age)
//	{ }
//	Person(const Person& p) = default;
//	Person(Person&& p) = default;
//	Person& operator=(Person&& p) = default;
//	Person& operator=(const Person& p) = default;
//	~Person() {}
//private:
//	csa::string _name;
//	int _age;
//};
//
//void func(const ostream& out)
//{ }
//
//int main()
//{
//	func(cout);
//	Person s1;
//	Person s2 = s1;
//	Person s3 = std::move(s1);
//	Person s4;
//	s4 = s2;
//	Person s5;
//	s5 = std::move(s2);
//	
//	return 0;
//}

class Plus
{
public:
	Plus(int n = 10)
		:_n(n)
	{ }
	static int plusi(int a, int b) { return a + b; }
	double plusd(double a, double b) { return (a + b) * _n; }
private:
	int _n;
};
//
//int main()
//{
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
//	return 0;
//}

using placeholders::_1;
using placeholders::_2;
using placeholders::_3;

int Sub(int a, int b) { return (a - b) * 10; }

int SubX(int a, int b, int c) { return (a - b - c) * 10; }

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
	//function<double(Plus&&, double, double)> f6 = &Plus::plusd;
	//Plus pd;
	//cout << f6(move(pd), 1.1, 1.1) << endl;
	//cout << f6(Plus(), 1.1, 1.1) << endl;

	//function<double(double, double)> f6 = bind(&Plus::plusd, Plus(), _1, _2);
	//cout << f6(1.1, 1.1) << endl;

	//Plus myObj(20); // 提前准备好一个对象
	//function<double(double, double)> f6 = bind(&Plus::plusd, &myObj, _1, _2);
	//cout << f6(1.1, 1.1) << endl;

	//// 计算复利的lambda
	//// 复利前一年的利息变成第二年本金
	//// (10000*0.02 + 10000)*0.02 + 10000*0.02 + 10000
	//// 利率  本金  年限
	//auto func1 = [](double rate, double money, int year)->double
	//	{
	//		double ret = money;
	//		for (int i = 0; i < year; i++)
	//		{
	//			ret += ret * rate;
	//		}
	//		return ret - money;
	//	};

	//cout << func1(0.05, 10000000, 30) << endl;

	//// 绑死一些参数，实现出支持不同年华利率，不同金额和不同年份计算出复利的结算利息
	//function<double(double)> func3_1_5 = bind(func1, 0.015, _1, 3);
	//function<double(double)> func5_1_5 = bind(func1, 0.015, _1, 5);
	//function<double(double)> func10_1_5 = bind(func1, 0.015, _1, 10);

	//function<double(double)> func3_2_5 = bind(func1, 0.025, _1, 3);
	//function<double(double)> func5_2_5 = bind(func1, 0.025, _1, 5);
	//function<double(double)> func10_2_5 = bind(func1, 0.025, _1, 10);

	//cout << func3_1_5(1000000) << endl;
	//cout << func5_1_5(1000000) << endl;
	//cout << func10_1_5(1000000) << endl;

	//cout << func3_2_5(1000000) << endl;
	//cout << func5_2_5(1000000) << endl;
	//cout << func10_2_5(1000000) << endl;

	auto funclu = [](double rate, double money, int year)
		{
			double ret = money;
			for (int i = 0; i < year; i++)
			{
				ret += ret * rate;
			}
			return ret - money;
		};
	// 绑死一些参数，实现出支持不同年华利率，不同金额和不同年份计算出复利的结算利息
	function<double(double)> func3_1_5 = bind(funclu, 0.015, _1, 3);
	function<double(double)> func5_1_5 = bind(funclu, 0.015, _1, 5);
	function<double(double)> func10_1_5 = bind(funclu, 0.015, _1, 10);

	function<double(double)> func3_2_5 = bind(funclu, 0.025, _1, 3);
	function<double(double)> func5_2_5 = bind(funclu, 0.025, _1, 5);
	function<double(double)> func10_2_5 = bind(funclu, 0.025, _1, 10);
	cout << func3_1_5(1000000) << endl;
	cout << func5_1_5(1000000) << endl;
	cout << func10_1_5(1000000) << endl;
	cout << func3_2_5(1000000) << endl;
	cout << func5_2_5(1000000) << endl;
	cout << func10_2_5(1000000) << endl;
	return 0;
}
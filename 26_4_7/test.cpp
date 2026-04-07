#define _CRT_SECURE_NO_WARNINGS 1

#include<vector>
#include<iostream>
#include<map>
#include<string>
#include<assert.h>
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


#include<list>
#include"List.h"

//int main()
//{
//	csa::list<csa::string> lt;
//	csa::string s1("11111111111");
//	lt.push_back(s1);
//
//	csa::string s2("33333333333");
//	lt.push_back(move(s2));
//
//	lt.push_back("22222222222");
//
//	return 0;
//}

//template <class ...Args>
//void Print(Args&&... args)
//{
//	// 不支持
//	for (size_t i = 0; i < sizeof...(args); i++)
//	{
//		// 不支持
//		cout << args[i] << " ";
//	}
//	cout << endl;
//}

//template <class ...Args>
//void Print(Args&&... args)
//{
//	// 不支持
//	for (auto&& e : args...)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//}

// 包扩展（解析出参数包的内容）
//void ShowList()
//{
//	// 编译器时递归的终止条件，参数包是0个时，直接匹配这个函数
//	cout << endl;
//}
//
//template <class T, class ...Args>
//void ShowList(T&& x, Args&&... args)
//{
//	// 运行时
//	/*if (sizeof...(args) == 0)
//		return;*/
//
//	cout << x << " ";
//	// args是N个参数的参数包
//	// 调用ShowList，参数包的第一个传给x，剩下N-1传给第二个参数包
//	ShowList(args...);
//}

//template <class ...Args>
//void Print(Args&&... args)
//{
//	ShowList(args...);
//}


// 包扩展
//template <class T>
//const T& GetArg(const T& x)
//{
//	cout << x << " ";
//	return x;
//}

template <class T>
int GetArg(const T& x)
{
	cout << x << " ";
	return 0;
}

template <class ...Args>
void Arguments(Args... args)
{
}

template <class ...Args>
void Print(Args... args)
{
	// 注意GetArg必须返回或者到的对象，这样才能组成参数包给Arguments
	//Arguments(GetArg(args)...);
}

//void Print(int x, string y, double z)
//{
// Arguments(GetArg(x), GetArg(y), GetArg(z));
//}

//int main()
//{
//	double x = 2.2;
//	Print(); // 包里有0个参数
//	Print(1); // 包里有1个参数
//	Print(1, string("xxxxx")); // 包里有2个参数
//	Print(1.1, string("xxxxx"), x); // 包里有3个参数
//
//	return 0;
//}

//int main()
//{
//	list<csa::string> lt;
//	// 传左值，跟push_back一样，走拷贝构造
//	csa::string s1("111111111111");
//	csa::string s2("111111111111");
//
//	lt.emplace_back(s1);
//	cout << "*********************************" << endl;
//
//	lt.push_back(s1);
//	cout << "*********************************" << endl;
//
//	// 右值，跟push_back一样，走移动构造
//	lt.emplace_back(move(s1));
//	cout << "*********************************" << endl;
//
//	lt.push_back(move(s2));
//	cout << "*********************************" << endl;
//	
//	lt.emplace_back("111111111111");
//	cout << "*********************************" << endl;
//
//	// 直接传参，隐式类型转换
//	lt.push_back("111111111111");
//	cout << "*********************************" << endl;
//
//	return 0;
//}

//int main()
//{
//	csa::list<pair<csa::string, int>> lt1;
//	// 跟push_back一样
//	// 构造pair + 拷贝/移动构造pair到list的节点中data上
//	pair<csa::string, int> kv("苹果", 1);
//	lt1.emplace_back(kv);
//	cout << "*********************************" << endl;
//
//	// 跟push_back一样
//	lt1.emplace_back(move(kv));
//	cout << "*********************************" << endl;
//
//	// 这里达到的效果是push_back做不到的
//	//lt1.emplace_back({ "苹果", 1 }); // 不支持
//	lt1.emplace_back("苹果", 1 ); // 
//	cout << "*********************************" << endl;
//
//	lt1.push_back({ "苹果", 1 });
//	cout << "*********************************" << endl;
//
//	return 0;
//}

//int main()
//{
//	auto add1 = [](int x, int y)->int {return x + y; };
//	cout << add1(1, 2) << endl;
//
//	// 1、捕捉为空也不能省略
//	// 2、参数为空可以省略
//	// 3、返回值可以省略，可以通过返回对象自动推导
//	// 4、函数体不能省略
//	auto func1 = []
//	{
//		cout << "hello csa" << endl;
//		return 0;
//	};
//
//	func1();
//
//	return 0;
//}

#include<algorithm>

struct Goods
{
	string _name;  // 名字
	double _price; // 价格
	int _evaluate; // 评价
	// ...

	Goods(const char* str, double price, int evaluate)
		:_name(str)
		, _price(price)
		, _evaluate(evaluate)
	{
	}
};

struct Compare1
{
	bool operator()(const Goods& gl, const Goods& gr)
	{
		return gl._price < gr._price;
	}
};

struct Compare2
{
	bool operator()(const Goods& gl, const Goods& gr)
	{
		return gl._price > gr._price;
	}
};

int main()
{
	vector<Goods> v = { { "苹果", 2.1, 5 }, { "香蕉", 3, 4 }, { "橙子", 2.2, 3}, { "菠萝", 1.5, 4 } };
	// 类似这样的场景，我们实现仿函数对象或者函数指针支持商品中
	// 不同项的比较，相对还是比较麻烦的，那么这里lambda就很好用了

	// 价格升序
	//sort(v.begin(), v.end(), Compare1());

	// 价格降序
	//sort(v.begin(), v.end(), Compare2());

	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2) {
		return g1._price < g2._price; });

	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2) {
		return g1._price > g2._price; });

	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2) {
		return g1._evaluate < g2._evaluate; });

	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2) {
		return g1._evaluate > g2._evaluate; });

	return 0;
}
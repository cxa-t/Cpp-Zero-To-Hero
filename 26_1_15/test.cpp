#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

//class Date
//{
//	friend ostream& operator<<(ostream& out, const Date& d);
//	friend istream& operator>>(istream& in, const Date& d);
//public:
//	Date(int year = 1900, int month = 1, int day = 1)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	void Print() const
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//	Date * operator&()
//	{
//		return this;
//		// return nullptr;
//	}
//	const Date * operator&()const
//	{
//		return this;
//		// return nullptr;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//ostream& operator<<(ostream& out, const Date& d)
//{
//	out << d._year << "-" << d._month << "-" << d._day << endl;
//	return out;
//}
//istream& operator>>(istream& in, const Date& d)
//{
//	cout << "请依次输入年月日:>";
//	in >> d._year >> d._month >> d._day;
//	return in;
//}
//int main()
//{
//	Date d1, d2;
//	cin >> d1 >> d2;
//	//cout << d1 << d2 << endl;
//	//Date d1(2025,1,2);
//	//d1.Print();
//	//const Date d2(2026, 2, 3);
//	//d2.Print();
//	return 0;
//}

//class Date
//{
//public:
//	// 单参数构造函数
//	Date(int year)
//	{
//		_year = year;
//		_month = 1;
//		_day = 1;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//int main() 
//{
//    Date d1(2024); // 1. 正常的构造调用
//    // 2. 隐式类型转换发生在这里
//    Date d2 = 2025; // 写法虽然像赋值，但本质是构造
//    return 0;
//}

//class Date
//{
//public:
//    // 多参数构造函数
//    Date(int year, int month)
//    {
//        _year = year;
//        _month = month;
//        _day = 1;
//    }
//    // ...
//private:
//    int _year;
//    int _month;
//    int _day;
//};
//
//int main()
//{
//    // C++11 支持这种写法
//    Date d1 = { 2024, 7 };
//}

class Time
{
public:
	Time(int hour)
	{
		_hour = hour;
	}
private:
	int _hour;
};
//
//class Date
//{
//public:
//	Date(int year,int month, int day)
//		:_year(year)
//		,_month(month)
//		,_day(day)
//		
//	{ }
//
//private:
//	int _year;
//	int _month;
//	int _day;
//
//	// error C2530: “Date::_ref”: 必须初始化引用
//	// error C2789 : “Date::_flag” : 必须初始化常量限定类型的对象
//	// error C2512 : “Time”: 没有合适的默认构造函数可用
//	int& _ref;
//	const int _flag;
//	Time _t;
//};

//class Date
//{
//public:
//	Date(int year = 1900, int month = 1, int day = 1)
//		: _year(year)
//		, _month(month)
//	{}
//	void Print() const
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//private:
//	//c++11
//	//缺省值->给初始化列表用
//	int _year = 1900;
//	int _month = 1;
//	int _day;
//	//Time _t;
//};
//
//int main()
//{
//	Date d1(2026, 4, 15);
//	d1.Print();
//	return 0;
//}

class A 
{
public:
    A(int a)
        : _a1(a)
        , _a2(_a1) // 这里的意图是用 _a1 初始化 _a2
    { }
    void Print() 
    {
        cout << _a1 << " " << _a2 << endl;
    }
private:
    int _a2; // 注意：_a2 先声明！
    int _a1;
};

int main() 
{
    A obj(1);
    obj.Print();
    return 0;
}
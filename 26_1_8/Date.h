#pragma once

#include<iostream>
using namespace std;

class Date
{
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);

public:
	//默认构造函数
	Date(int year = 1900, int month = 1, int day = 1);
	//析构函数
	~Date();
	//拷贝构造
	Date(const Date& d);

	void Print()const;

	//内联函数
	inline int GetDay(int year, int month)const
	{
		//频繁调用  放至静态区
		static const int dayArray[13] = { -1,31,28,31,30,31,30,31,31,30,31,30,31 };
		if (month == 2 && (year % 4 == 0 && year % 100 != 0 || year % 400 == 0))
			return 29;
		return dayArray[month];
	}

	bool checkDate() const;

	bool operator>(const Date& d)const;
	bool operator>=(const Date& d)const;
	bool operator<(const Date& d)const;
	bool operator<=(const Date& d)const;
	bool operator==(const Date& d)const;
	bool operator!=(const Date& d)const;

	Date& operator=(const Date& d);
	Date& operator+=(int day);
	Date operator+(int day);
	Date operator-(int day);
	Date& operator-=(int day);

	// 前置++
	Date& operator++();
	// 后置++
	Date operator++(int);
	// 后置--
	Date operator--(int);
	// 前置--
	Date& operator--();

	int operator-(const Date& d);

private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& out, const Date& d);
istream& operator>>(istream& in, Date& d);
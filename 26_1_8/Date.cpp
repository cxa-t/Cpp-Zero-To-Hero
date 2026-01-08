#define _CRT_SECURE_NO_WARNINGS 1

#include "Date.h"

bool Date::checkDate()const
{
	if (_month < 0 || _month >12 || _day < 1 || _day > GetDay(_year, _month))
		return false;
	return true;
}

Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
}

Date::~Date()
{
	_year = 0;
	_month = 0;
	_day = 0;
}

Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

void Date::Print()const
{
	cout << _year << "/" << _month << "/" << _day << endl;
}

Date& Date::operator=(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
	return *this;
}

Date& Date::operator+=(int day)
{
	if (day < 0)
	{
		return *this -= (-day);
	}
	_day += day;
	while (_day > GetDay(_year, _month))
	{
		_day -= GetDay(_year, _month);
		_month++;
		if (_month > 12)
		{
			_month = 1;
			_year++;
		}
	}
	return *this;
}

Date& Date::operator-=(int day)
{
	if (day < 0)
	{
		return *this += (-day);
	}
	_day -= day;
	while (_day <= 0)
	{
		_month--;
		if (_month <= 0)
		{
			_month = 12;
			_year--;
		}
		_day += GetDay(_year, _month);
	}
	return *this;
}

Date Date::operator+(int day)
{
	Date tmp = *this;
	tmp += day;
	return tmp;
}

Date Date::operator-(int day)
{
	Date tmp = *this;
	tmp -= day;
	return tmp;
}

bool Date::operator>(const Date& d)const
{
	if (_year != d._year)
		return _year > d._year;
	if (_month != d._month)
		return _month > d._month;
	return _day > d._day;
}

bool Date::operator<(const Date& d)const
{
	if (_year != d._year)
		return _year < d._year;
	if (_month != d._month)
		return _month < d._month;
	return _day < d._day;
}

bool Date::operator==(const Date& d)const
{
	return _year == d._year && _month == d._month && _day == d._day;
}

bool Date::operator>=(const Date& d)const
{
	return *this == d || *this > d;
}

bool Date::operator<=(const Date& d)const
{
	return *this == d || *this < d;
}

bool Date::operator!=(const Date& d)const
{
	return !(*this == d);
}

//后置++
Date Date::operator++(int)
{
	Date tmp = *this;
	*this += 1;
	return tmp;
}

Date& Date::operator++()
{
	*this += 1;
	return *this;
}

Date Date::operator--(int)
{
	Date tmp = *this;
	*this -= 1;
	return tmp;
}

Date& Date::operator--()
{
	*this -= 1;
	return *this;
}

int Date::operator-(const Date& d)
{
	Date min = *this;
	Date max = d;
	int flag = 1;
	if (min > max)
	{
		min = d;
		max = *this;
		flag = -1;
	}
	int n = 0;
	while (min != max)
	{
		++min;
		++n;
	}
	return n * flag;
}

ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "/" << d._month << "/" << d._day << endl;
	return out;
}

istream& operator>>(istream& in, Date& d)
{
	while (1)
	{
		cout << "请依次输入年月日:>";
		in >> d._year >> d._month >> d._day;
		if (!d.checkDate())
		{
			cout << "输入日期不合法\n";
			d.Print();
			cout << "重新输入！\n";
		}
		else
		{
			break;
		}
	}
	return in;
}

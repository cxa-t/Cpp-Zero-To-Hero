#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void test_heap() 
{
    vector<int> data = { 3, 1, 4, 1, 5, 9, 2, 6, 5 };
    for (auto e : data)
        cout << e << " ";
    cout << endl;

    // 第一步：将普通数组转化为最大堆 O(N)
    make_heap(data.begin(), data.end());
    for (auto e : data)
        cout << e << " ";
    cout << endl;

    // 第二步：执行堆排序 O(N log N)
    // 注意：sort_heap 要求传入的区间必须已经是一个堆！
    sort_heap(data.begin(), data.end());

    for (auto e : data)
        cout << e << " ";
    cout << endl;
}

//template<class T>
//struct Less
//{
//    bool operator()(const T& x, const T& y) const
//    {
//        return *x < *y;
//    }
//};

void testvector1()
{
    vector<int*> vp;
    vp.push_back(new int(1));
    vp.push_back(new int(4));
    vp.push_back(new int(3));
    vp.push_back(new int(9));
    
    // 使用默认的比较方式（隐式使用 std::less<int*>）
    //sort(vp.begin(), vp.end(),Less<int*>());

    for (int* p : vp) 
        std::cout << *p << " ";
    cout << endl;
}

template<class T, size_t size = 10>
class array
{
public:
    T& operator[](size_t index) { return _array[index]; }
    const T& operator[](size_t index)const { return _array[index]; }
    size_t size() const { return _size; }
    bool empty() const { return _size == 0; }
private:
    T _array[size];
    size_t _size;
};


class Date
{
    friend ostream& operator<<(ostream& _cout, const Date& d);
public:
    Date(int year = 1900, int month = 1, int day = 1)
        : _year(year)
        , _month(month)
        , _day(day)
    { }

    bool operator<(const Date& d)const
    {
        return (_year < d._year) ||
            (_year == d._year && _month < d._month) ||
            (_year == d._year && _month == d._month && _day < d._day);
    }

    bool operator>(const Date& d)const
    {
        return (_year > d._year) ||
            (_year == d._year && _month > d._month) ||
            (_year == d._year && _month == d._month && _day > d._day);
    }
private:
    int _year;
    int _month;
    int _day;
};

template<class T>
bool LessFunc(const T& left, const T& right)
{
    return *left < *right;
}

//模板特化
template<>
bool LessFunc<Date*>(Date* const& left, Date* const& right)
{
    return *left < *right;
}
//模板特化
template<>
bool LessFunc<const Date*>(const Date* const& left, const Date* const& right)
{
    return *left < *right;
}

//int main()
//{
//	cout << LessFunc(1, 2) << endl; // 可以比较，结果正确
//
//	Date d1(2022, 7, 7);
//	Date d2(2022, 7, 8);
//	cout << LessFunc(d1, d2) << endl; // 可以比较，结果正确
//
//	Date* p1 = &d1;
//	Date* p2 = &d2;
//	cout << LessFunc(p1, p2) << endl; // 可以比较，结果错误
//
//	const Date* p3 = &d1;
//	const Date* p4 = &d2;
//	cout << LessFunc(p3, p4) << endl; // 可以比较，结果错误
//
//	const int i = 0;
//	int const j = 0;
//	const int& rx = i;
//	int const& ry = i;
//
//	return 0;
//}


//template<class T1, class T2>
//class Data
//{
//public:
//    Data() { cout << "Data<T1, T2>" << endl; }
//private:
//    T1 _d1;
//    T2 _d2;
//};
//
////全特化
//template<>
//class Data<int, char>
//{
//public:
//    Data() { cout << "class Data<int, char>" << endl; }
//};
//
//// 偏特化/半特化
//template<class T1>
//class Data<T1, double>
//{
//public:
//    Data() { cout << "Data<T1, double>" << endl; }
//};
//
//template<class T1>
//class Data<T1, char>
//{
//public:
//    Data() { cout << "Data<T1, char>" << endl; }
//};
//
//// 偏特化，传的类型是指针
//template <typename T1, typename T2>
//class Data <T1*, T2*>
//{
//public:
//    Data() { cout << "Data<T1*, T2*>" << endl; }
//};
//
//template <typename T1, typename T2>
//class Data <T1&, T2&>
//{
//public:
//    Data() { cout << "Data<T1&, T2&>" << endl; }
//};
//
//
//template <typename T1, typename T2>
//class Data <T1&, T2*>
//{
//public:
//    Data()
//    {
//        cout << "Data<T1&, T2*>" << endl;
//
//        int a = 0;
//        T1& x = a;
//        T2* y = &a;
//        T1 z = a;
//
//        cout << typeid(x).name() << endl;
//        cout << typeid(y).name() << endl;
//    }
//
//    void Push(const T1& x) {}
//};


//int main()
//{
//    //test_heap();
//    testvector1();
//	return 0;
//}

#include "Data.h"

int main()
{
    //1. 完美运行：匹配全特化版本 (实现就在 .h 里，没问题)
    Data<int, char> d1;

    //2. 完美运行：匹配偏特化版本 (实现就在 .h 里，没问题)
    int a = 10;
    Data<int*, int*> d2;

    //3. 完美运行：匹配基础模板。
    // main.cpp 看不到实现，但在链接时，链接器在 Data.cpp 里找到了预先生成的 <int, int> 机器码！
    Data<int, int> d3;

    //4. 完美运行：匹配基础模板。链接器同样找到了预先生成的 <double, int> 机器码。
    Data<double, int> d4;

    // 5. 链接错误 (LNK2019 / undefined reference)：
    // Data<float, float> d5;
    // 报错原因：匹配基础模板。但 Data.cpp 末尾没有写 `template class Data<float, float>;`
    // 链接器翻遍了所有文件，找不到对应的实现，当场罢工。

    return 0;
}

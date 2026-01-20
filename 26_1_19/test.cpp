#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

//class A
//{
//public:
//	A(int a = 0)
//		: _a(a)
//	{ cout << "A():" << this << endl; }
//	~A()
//	{ cout << "~A():" << this << endl; }
//private:
//	int _a;
//};
//
//int main()
//{
//	A* p1 = new A(1);
//	delete p1;
//
//	A* p2 = (A*)operator new(sizeof(A));
//	new(p2)A(1);
//
//	p2->~A();
//	operator delete(p2);
//
//	return 0;
//}

//template<class T>
//void Swap(T& t1, T& t2)
//{
//	T tmp = t1;
//	t1 = t2;
//	t2 = tmp;
//}
//
//void Swap(int& t1, int& t2)
//{
//	int tmp = t1;
//	t1 = t2;
//	t2 = tmp;
//}
//
//void Swap(double& t1, double& t2)
//{
//	double tmp = t1;
//	t1 = t2;
//	t2 = tmp;
//}
//
//void Swap(char& t1, char& t2)
//{
//	char tmp = t1;
//	t1 = t2;
//	t2 = tmp;
//}
//
//int main()
//{
//	int i1 = 10;
//	int i2 = 20;
//	char c1 = 'x';
//	char c2 = 'a';
//	double d1 = 1.1;
//	double d2 = 2.2;
//	Swap(i1, i2);
//	Swap(d1, d2);
//	Swap(c1, c2);
//
//	return 0;
//}

//template<class T>
//T Add(const T& left, const T& right)
//{
//	return left + right;
//}
//int main()
//{
//	int a1 = 10, a2 = 20;
//	double d1 = 10.0, d2 = 20.0;
//
//	/*
//	该语句不能通过编译，因为在编译期间，当编译器看到该实例化时，需要推演其实参类型通过实参a1将T推演为int，
//	通过实参d1将T推演为double类型，但模板参数列表中只有一个T，编译器无法确定此处到底该将T确定为int 或者 
//	double类型而报错注意：在模板中，编译器一般不会进行类型转换操作，因为一旦转化出问题，编译器就需要背黑锅
//	*/
//	//Add(a1, d1);
//
//	Add(a1, (int)d1);
//	Add<int>(a1, d1);
//	return 0;
//}

//template<class T>
//T* func(int n)
//{
//	return new T[n];
//}
//int main()
//{
//	double* p = func<double>(10);
//	return 0;
//}

//template<class T>
//T Add(const T& x, const T& y)
//{
//	return x + y;
//}

//// 通用加法函数
//template<class T1, class T2>
//T1 Add(T1 left, T2 right)
//{
//	return left + right;
//}
//int Add(int x, int y)
//{
//	return (x + y) * 10;
//}
//int main()
//{
//	cout << Add(2, 3.0) << endl;
//	return 0;
//}


template<class T>
class Stack
{
public:
	Stack(int n = 4)
		:_array(new T[n])
		,_capacity(n)
		,_size(0)
	{ }
	~Stack()
	{
		delete[] _array;
		_size = _capacity = 0;
	}
	void Push(const T& x);
private:
	T* _array;
	size_t _size;
	size_t _capacity;
};
template<class T>
void Stack<T>::Push(const T& x)
{
	if (_size == _capacity)
	{
		T* tmp = new T[_capacity * 2];
		memcpy(tmp, _array, sizeof(T) * _size);
		delete[] _array;
		_capacity *= 2;
		_array = tmp;
	}
	_array[_size++] = x;
}

int main()
{
	//类模板都必须显式实例化
	Stack<int> s1;//char
	s1.Push(30);
	Stack<char> s2;//int
	s2.Push('W');
	s2.Push('+');

	return 0;
}

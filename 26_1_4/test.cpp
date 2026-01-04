#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

//int main()
//{
//	std::cout << "CXA" << std::endl;
//	return 0;
//}

////把标准命名空间的全部展开
//using namespace std;
//
//int main()
//{
//	cout << "CXA" << endl;
//	return  0;
//}

//int height = 190;
//namespace cxa
//{
//	namespace csa
//	{
//		int height = 170;
//
//		int ADD(int x, int y)
//		{
//			return x * y;
//		}
//	}
//
//	int height = 180;
//
//	int ADD(int x, int y)
//	{
//		return x + y;
//	}
//}
//using namespace std;
//int main()
//{
//	cout << height << endl;
//	cout << cxa::height << endl;
//	cout << cxa::ADD(2, 3) << endl;
//	cout << cxa::csa::ADD(2, 3) << endl;
//	return 0;
//}

//using namespace std;
//int main()
//{
//	//竞赛中加上上面这三行代码可以提升io效率
//	ios_base::sync_with_stdio(false);
//	cin.tie(nullptr);
//	cout.tie(nullptr);
//
//	int a = 0;
//	float b = 3.52f;
//	char c = 'x';
//	printf("%d %lf %c\n", a, b, c);
//	cout << a << " " << b << " " << c << endl;
//	
//	cin >> a;
//	cin >> b >> c;
//	cout << a << " ";
//	cout << b << " " << c << endl;
//	return 0;
//}

//void func(int c = 0)
//{
//	cout << c << endl;
//}
//
////全缺省
//void func1(int a = 10, int b = 20, int c = 30)
//{
//	cout << a << " " << b << " " << c << endl;
//}
//
////半缺省
////C++规定半缺省参数必须从右往左依次连续缺省，不能间隔跳跃给缺省值。
//void func2(int a, int b = 20, int c = 30)
//{
//	cout << a << " " << b << " " << c << endl;
//}
//
//int main()
//{
//	func();
//	func(20);
//
//	//带缺省参数的函数调⽤，C++规定必须从左到右依次给实参，不能跳跃给实参。
//	func1();
//	func1(15);
//	func1(15, 25);
//	func1(15, 25, 35);
//	
//	//func2();
//	func2(15);
//	func2(15, 25);
//	func2(15, 25, 35);
//
//	return 0;
//}

//1.参数类型不同 其他相同
int Add(int x, int y)
{
	cout << "int Add(int x, int y)" << endl;
	return x + y;
}

double Add(double x, double y)
{
	cout << "double Add(double x, double y)" << endl;
	return x + y;
}

//2.参数个数不同
void func()
{
	cout << "func()" << endl;
}

void func(int a)
{
	cout << "func(int a)" << endl;
}

//3.参数顺序不同
void func1(int x, float y)
{
	cout << "void func1(int x, float y)" << endl;
}

void func1(float y, int x)
{
	cout << "void func1(float y, int x)" << endl;
}

//以下两个函数构成重载，但会报错，因为空调用时两个都可以匹配，编译器也不知道调用哪个
void f1()
{
	cout << "f()" << endl;
}

void f1(int a = 10)
{
	cout << "f(int a)" << endl;
}

int main()
{
	cout << Add(1, 2) << endl;
	cout << Add(1.0, 2.0) << endl;
	func();
	func(10);
	func1(1.0, 2);
	func1(2, 1.0);

	return 0;
}
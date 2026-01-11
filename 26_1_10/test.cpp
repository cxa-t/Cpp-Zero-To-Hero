#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

//#include <stdio.h>
//int main()
//{
//	printf("hello world!\n");
//	return 0;
//}

//int main()
//{
//	cout << "hello world!" << endl;
//	return 0;
//}

namespace marathon
{
	namespace extreme
	{
		int Add(int x, int y)
		{
			return x + y;
		}

		int rand = 300;
	}

	int Add(int x, int y)
	{
		return x + y;
	}

	int rand = 100;
}

//using marathon::Add;
////using namespace marathon;
//int main()
//{
//	//1.局部展开 using marathon::Add;
//	printf("%d\n", Add(2, 3));
//	//2.加上域限定 marathon::
//	printf("%d\n", marathon::Add(2, 3));
//	//3.全局展开 using namespace marathon;
//	printf("%d\n", Add(2, 3));
//	return 0;
//}

//int main()
//{
//	int a = 0;
//	double b = 0.1314;
//	char c = 'c';
//	
//	cout << a << " " << b << " " << c << endl;
//	std::cout << a << " " << b << " " << c << std::endl;
//
//	//scanf("%d%lf", &a, &b);
//	//printf("%d %lf\n", a, b);
//	
//	// 可以自动识别变量的类型
//	cin >> a >> b >> c;
//	cout << a << b << " " << c << endl;
//	
//	return 0;
//}

//int main()
//{
//	ios_base::sync_with_stdio(false);
//	cin.tie(nullptr);
//	cout.tie(nullptr);
//	
//	return 0;
//}

//void Func(int a = 10, int b = 20) 
//{
//	cout << a + b << endl;
//}
//
//int main() 
//{
//	Func();     // 使用默认值：10 + 20
//	Func(1);    // a=1, b=20
//	Func(1, 2); // a=1, b=2
//	return 0;
//}

//// 1、参数类型不同
//int Add(int left, int right)
//{
//	cout << "int Add(int left, int right)" << endl;
//	return left + right;
//}
//double Add(double left, double right)
//{
//	cout << "double Add(double left, double right)" << endl;
//	return left + right;
//}
//
//// 2、参数个数不同
//void f()
//{
//	cout << "f()" << endl;
//}
//void f(int a)
//{
//	cout << "f(int a)" << endl;
//}
//
//// 3、参数类型顺序不同
//void f(int a, char b)
//{
//	cout << "f(int a,char b)" << endl;
//}
//void f(char b, int a)
//{
//	cout << "f(char b, int a)" << endl;
//}

//void f()
//{ }
//void f(int x = 1)
//{ }
//
//int main()
//{
//	f();
//	//Add(10, 20);
//	//Add(10.1, 20.2);
//	//
//	//f();
//	//f(10);
//
//	//f(10, 'a');
//	//f('a', 10);
//	return 0;
//}

//int& Fun()
//{
//	int n = 0;
//	return n;
//}

//int& STTop(ST & rs)
//{
//	assert(rs.top > 0);
//	return rs.a[rs.top-1];
//}
//
//STTop(rs) = 20;

// 指针变量也可以取别名，这⾥LTNode*& phead就是给指针变量取别名
// 这样就不需要用二级指针了，相对而言简化了程序
//void ListPushBack(LTNode** phead, int x)
//void ListPushBack(LTNode*& phead, int x)

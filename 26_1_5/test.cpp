#define _CRT_SECURE_NO_WARNINGS

#include "head.h"

void test1()
{
	csa::ST st;
	csa::STInit(st);

	for (int i = 0; i < 10; i++)
	{
		csa::STPush(st, i + 1);
	}

	cout << csa::STSize(st) << endl;
	csa::STPop(st);
	cout << csa::STTop(st) << endl;
	csa::STPop(st);
	cout << csa::STTop(st) << endl;

	csa::STModify(st, 100);
	cout << csa::STTop(st) << endl;

	csa::STTop2(st) = 200;
	cout << csa::STTop(st) << endl;

	csa::STDestroy(st);
}

// 内联函数声明和实现不要分离至两个文件 会导致链接失败
// debug版本默认不展开，展开需要设置
// 反汇编看见call指令就代表没有展开
inline int Add(int x, int y)
{
	int ret = x + y;
	ret += 1;
	ret += 1;
	ret += 1;
	ret += 1;
	ret += 1;
	ret += 1;
	ret += 1;
	ret += 1;
	ret += 1;
	ret += 1;
	ret += 1;
	return ret;
}

void test2()
{
	int res = Add(1, 2);
	cout << res << endl;
}

void f(int x)
{
	cout << "f(int x)" << endl;
}

void f(int* ptr)
{
	cout << "f(int* ptr)" << endl;
}

void test3()
{
	f(0);
	f(NULL);
	//强转之后有隐式类型转换
	// 与 int 不匹配 int* 不匹配
	// c语言可以
	//f((void*)0);

	//C++
	//在C++中 全部使用nullptr，它可以解决空指针问题
	void* p = NULL;
	int* p1 = (int*)p;
	f(p1);
}

int main()
{
	//cout << "666\n";
	//test1();
	//test2();
	test3();
	return 0;
}

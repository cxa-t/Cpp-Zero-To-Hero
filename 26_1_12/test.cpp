#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

//int Add_NoInline(int x, int y)
//{
//	return x + y;
//}
//
//inline int Add_Inline(int x, int y)
//{
//	int c = 0;
//	c += 1;
//	c += 1;
//	c += 1;
//	c += 1;
//	c += 1;
//	c += 1;
//	c += 1;
//	c += 1;
//	return x + y;
//}
//
//int main()
//{
//	int ret1 = Add_NoInline(2, 3);
//	int ret2 = Add_Inline(2, 3);
//	return 0;
//}

//#ifndef NULL
//	#ifdef __cplusplus
//		#define NULL 0
//	#else
//		#define NULL((void*)0)
//	#endif
//#endif

void f(int x) 
{
	cout << "f(int) 被调用" << endl;
}
void f(int* x) 
{
	cout << "f(int*) 被调用" << endl;
}

//int main() 
//{
//	f(0);           // 调用 f(int) -> 合理
//	f(NULL);        // 期望调用 f(int*)，但实际调用了 f(int)！
//	f((int*)NULL);  // 必须强转才能调用指针版本 -> 麻烦
//	return 0;
//}

//int main() 
//{
//    f(0);       // 调用 f(int)
//    f(nullptr); // 明确调用 f(int*)，因为 nullptr 只能匹配指针
//    return 0;
//}

struct A
{
	long a1;
	short a2;
	int a3;
	int* a4;
};

int main()
{
	cout << sizeof(struct A) << endl;
	return 0;
}

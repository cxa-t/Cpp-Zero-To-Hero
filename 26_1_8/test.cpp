#define _CRT_SECURE_NO_WARNINGS 1

#include"Date.h"

//int main()
//{
//	Date d(2026, 1, 8);
//	Date d1 = d - 2000;
//	d1.Print();
//	d1 += 3000;
//	d1.Print();
//	cout << (d > d1) << endl;
//	cout << (d >= d1) << endl;
//	cout << (d == d1) << endl;
//	cout << (d != d1) << endl;
//	cout << (d < d1) << endl;
//	cout << (d <= d1) << endl;
//
//	return 0;
//}


// 辅助测试函数：打印分割线
void PrintHeader(const char* title) 
{
	cout << "\n================ " << title << " ================" << endl;
}

void TestConstruction() 
{
	PrintHeader("构造与非法日期测试");

	Date d1(2023, 10, 1);
	cout << "正常构造 d1: " << d1; // 需要确保 operator<< 已实现

	Date d2(2023, 2, 29); // 非法日期：平年2月29
	if (!d2.checkDate()) 
	{
		cout << "非法日期检测通过：2023/2/29 是无效的" << endl;
	}
	else {
		cout << "非法日期检测失败！" << endl;
	}
}

void TestOperators() 
{
	PrintHeader("加减运算符测试");

	Date d(2023, 1, 1);
	Date ret = d + 100;
	cout << "2023/1/1 + 100天 = " << ret;

	Date d2 = ret - 100;
	cout << "结果 - 100天 (预期 2023/1/1) = " << d2;

	// 自增自减测试
	Date d3(2023, 12, 31);
	cout << "当前: " << d3;
	cout << "前置++: " << ++d3; // 2024/1/1
	cout << "后置++: " << d3++; // 打印 2024/1/1，实际变为 1/2
	cout << "当前: " << d3;
}

void TestLeapYearBoundary() 
{
	PrintHeader("闰年与边界测试");

	// 测试平年2月末
	Date d1(2023, 2, 28);
	d1 += 1;
	cout << "平年 2023/2/28 + 1天 -> " << d1; // 预期 3/1

	// 测试闰年2月末
	Date d2(2024, 2, 28);
	d2 += 1;
	cout << "闰年 2024/2/28 + 1天 -> " << d2; // 预期 2/29
	d2 += 1;
	cout << "闰年 2024/2/29 + 1天 -> " << d2; // 预期 3/1
}

void TestDateDifference() 
{
	PrintHeader("日期相减测试");

	Date d1(2026, 1, 8); // 今天
	Date d2(2025, 12, 25); // 考研/圣诞前后

	int gap = d1 - d2;
	cout << d1 << " - " << d2 << " 相差天数: " << gap << endl;

	// 测试负数结果
	int gap_neg = d2 - d1;
	cout << d2 << " - " << d1 << " 相差天数: " << gap_neg << endl;
}

void TestPerformance() 
{
	PrintHeader("大量计算压力测试");
	// 如果 GetDay 没有加 static，这里可能会稍微慢一点点，或者只是验证逻辑
	Date begin(1900, 1, 1);
	Date end(2050, 1, 1);
	int days = end - begin;
	cout << "1900/1/1 到 2050/1/1 总天数: " << days << endl;

	Date verify = begin + days;
	cout << "验证回推: " << verify << " (预期 2050/1/1)" << endl;
}

int main() 
{
	//TestConstruction();
	//TestOperators();
	//TestLeapYearBoundary();
	//TestDateDifference();
	//TestPerformance();

	 //取消注释以测试输入
	 Date inputDate;
	 cin >> inputDate;
	 cout << "输入的是: " << inputDate;

	return 0;
}

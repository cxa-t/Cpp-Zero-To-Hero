#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
using namespace std;

void test_vector1()
{
	//vector<int> v1;
	//vector<int> v2(10, 1);
	////vector<int> v3(++v2.begin(),--v2.end());
	//vector<int> v3;
	//v3 = v2;
	//vector<int>::iterator it = v3.begin();
	//while (it != v3.end())
	//{
	//	cout << *it << ' ';
	//	it++;
	//}
	//cout << endl;
	//for (auto e : v3)
	//{
	//	cout << e << ' ';
	//}
	//cout << endl;

	// 1. 默认构造函数--创建一个空的 vector
	vector<int> v1;
	cout << "v1 size: " << v1.size() << " (Expected: 0)" << endl;

	// 2. 填充构造函数--创建包含 5 个元素，每个值都为 100 的 vector
	vector<int> v2(10, 100);
	cout << "v2[0]: " << v2[0] << ", size: " << v2.size() << endl;

	// 3. 范围构造函数--C++98 中常用数组指针作为迭代器来初始化 vector
	int myInts[] = { 10, 20, 30, 40, 50 };
	//vector<int> v3(++v2.begin(),--v2.end());
	vector<int> v3(myInts, myInts + 5); // 复制数组中从开始到第 5 个元素之前的内容
	cout << "v3 front: " << v3.front() << ", back: " << v3.back() << endl;

	// 4. 拷贝构造函数--创建一个与 v3 完全相同的副本
	vector<int> v4(v3);
	cout << "v4 size: " << v4.size() << " (Should be same as v3)" << endl;

	// 5. 赋值运算符--将 v2 的内容（10个100）覆盖掉 v4 原有的内容，满了会扩容
	v4 = v2;
	cout << "v4 after assignment, size: " << v4.size() << ", first element: " << v4[0] << endl;

	// 6. 析构函数--当作用域结束（即执行到下面的 }）时，v1, v2, v3, v4 会自动调用析构函数释放内存
}

void testVectorExpand()
{
	size_t sz;
	vector<int> v;
	sz = v.capacity();
	cout << "capacity changed:" << sz << '\n';
	cout << "making v grow:\n";
	for (size_t i = 0; i < 100; i++)
	{
		v.push_back(i);
		if (v.capacity() != sz)
		{
			sz = v.capacity();
			cout << "capacity changed:" << sz << '\n';
		}
	}
}

void test_vector2()
{
	//testVectorExpand();
	vector<int> v(10, 1);
	v.reserve(20);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.reserve(15);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.reserve(5);
	cout << v.size() << endl;
	cout << v.capacity() << endl;
}

void test_vector3()
{
	vector<int> v(10, 1);
	v.reserve(20);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(15, 2);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(25, 3);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(5);
	cout << v.size() << endl;
	cout << v.capacity() << endl;
}

void test_vector4()
{
	// 1. 初始化：创建一个包含 10 个 5 的 vector
	vector<int> v(10, 5);
	for (auto e : v)
	{
		cout << e << ' ';
	}
	cout << endl; // 输出: 5 5 5 5 5 5 5 5 5 5

	// 2. 插入与尾部追加
	// v.begin() 指向第一个 5 的位置，在其之前插入 100
	v.insert(v.begin(), 100);
	// 在容器当前末尾添加 99
	v.push_back(99);
	for (auto e : v)
	{
		cout << e << ' ';
	}
	cout << endl; // 输出: 100 5 5 5 5 5 5 5 5 5 5 99

	// 3. 定点插入
	// v.begin() + 2 指向索引为 2 的位置（即第三个元素）
	// 在该位置插入 88，原位置及之后的元素后移
	v.insert(v.begin() + 2, 88);
	for (auto e : v)
	{
		cout << e << ' ';
	}
	cout << endl; // 输出: 100 5 88 5 5 5 5 5 5 5 5 5 99

	// 4. 删除操作
	// 删除 v.begin() + 1 位置的元素（即删除第一个 5）
	v.erase(v.begin() + 1);

	// 区间删除：v.erase(first, last) 删除 [first, last) 范围内的元素
	// v.begin() + 2 指向当前的第二个 5
	// v.end() - 1 指向最后一个元素 99 的位置
	// 因此这里删除了中间所有的 5，但保留了最后的 99（因为是左闭右开区间）
	v.erase(v.begin() + 2, v.end() - 1);

	for (auto e : v)
	{
		cout << e << ' ';
	}
	cout << endl; // 输出: 100 88 99

	//尾删两次
	v.pop_back();
	v.pop_back();
	for (auto e : v) { cout << e << ' '; }
	cout << endl; // 输出: 100
}

void test_vector5()
{
	// 准备数据：存储复杂类型 string
	vector<string> v1;
	v1.push_back("apple");
	v1.push_back("banana");
	v1.push_back("cherry");

	// --- 示范 1：【错误/低效】传值遍历 (auto e) ---
	// 缺点：每一轮循环都会调用 string 的拷贝构造函数，产生一个临时副本 e。
	// 影响：如果字符串很长，或者 vector 很大，会消耗大量内存和 CPU 时间。
	cout << "Bad (Copy): ";
	for (auto e : v1)
	{
		e += "!"; // 修改的是副本 e，不会影响容器 v1 里的原字符串
		cout << e << " ";
	}
	cout << "\n验证 v1 是否被修改: " << v1[0] << " (原封不动)" << endl;


	// --- 示范 2：【正确/高效】引用遍历 (auto& e) ---
	// 优点：e 是原字符串的别名，没有拷贝开销。
	// 场景：当你需要修改容器内的元素时，必须用这个。
	cout << "Good (Ref): ";
	for (auto& e : v1)
	{
		e += " (fixed)"; // 直接修改容器内的原数据
		cout << e << " | ";
	}
	cout << "\n验证 v1 是否被修改: " << v1[0] << " (已修改)" << endl;


	// --- 示范 3：【最推荐/只读】常量引用遍历 (const auto& e) ---
	// 优点：既保证了零拷贝的高效率，又防止了在循环内不小心误改数据。
	// 场景：90% 的只读遍历场景都应该这样写。
	cout << "Best (Const Ref): ";
	for (const auto& e : v1)
	{
		// e += "?"; // 如果取消注释，编译器会报错，保证了数据安全
		cout << e << " ";
	}
	cout << endl;

	// --- 示范 4：嵌套容器场景 (vector<vector<int>>) ---
	vector<vector<int>> matrix(3, vector<int>(5, 1)); // 3行5列的1

	// 极其重要：外层循环如果不加引用，每行都会被深拷贝！
	for (const auto& row : matrix) // 必须用引用
	{
		for (auto val : row) // 内层是 int，加不加引用影响不大
		{
			cout << val << " ";
		}
		cout << endl;
	}
}

int main()
{
	test_vector5();
	return 0;
}


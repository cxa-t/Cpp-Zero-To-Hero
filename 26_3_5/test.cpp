#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

void test_list1()
{
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	
	auto it = lt.begin();
	while (it != lt.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;

	for (auto& e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	//双向迭代器不支持 + 
	//it = lt.begin() + 3;
	//lt.erase(it);

	//要求随机迭代器
	//sort(lt.begin(), lt.end());

	string s1("asdghacg");
	cout << s1 << endl;
	sort(s1.begin(), s1.end());
	cout << s1 << endl;
}

struct A
{
	A(const A& a)
		:_a1(a._a1)
		,_a2(a._a2)
	{
		cout << "A(const A& a)" << endl;
	}

	A(int a1 = 1, int a2 = 1)
		:_a1(a1)
		, _a2(a2)
	{
		cout << "A(int a1 = 1, int a2 = 1)" << endl;
	}

	int _a1;
	int _a2;
};

void test_list2()
{
	//list<int> lt;
	//lt.push_back(1);
	//lt.emplace_back(2);
	//lt.emplace_back(3);
	//lt.emplace_back(4);
	//for (auto& e : lt)
	//{
	//	cout << e << " ";
	//}
	//cout << endl;

	list<A> lt;
	A aa1(1, 1);
	lt.push_back(aa1);
	lt.push_back(A(2, 2));
	//lt.push_back(3, 3);

	lt.emplace_back(aa1);
	lt.emplace_back(A(2, 2));
	cout << endl;
	// emplace_back:支持直接传构造A对象的参数
	lt.emplace_back(3, 3);
}

void test_list3()
{
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(4);
	lt.push_back(7);
	lt.push_back(5);

	lt.insert(lt.begin(), 10);
	for (auto& e : lt)
		cout << e << " ";
	cout << endl;

	list<int>::iterator it = lt.begin();
	int k = 0;
	cin >> k;
	while (k--)
	{
		it++;
	}
	lt.insert(it, 20);
	for (auto& e : lt)
		cout << e << " ";
	cout << endl;

	int x;
	cin >> x;
	it = find(lt.begin(), lt.end(), x);
	if (it != lt.end())
	{
		lt.insert(it, 30);
	}
	for (auto& e : lt)
		cout << e << " ";
	cout << endl;

	int i = 2;
	while (i > 0)
	{
		int y = 0;
		cin >> y;
		it = find(lt.begin(), lt.end(), y);
		if (it != lt.end())
			lt.erase(it);
		for (auto& e : lt)
			cout << e << " ";
		cout << endl;
		i--;
	}
}

void test_list4()
{
	list<int> lt;
	lt.push_back(1);
	lt.push_back(32);
	lt.push_back(33);
	lt.push_back(234);
	lt.push_back(44);
	lt.push_back(72);
	lt.push_back(54);
	for (auto& e : lt)
		cout << e << " ";
	cout << endl;

	//lt.sort();
	//for (auto& e : lt)
	//	cout << e << " ";
	//cout << endl;

	less<int> ls;
	greater<int> gt;

	//lt.sort(gt);
	lt.sort(greater<int>());
	for (auto& e : lt)
		cout << e << " ";
	cout << endl;


	list<int> l1, l2;
	l1.push_back(24);
	l1.push_back(563);
	l1.push_back(63);

	l2.push_back(876);
	l2.push_back(98);
	l2.push_back(23);

	l1.sort();
	l2.sort();

	l1.merge(l2);
	for (auto& e : l1)
		cout << e << " ";
	cout << endl;
	cout << l2.empty() << endl;
}

void test_list5()
{
	list<int> lt;
	lt.push_back(10);
	lt.push_back(32);
	lt.push_back(33);
	lt.push_back(33);
	lt.push_back(44);
	lt.push_back(33);
	lt.push_back(54);
	for (auto& e : lt)
		cout << e << " ";
	cout << endl;

	lt.sort();
	for (auto& e : lt)
		cout << e << " ";
	cout << endl;

	lt.unique();
	for (auto& e : lt)
		cout << e << " ";
	cout << endl;
}

void test_list6()
{
	// 一个链表节点转移给另一个链表
	std::list<int> mylist1, mylist2;
	std::list<int>::iterator it;

	// set some initial values:
	for (int i = 1; i <= 4; ++i)
		mylist1.push_back(i);      // mylist1: 1 2 3 4

	for (int i = 1; i <= 3; ++i)
		mylist2.push_back(i * 10);   // mylist2: 10 20 30

	it = mylist1.begin();
	++it;                         // points to 2

	mylist1.splice(it, mylist2); // mylist1: 1 10 20 30 2 3 4
	// mylist2 (empty)
	// "it" still points to 2 (the 5th element)


	// 调整当前链表节点的顺序
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
	lt.push_back(6);
	for (auto e : lt)
		cout << e << " ";
	cout << endl;

	int x = 0;
	cin >> x;
	it = find(lt.begin(), lt.end(), x);
	if (it != lt.end())
	{
		//lt.splice(lt.begin(), lt, it);
		lt.splice(lt.begin(), lt, it, lt.end());
	}

	for (auto e : lt)
		cout << e << " ";
	cout << endl;
}

void test_op1()
{
	srand(time(nullptr));
	const int N = 1000000;
	list<int> lt1;
	vector<int> v;
	for (int i = 0; i < N; ++i)
	{
		auto e = rand() + i;
		lt1.push_back(e);
		v.push_back(e);
	}
	int begin1 = clock();
	sort(v.begin(), v.end());
	int end1 = clock();

	int begin2 = clock();
	lt1.sort();
	int end2 = clock();

	printf("vector sort:%d\n", end1 - begin1);
	printf("list sort:%d\n", end2 - begin2);
}

void test_op2()
{
	srand(time(nullptr));
	const int N = 1000000;
	list<int> lt1;
	list<int> lt2;
	for (int i = 0; i < N; ++i)
	{
		auto e = rand() + i;
		lt1.push_back(e);
		lt2.push_back(e);
	}

	int begin1 = clock();
	vector<int> v(lt2.begin(), lt2.end());
	sort(v.begin(), v.end());
	lt2.assign(v.begin(), v.end());
	int end1 = clock();

	int begin2 = clock();
	lt1.sort();
	int end2 = clock();

	printf("list copy vector sort copy list sort:%d\n", end1 - begin1);
	printf("list sort:%d\n", end2 - begin2);
}

int main()
{
	//test_list2();
	//test_op2();
	return 0;
}
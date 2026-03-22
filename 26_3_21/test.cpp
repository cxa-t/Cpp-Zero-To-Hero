#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<set>
#include<map>
#include<string>

using namespace std;

//int main()
//{
//	set<int> s;
//	s.insert(5);
//	s.insert(6);
//	s.insert(40);
//	s.insert(8);
//	s.insert(3);
//
//	//set<int>::iterator it = s.begin();
//	//while (it != s.end())
//	//{
//	//	cout << *it << " ";
//	//	it++;
//	//}
//	//cout << endl;
//
//	//s.insert({ 3,5,1 });
//	//for (auto e : s)
//	//	cout << e << ' ';
//	//cout << endl;
//
//	// void insert (initializer_list<value_type> il);
//	set<string> strset = { "sort", "insert", "add" };
//	//set<string> strset({ "sort", "insert", "add" });
//	// 
//	// 遍历string比较ascll码大小顺序遍历的
//	for (auto& e : strset)
//		cout << e << " ";
//	cout << endl;
//
//	return 0;
//}

//int main()
//{
//	set<int> s({ 4,2,7,2,8,5,9 });
//	for (auto e : s)
//		cout << e << ' ';
//	cout << endl;
//
//	s.erase(s.begin());
//
//	for (auto e : s)
//		cout << e << ' ';
//	cout << endl;
//
//	int x;
//	cin >> x;
//
//	//int num = s.erase(x);
//	//if (num == 0)
//	//	cout << "NO x" << endl;
//	//else
//	//	cout << "success" << endl;
//
//	auto pos = s.find(x);
//	if (pos != s.end())
//		s.erase(pos);
//	else
//		cout << "NO x" << endl;
//
//	for (auto e : s)
//		cout << e << ' ';
//	cout << endl;
//
//	// 算法库的查找 O(N)
//	auto pos1 = find(s.begin(), s.end(), x);
//
//	// set自身实现的查找 O(logN)
//	auto pos2 = s.find(x);
//
//	return 0;
//}

//// 辅助函数：打印 set
//void printSet(const set<int>& s, const string& msg) 
//{
//    cout << msg << ": ";
//    for (int val : s)
//        cout << val << " ";
//    cout << "\n";
//}
//
//int main() 
//{
//    set<int> scores = { 50, 20, 60, 10, 30, 40, 25 };
//    printSet(scores, "初始所有分数");
//
//    // 遍历输出区间 [25, 45] 内的分数
//    // 定位起点：第一个 >= 25 的元素 (这里是 25)
//    auto it_start = scores.lower_bound(25);
//
//    // 定位终点：第一个 > 45 的元素 (这里是 50)
//    auto it_end = scores.upper_bound(45);
//
//    // 从 it_start 遍历到 it_end (不包含 it_end)
//    for (auto it = it_start; it != it_end; ++it)
//        cout << *it << " "; // 预期输出: 25 30 40
//    cout << "\n";
//
//    // 删除区间 [15, 35] 内的所有分数
//    // 同样的方法，精准定位要删除的区间边界
//    auto erase_first = scores.lower_bound(15); // 第一个 >= 15 的元素是 20
//    auto erase_last = scores.upper_bound(35);  // 第一个 > 35 的元素是 40
//
//    // 调用 erase 的区间重载版本：erase(first, last)
//    // 注意：这里删除的是 [erase_first, erase_last) 范围内的元素
//    scores.erase(erase_first, erase_last);
//    printSet(scores, "删除 [15, 35] 后的剩余分数"); // 预期剩余: 10 40 50 60
//    
//    return 0;
//}

//int main()
//{
//	// 相比set不同的是，multiset是排序，但是不去重
//	multiset<int> s = { 4,2,7,2,4,8,4,5,4,9 };
//	auto it = s.begin();
//	while (it != s.end())
//	{
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//
//	// 相比set不同的是，x可能会存在多个，find查找中序的第一个
//	int x;
//	cin >> x;
//	auto pos = s.find(x);
//	while (pos != s.end() && *pos == x)
//	{
//		cout << *pos << " ";
//		++pos;
//	}
//	cout << endl;
//
//	// 相比set不同的是，count会返回x的实际个数
//	cout << s.count(x) << endl;
//
//	//pos = s.find(x);
//	//while (pos != s.end() && *pos == x)
//	//{
//	//	pos = s.erase(pos);
//	//}
//	//cout << endl;
//	s.erase(x);
//
//	it = s.begin();
//	while (it != s.end())
//	{
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//
//	return 0;
//}

//int main()
//{
//	//map<string, string> dict;
//	map<string, string> dict = { {"left", "左边"}, {"right", "右边"}, {"insert", "插入"},{ "string", "字符串" } };
//
//	//pair<string, string> kv1("first", "第一个");
//	//map<string, string> dict = {kv1, pair<string, string>("second", "第二个")};
//
//	pair<string, string> kv1("first", "第一个");
//	dict.insert(kv1);
//
//	dict.insert(pair<string, string>("second", "第二个"));
//
//	dict.insert(make_pair("sort", "排序"));
//
//	// C++11
//	dict.insert({ "auto", "自动的" });
//
//	// 插入时只看key，value不相等不会更新
//	dict.insert({ "auto", "自动的xxxx" });
//
//	map<string, string>::iterator it = dict.begin();
//	while (it != dict.end())
//	{
//		// 可以修改value，不支持修改key
//		//it->first += 'x';
//		it->second += 'x';
//
//		//cout << (*it).first <<":"<< (*it).second<< endl;
//		cout << it->first << ":" << it->second << endl;
//		//cout << it.operator->()->first << ":" << it.operator->()->second << endl;
//		++it;
//	}
//	cout << endl;
//
//	return 0;
//}

#define _CRT_SECURE_NO_WARNINGS 1

#include"Myset.h"
#include"Mymap.h"

//void Print(const csa::set<int>& s)
//{
//	csa::set<int>::const_iterator it = s.end();
//	while (it != s.begin())
//	{
//		--it;
//		cout << *it << " ";
//	}
//	cout << endl;
//}
//
//int main()
//{
//	csa::set<int> s;
//	s.insert(5);
//	s.insert(1);
//	s.insert(3);
//	s.insert(2);
//	s.insert(6);
//
//	s.find(5);
//	
//	csa::set<int>::iterator sit = s.begin();
//	while (sit != s.end())
//	{
//		//*sit += 10;
//		cout << *sit << " ";
//		++sit;
//	}
//	cout << endl;
//
//	Print(s);
//
//	csa::map<string, string> dict;
//	dict.insert({ "sort", "排序" });
//	dict.insert({ "left", "左边" });
//	dict.insert({ "right", "右边" });
//
//	dict["left"] = "左边，剩余";
//	dict["insert"] = "插入";
//	dict["string"];
//
//	csa::map<string, string>::iterator it = dict.begin();
//	while (it != dict.end())
//	{
//		// 不能修改first，可以修改second
//		//it->first += 'x';
//		//it->second += 'x';
//		cout << it->first << ":" << it->second << endl;
//		++it;
//	}
//	cout << endl;
//
//	for (auto& kv : dict)
//	{
//		cout << kv.first << ":" << kv.second << endl;
//	}
//
//	return 0;
//}


int main()
{
	cout << "================ 测试 csa::set 的 Find 功能 ================" << endl;
	csa::set<int> s;
	s.insert(5);
	s.insert(1);
	s.insert(3);
	s.insert(2);
	s.insert(6);

	// 测试用例 1：查找 Set 中存在的元素
	int search_val1 = 3;
	auto it_set1 = s.find(search_val1);
	if (it_set1 != s.end()) {
		cout << "成功找到元素: " << *it_set1 << endl;
	}
	else {
		cout << "查找失败，没找到 " << search_val1 << endl;
	}

	// 测试用例 2：查找 Set 中不存在的元素
	int search_val2 = 100;
	auto it_set2 = s.find(search_val2);
	if (it_set2 == s.end()) {
		cout << "逻辑正确，成功拦截不存在的元素: " << search_val2 << endl;
	}
	else {
		cout << "逻辑错误，居然找到了不存在的元素！" << endl;
	}

	cout << "\n================ 测试 csa::map 的 Find 功能 ================" << endl;
	csa::map<string, string> dict;
	dict.insert({ "sort", "排序" });
	dict.insert({ "left", "左边" });
	dict.insert({ "right", "右边" });

	// 测试用例 3：查找 Map 中存在的键 (Key)
	string search_key1 = "left";
	auto it_map1 = dict.find(search_key1);
	if (it_map1 != dict.end()) {
		cout << "成功找到键: [" << it_map1->first << "]，对应的值为: " << it_map1->second << endl;
	}
	else {
		cout << "查找失败，没找到键 " << search_key1 << endl;
	}

	// 测试用例 4：查找 Map 中不存在的键
	string search_key2 = "unknown";
	auto it_map2 = dict.find(search_key2);
	if (it_map2 == dict.end()) {
		cout << "逻辑正确，成功拦截不存在的键: [" << search_key2 << "]" << endl;
	}
	else {
		cout << "逻辑错误，居然找到了不存在的键！" << endl;
	}

	return 0;
}
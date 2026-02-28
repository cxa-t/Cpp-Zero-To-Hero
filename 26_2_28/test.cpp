#define _CRT_SECURE_NO_WARNINGS 1

#include "vector.h"
#include <iostream>
using namespace std;

//#include <iostream>
//#include <vector>
//
//void printVc(const std::vector<int>& v)
//{
//	auto it = v.begin();
//	while (it != v.end())
//	{
//		std::cout << *it << " ";
//		it++;
//	}
//	std::cout << std::endl;
//}
//void testVector()
//{
//	std::vector<int> v1;
//	v1.push_back(0);
//	v1.push_back(1);
//	v1.push_back(2);
//	//v1.push_back(3);
//	//v1.push_back(4);
//	printVc(v1);
//	//v1.insert(v1.begin(), 30);
//	//printVector(v1);
//
//	int x;
//	std::cin >> x;
//	auto p = find(v1.begin(), v1.end(), x);
//	if (p != v1.end())
//	{
//		v1.insert(p, 99);
//		(*p) *= 10;
//
//		//p = v1.insert(p, 99);
//		//(*(p + 1)) *= 10;
//	}
//	printVc(v1);
//}

int main()
{
	//testVector();
	csa::testCsaVector5();

	//std::vector<int> v(5, 1);
	//for (int i = 0; i < v.size(); i++)
	//	printf("%p\n", &v[i]);

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <vector>
using namespace std;

//int main()
//{
//	vector <vector<int>> vv(10, vector<int>(5, 1));
//	vv[2][1] = 10;
//	vv.operator[](2).operator[](1) = 11;
//	return 0;
//}

#include "vector.h"
namespace csa
{
	void testCsaVector1()
	{
		vector<int> v1;
		v1.push_back(0);
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);

		printVector(v1);

		vector<double> v2;
		v2.push_back(1.1);
		v2.push_back(1.2);
		v2.push_back(2.1);
		v2.push_back(3.1);
		v2.push_back(4.1);
		printVector(v2);
		v2.pop_back();
		printVector(v2);
		cout << v2.empty() << endl;
	}

	void testCsaVector2()
	{
		vector<int> v1;
		v1.push_back(0);
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		//v1.push_back(4);
		printVector(v1);
		//v1.insert(v1.begin(), 30);
		//printVector(v1);

		int x;
		cin >> x;
		auto p = find(v1.begin(), v1.end(), x);
		if (p != v1.end())
		{
			//v1.insert(p, 99);
			//(*p) *= 10;

			p = v1.insert(p, 99);
			(*(p+1)) *= 10;
		}
		printVector(v1);
	}
}

int main()
{
	csa::testCsaVector2();
	return 0;
}
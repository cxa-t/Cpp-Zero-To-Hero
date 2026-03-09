#define _CRT_SECURE_NO_WARNINGS 1

#include <deque>
#include <iostream>
#include <algorithm>
using namespace std;

#include "Stack.h"
#include "Queue.h"
#include "PriorityQueue.h"

//int main()
//{
//	csa::stack<int, vector<int>> st;
//	st.push(1);
//	st.push(2);
//	st.push(3);
//	st.push(4);
//
//	cout << st.top() << endl;
//	st.pop();
//	cout << st.top() << endl;
//
//	csa::queue<int> q;
//	q.push(1);
//	q.push(2);
//	q.push(3);
//	q.push(4);
//
//	cout << q.front() << endl;
//	q.pop();
//	cout << q.front() << endl;
//
//	csa::priority_queue<int> pq;
//	pq.push(3);
//	pq.push(6);
//	pq.push(1);
//	pq.push(10);
//	pq.push(9);
//
//	cout << pq.top() << endl;
//	pq.pop();
//	cout << pq.top() << endl;
//	return 0;
//}

void test_op1()
{
	srand((unsigned int)time(nullptr));
	const int N = 1000000;

	deque<int> dq;
	vector<int> v;

	for (int i = 0; i < N; ++i)
	{
		auto e = rand() + i;
		v.push_back(e);
		dq.push_back(e);
	}

	int begin1 = clock();
	sort(v.begin(), v.end());
	int end1 = clock();

	int begin2 = clock();
	sort(dq.begin(), dq.end());
	int end2 = clock();

	printf("vector:%d\n", end1 - begin1);
	printf("deque:%d\n", end2 - begin2);
}

void test_op2()
{
	srand((unsigned int)time(nullptr));
	const int N = 1000000;

	deque<int> dq1;
	deque<int> dq2;

	for (int i = 0; i < N; ++i)
	{
		auto e = rand() + i;
		dq1.push_back(e);
		dq2.push_back(e);
	}

	int begin1 = clock();
	sort(dq1.begin(), dq1.end());
	int end1 = clock();

	int begin2 = clock();
	// ¿½±´µ½vector
	vector<int> v(dq2.begin(), dq2.end());
	sort(v.begin(), v.end());
	dq2.assign(v.begin(), v.end());
	int end2 = clock();

	printf("deque sort:%d\n", end1 - begin1);
	printf("deque copy vector sort, copy back deque:%d\n", end2 - begin2);
}

int main()
{
	test_op2();
	return 0;
}

//int main()
//{
//	//priority_queue<int> pq;
//	csa::priority_queue<int, vector<int>, Less<int>> pq;
//	//csa::priority_queue<int> pq;
//	pq.push(4);
//	pq.push(1);
//	pq.push(5);
//	pq.push(7);
//	pq.push(9);
//	while (!pq.empty())
//	{
//		cout << pq.top() << " ";
//		pq.pop();
//	}
//	cout << endl;
//
//	return 0;
//}

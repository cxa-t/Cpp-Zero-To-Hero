#define _CRT_SECURE_NO_WARNINGS 1

#include "string.h"

namespace csa
{
	void test_string1()
	{
		string s1;
		string s2("hello world");
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;

		for (size_t i = 0; i < s2.size(); i++)
		{
			s2[i] += 2;
		}

		cout << s2.c_str() << endl;

		for (auto e : s2)
		{
			cout << e << " ";
		}
		cout << endl;

		string::iterator it = s2.begin();
		while (it != s2.end())
		{
			//*it += 2;
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}

	void test_string2()
	{
		string s1("hello world");
		s1 += 'x';
		s1 += '#';
		cout << s1.c_str() << endl;

		s1 += "hello bit";
		cout << s1.c_str() << endl;

		s1.insert(5, '$');
		cout << s1.c_str() << endl;

		s1.insert(0, '$');
		cout << s1.c_str() << endl;

		string s2("hello world");
		cout << s2.c_str() << endl;

		s2.insert(5, "$$$");
		cout << s2.c_str() << endl;

		s2.insert(0, "$$$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");
		cout << s2.c_str() << endl;
	}

	void test_string3()
	{
		string s1("hello world");
		s1.erase(6, 100);
		cout << s1.c_str() << endl;

		string s2("hello world");
		s2.erase(6);
		cout << s2.c_str() << endl;

		string s3("hello world");
		s3.erase(6, 3);
		cout << s3.c_str() << endl;
	}

	void test_string4()
	{
		string s("test.cpp.zip");
		size_t pos = s.find('.');
		string suffix = s.substr(pos);
		cout << suffix.c_str() << endl;

		string copy(s);
		cout << copy.c_str() << endl;

		s = suffix;
		cout << suffix.c_str() << endl;
		cout << s.c_str() << endl;

		s = s;
		cout << s.c_str() << endl;
	}

	void test_string5()
	{
		string s1("hello world");
		string s2("hello world");

		cout << (s1 < s2) << endl;
		cout << (s1 == s2) << endl;
		cout << ("hello world" < s2) << endl;
		cout << (s1 == "hello world") << endl;
		//cout << ("hello world" == "hello world") << endl;

		cout << s1 << s2 << endl;

		string s0;
		cin >> s0;
		cout << s0 << endl;
	}
}

int main()
{
	//csa::string s1("hello world");
	////s1[0] = 'z';
	////cout << s1.c_str() << endl;

	//csa::string s2 = s1;

	//s2.insert(0, "csa");
	//cout << s2.c_str() << endl;

	csa::test_string5();

	//csa::string s1;
	//cin >> s1;
	//cout << s1;

	return 0;
}
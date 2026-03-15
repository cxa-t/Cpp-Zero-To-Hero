#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;

//// C++11
//class Base final
//{
//public:
//	void func5() { cout << "Base::func5" << endl; }
//protected:
//	int a = 1;
//private:
//	// C++98的方法
//	Base() {}
//};
//
//class Derive :public Base
//{
//public:
//	void func4() { cout << "Derive::func4" << endl; }
//};
//
//int main()
//{
//	//Derive d;
//	return 0;
//}

//// 前置声明
//class Student;
//
//class Person
//{
//public:
//	// 友元关系不能被继承
//	friend void Display(const Person& p, const Student& s);
//protected:
//	string _name; // 姓名
//};
//class Student : public Person
//{
//	friend void Display(const Person& p, const Student& s);
//protected:
//	int _stuNum; // 学号
//};
//void Display(const Person& p, const Student& s)
//{
//	cout << p._name << endl;
//	cout << s._stuNum << endl;
//}
//
//int main()
//{
//	Person p;
//	Student s;
//	// 编译报错：error C2248: “Student::_stuNum”: 无法访问 protected 成员
//	// 解决方案：Display也变成Student 的友元即可
//	Display(p, s);
//
//	return 0;
//}

//class Person
//{
//public:
//	string _name;
//	static int _count;
//};
//int Person::_count = 0;
//
//class Student : public Person
//{
//public:
//	static int _count;
//protected:
//	int _stuNum;
//};
//int Student::_count = 10;
//int main()
//{
//	Person p;
//	Student s;
//
//	// 这里的运行结果可以看到非静态成员_name的地址是不一样的
//	// 说明子类继承下来了，父子类对象各有一份
//	cout << &p._name << endl;
//	cout << &s._name << endl;
//
//	// 这里的运行结果可以看到静态成员_count的地址是一样的
//	// 说明子类和父类共用同一份静态成员
//	cout << &p._count << endl;
//	cout << &s._count << endl;
//
//	// 公有的情况下，父子类指定类域都可以访问静态成员
//	cout << Person::_count << endl;
//	cout << Student::_count << endl;
//
//	//Person::_count++;
//
//	//cout << p._count << endl;
//	//cout << s._count << endl;
//
//	return 0;
//}


class Person
{
public:
	string _name; // 姓名
};

class Student : public Person
{
protected:
	int _num; //学号
};

class Teacher : public Person
{
protected:
	int _id; // 职工编号
};

// 不要去玩菱形继承
class Assistant : public Student, public Teacher
{
protected:
	string _majorCourse; // 主修课程
};

int main()
{
	// 编译报错：error C2385: 对“_name”的访问不明确
	Assistant a;
	//a._name = "peter";

	//// 需要显示指定访问哪个父类的成员可以解决二义性问题，但是数据冗余问题无法解决
	a.Student::_name = "小李";
	a.Teacher::_name = "老李";

	return 0;
}

//int main()
//{
//	std::string name;
//	std::cout << "Please, enter your full name: ";
//	std::getline(std::cin, name,'/');
//	std::cout << "Hello, " << name << "!\n";
//	return 0;
//}


class Base1 { public: int _b1 = 1; };
class Base2 { public: int _b2 = 2; };
class Derive : public Base2, public Base1 {
public:
	int _d = 3;
	int _e = 4;
};

int main()
{
	Derive d;
	Base1* p1 = &d;
	Base2* p2 = &d;
	Derive* p3 = &d;
	return 0;
}

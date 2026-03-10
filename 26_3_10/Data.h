#pragma once
#include <iostream>

// 1. 基础模板 (只留声明)
template<class T1, class T2>
class Data
{
public:
    Data(); // 实现被挪到了 .cpp 文件中
private:
    T1 _d1;
    T2 _d2;
};

// 2. 特化版本
template<>
class Data<int, char>
{
public:
    Data() { std::cout << "class Data<int, char>" << std::endl; }
};

// 偏特化 (以指针为例，其他的同理省略)
template <typename T1, typename T2>
class Data <T1*, T2*>
{
public:
    Data() { std::cout << "Data<T1*, T2*>" << std::endl; }
};

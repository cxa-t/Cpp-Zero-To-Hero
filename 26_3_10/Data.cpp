#define _CRT_SECURE_NO_WARNINGS 1

#include "Data.h"

// 1. 基础模板的具体实现
template<class T1, class T2>
Data<T1, T2>::Data()
{
    std::cout << "Data<T1, T2> 基础模板 (来自 .cpp 的实现)" << std::endl;
}

// 2.显式实例化 (Explicit Instantiation)
// 告诉编译器：把 <int, int> 和 <double, int> 的代码生成出来
// 语法注意：开头是 template class，绝对不能带 <>，带了就变成全特化了
template class Data<int, int>;
template class Data<double, int>;

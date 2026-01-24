#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <string>
using namespace std;

//int main()
//{
//	try
//	{
//
//	}
//	catch (const exception& e)
//	{
//		cout << e.what() << endl;
//	}
//
//	return 0;
//}

//int main()
//{
//	string s1;
//	string s2("marathon 666");
//	string s3(s2);
//
//	cout << s1 << endl;
//	cout << s2 << endl;
//	cout << s3 << endl;
//
//	cin >> s1;
//	cout << s1;
//
//	return 0;
//}

void test_string1()
{
    // 1. 默认构造函数 (Default Constructor)
    // 创建一个空字符串，size 为 0，不分配字符内存（但可能分配少许内部缓冲区）。
    string s1;

    // 2. C-String 构造函数 (String from C-string)
    // 使用 C 风格字符串常量初始化，自动计算长度并拷贝内容。
    string s2("hello world!");

    // 3. 拷贝构造函数 (Copy Constructor)
    // 创建 s2 的一份副本。s3 和 s2 内容相同，但内存地址独立（深拷贝）。
    string s3(s2);

    // 4. 子串构造函数 (Substring Constructor)
    // 原型: string(const string& str, size_t pos, size_t len = npos)
    // 含义: 从 s2 的下标 6 (即 'w') 开始，拷贝 npos (直到末尾) 个字符。
    // s2: "hello world!"
    //            ^ (下标6)
    string s4(s2, 6, std::string::npos);

    // 5. 填充构造函数 (Fill Constructor)
    // 原型: string(size_t n, char c)
    // 含义: 创建由 10 个字符 '*' 组成的字符串。
    string s5(10, '*');

    // 6. 区间构造函数 (Range Constructor)
    // 原型: string(InputIterator first, InputIterator last)
    // 含义: 拷贝迭代器 [first, last) 区间内的字符。
    // 左闭右开原则：包含 begin()，但不包含 begin() + 5。
    // s3: "hello world!"
    //      ^    ^
    //    begin  begin+5 (指向空格) -> 空格不被拷贝
    string s6(s3.begin(), s3.begin() + 5);

    // --- 输出结果验证 ---
    cout << "s1:" << s1 << "\n"; // 输出空行
    cout << "s2:" << s2 << "\n"; // 输出: hello world!
    cout << "s3:" << s3 << "\n"; // 输出: hello world!
    cout << "s4:" << s4 << "\n"; // 输出: world!
    cout << "s5:" << s5 << "\n"; // 输出: **********
    cout << "s6:" << s6 << "\n"; // 输出: hello
}

void test_string2()
{
    string s;                    // 默认构造：空字符串
    string original("marathon"); // 有参构造：初始化为 "marathon"

    cout << "--- 初始化状态 ---" << endl;
    cout << "s (初始): " << s << endl;          // 输出空串
    cout << "original: " << original << endl;   // 输出 marathon

    // 2. String 对象赋值: 将 original 的内容深拷贝给 s。此时 s 拥有独立的内存空间。
    s = original;

    cout << "\n--- 赋值后 (string对象) ---" << endl;
    cout << "s = original;" << endl;
    cout << "s: " << s << endl; // 输出: marathon

    // 3. C 风格字符串赋值: 将字符数组/常量字符串 "china" 赋值给 s。
    // 注意: s 原有的 "marathon" 内存会被释放或重用，内容被覆盖。
    s = "china";

    cout << "\n--- 赋值后 (C字符串) ---" << endl;
    cout << "s = \"china\";" << endl;
    cout << "s: " << s << endl; // 输出: china

    // 4. 单字符赋值: 将 s 的内容变成仅包含一个字符 'A'。
    s = 'A';

    cout << "\n--- 赋值后 (char字符) ---" << endl;
    cout << "s = 'A';" << endl;
    cout << "s: " << s << endl; // 输出: A
}

void test_string3()
{
    string s("hello world");
    cout << "s:" << s << endl;
    // 1. 普通正向迭代器 (iterator)：可读、可写、从左向右
    cout << "--- 1. 正向遍历并加密 (+1) ---" << endl;
    // begin() 指向第一个字符 'h'
    string::iterator it = s.begin();
    while (it != s.end()) // end() 指向最后一个字符的 *后面*
    {
        *it += 1;         // 修改：将当前字符 ASCII 码 +1 (加密)
        cout << *it;      // 输出修改后的字符
        ++it;             // 步进：向后移动
    }
    cout << "\n(当前字符串变为: " << s << ")\n" << endl;

    // 2. 遍历验证修改
    cout << "--- 2. 验证修改后的字符串 ---" << endl;
    it = s.begin(); // 重新指向开头
    while (it != s.end())
    {
        cout << *it << " "; // 用空格分隔打印
        ++it;
    }
    cout << "\n" << endl;


    // 3. 反向迭代器 (reverse_iterator)：可读、可写、从右向左
    cout << "--- 3. 反向遍历并解密 (-1) ---" << endl;
    // rbegin() 指向最后一个有效字符  rend() 指向第一个字符的 *前面*
    string::reverse_iterator rit = s.rbegin();
    while (rit != s.rend())
    {
        *rit -= 1;        // 修改：将字符 -1 (还原/解密)
        cout << *rit;     // 此时打印的是还原后的字符，顺序是从后往前
        ++rit;            // 注意：反向迭代器的 ++ 在物理内存上是 向前 移动
    }
    cout << "\n(字符串内容已还原: " << s << ")\n" << endl;

    // 4. 常量迭代器 (const_iterator)：只读 (Read Only)、从左向右
    // 场景：用于 const 对象，或者为了安全不希望修改数据
    cout << "--- 4. const 字符串的正向遍历 ---" << endl;
    const string str("const hello world");

    // 必须使用 const_iterator，否则编译报错，因为 str 是 const 的
    // cbegin() 显式返回 const_iterator (C++11)
    string::const_iterator cit = str.cbegin();
    while (cit != str.cend())
    {
        // *cit += 1; // 错误！const 迭代器不允许修改指向的内容
        cout << *cit;
        ++cit;
    }
    cout << "\n" << endl;

    // 5. 常量反向迭代器 (const_reverse_iterator)：只读、从右向左
    cout << "--- 5. const 字符串的反向遍历 ---" << endl;
    // crbegin() 显式返回 const_reverse_iterator
    string::const_reverse_iterator crit = str.crbegin();

    while (crit != str.crend())
    {
        cout << *crit;
        ++crit;
    }
    cout << endl;
}

void test_string4() 
{
    // ---------------------------------------------------------
    // 1. 初始状态 (Empty)
    // ---------------------------------------------------------
    string s;
    cout << "--- 1. Initial State ---" << endl;
    cout << "Is empty? : " << (s.empty() ? "true" : "false") << endl;
    cout << "Size      : " << s.size() << endl;
    cout << "Capacity  : " << s.capacity() << " (Default SSO buffer)" << endl;
    cout << "Max Size  : " << s.max_size() << endl;

    // ---------------------------------------------------------
    // 2. 预分配内存 (Reserve)
    // 目的：避免后续追加时的多次扩容
    // ---------------------------------------------------------
    s.reserve(100);
    cout << "\n--- 2. After reserve(100) ---" << endl;
    cout << "Size      : " << s.size() << " (Unchanged)" << endl;
    cout << "Capacity  : " << s.capacity() << " (>= 100)" << endl;

    // ---------------------------------------------------------
    // 3. 赋值 (Assignment)
    // ---------------------------------------------------------
    s = "Hello World";
    cout << "\n--- 3. After assignment \"Hello World\" ---" << endl;
    cout << "Is empty? : " << (s.empty() ? "true" : "false") << endl;
    cout << "Size      : " << s.size() << endl;
    cout << "Capacity  : " << s.capacity() << " (Unchanged)" << endl;

    // ---------------------------------------------------------
    // 4. 修改大小 (Resize - 变大)
    // ---------------------------------------------------------
    // 将长度强行拉大到 50，新增的位置补 'x'
    s.resize(50, 'x');
    cout << "\n--- 4. After resize(50, 'x') ---" << endl;
    cout << "Content   : " << s << endl;
    cout << "Size      : " << s.size() << endl;
    cout << "Capacity  : " << s.capacity() << endl;

    // ---------------------------------------------------------
    // 5. 修改大小 (Resize - 变小)
    // ---------------------------------------------------------
    // 截断字符串，只保留前 5 个字符
    s.resize(5);
    cout << "\n--- 5. After resize(5) ---" << endl;
    cout << "Content   : " << s << endl;
    cout << "Size      : " << s.size() << endl;
    cout << "Capacity  : " << s.capacity() << " (Usually not reduced)" << endl;

    // ---------------------------------------------------------
    // 6. 清空 (Clear)
    // ---------------------------------------------------------
    s.clear();
    cout << "\n--- 6. After clear() ---" << endl;
    cout << "Is empty? : " << (s.empty() ? "true" : "false") << endl;
    cout << "Size      : " << s.size() << endl;
    cout << "Capacity  : " << s.capacity() << " (Memory still held)" << endl;

    // ---------------------------------------------------------
    // 7. 缩容 (Shrink to fit)
    // ---------------------------------------------------------
    // 请求归还未使用的内存
    s.shrink_to_fit();
    cout << "\n--- 7. After shrink_to_fit() ---" << endl;
    cout << "Size      : " << s.size() << endl;
    cout << "Capacity  : " << s.capacity() << " (Reduced to minimum)" << endl;
}

void TestPushBack()
{
    string s("hello world");
    size_t sz = s.capacity();
    cout << "capacity changed: " << sz << '\n';

    cout << "making s grow:\n";
    for (int i = 0; i < 100; ++i)
    {
        s.push_back('c');
        if (sz != s.capacity())
        {
            sz = s.capacity();
            cout << "capacity changed: " << sz << '\n';
        }
    }
}

void test_string5()
{
    //string s2("hello world");
    TestPushBack();
}

void test_string6()
{
    string s = "Super C++";

    cout << "--- 1. 基础访问 (读) ---" << endl;
    cout << "s[0] (下标):       " << s[0] << endl;
    cout << "s.at(0) (安全):    " << s.at(0) << endl;
    cout << "s.front() (头部):  " << s.front() << endl; // C++11
    cout << "s.back() (尾部):   " << s.back() << endl;  // C++11

    cout << "\n--- 2. 修改字符 (写) ---" << endl;
    // 这些接口返回的都是字符的引用 (char&)，所以可以直接修改
    s[0] = 's';           // S -> s
    s.at(6) = '#';        // + -> #
    s.back() = '!';       // + -> !
    s.front() = 'H';      // s -> H (再次修改)

    cout << "修改后 s: " << s << endl; // 输出: Huper C#!

    cout << "\n--- 3. 越界安全性测试 (重点) ---" << endl;

    // A. 使用 at() 访问越界
    try {
        cout << "尝试执行 s.at(100)..." << endl;
        char c = s.at(100); // 100 远超 size，肯定越界
        cout << "这行永远不会执行: " << c << endl;
    }
    catch (const std::out_of_range& e) {
        cout << "[捕获异常] at() 检测到越界: " << e.what() << endl;
    }

    // B. 使用 [] 访问越界 (危险行为！)
    cout << "尝试执行 s[100]..." << endl;
    // 警告：s[100] 是未定义行为 (Undefined Behavior)。
    // 它不会抛出标准异常，可能导致程序崩溃，也可能读到乱码。
    // 在 Debug 模式下有些编译器会报错，但在 Release 模式下它就像"野指针"一样危险。
    cout << "结果 (未定义): " << (int)s[100] << " (可能乱码或崩溃)" << endl;
}

void test_string7()
{
    string s;
    // 1. 追加 (Append)
    s.push_back('H');          // "H"
    s += "ello";               // "Hello"
    s.append(" World");        // "Hello World"
    s.append("C++ is cool", 3);// 追加前3个字符 -> "Hello WorldC++"
    cout << "[1. 追加后]\t: " << s << endl;

    // 2. 插入 (Insert)
    s.insert(5, ",");          // 在下标5插入逗号 -> "Hello, WorldC++"
    s.insert(0, "xxx");        // 头插字符串 -> "xxxHello, WorldC++"
    // 注意：insert(pos, n, char)
    s.insert(0, 1, 'A');       // 头插1个'A' -> "AxxxHello, WorldC++"

    // 使用迭代器头插
    s.insert(s.begin(), 'Z');  // -> "ZAxxxHello, WorldC++"
    // 在下标12位置插入3个感叹号
    // 目前 s 是 "ZAxxxHello, WorldC++"
    // 下标 12 刚好是 'W' 的位置
    s.insert(12, 3, '!');      // -> "ZAxxxHello, !!!WorldC++"
    cout << "[2. 插入后]\t: " << s << endl;

    // 3. 替换 (Replace)
    size_t pos = s.find("World");
    if (pos != string::npos)
        // 从 pos 开始，把长度为 5 ("World") 的内容替换为 "Universe"
        s.replace(pos, 5, "Universe");
    // 结果 -> "ZAxxxHello, !!!UniverseC++"
    cout << "[3. 替换后]\t: " << s << endl;

    // 4. 删除 (Erase)
    s.pop_back(); // 删掉最后一个 '+'
    s.pop_back(); // 删掉倒数第二个 '+'
    // 此时 -> "ZAxxxHello, !!!Universe"
    // erase(pos, len)
    // 从下标 0 开始删除 7 个字符 ("ZAxxxHe")
    s.erase(0, 7);
    // 结果应该是 "llo, !!!Universe"
    cout << "[4. 删除后]\t: " << s << endl;

    // 5. 交换 (Swap)
    string other = "Empty";
    cout << "[5. 交换前]\t: s=" << s << ", other=" << other << endl;
    s.swap(other); // s 变成 "Empty", other 变成刚才那个复杂的串
    cout << "[5. 交换后]\t: s=" << s << ", other=" << other << endl;
}

int main() 
{
    test_string7();
    return 0;
}
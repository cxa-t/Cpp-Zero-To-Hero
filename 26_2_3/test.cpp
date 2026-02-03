#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <string>
using namespace std;

void test_string1()
{
	string s("hello world");
	string tmp("csa");

	//s.insert(6, tmp);
	//cout << s << endl;

	//s.insert(0, 1, 'z');
	//cout << s << endl;

	//s.insert(0,"xxxxxx");
	//cout << s << endl;

	//s.insert(s.begin(),'c');
	//cout << s << endl;
	//auto it = s.begin();
	//for (auto ch : s)
	//{
	//	*it += 2;
	//	cout << *it << ' ';
	//	it++;
	//}
	//cout << endl;
	
	string ss("xxxxx");
	s += ' ';
	s += "csa";
	s += ss;
	cout << s << endl;
}

void test_insert() 
{
    cout << "=== 测试 Insert 接口 ===" << endl;
    string s = "Hello World";

    // 1.最常用：指定位置插入字符串
    s.insert(5, " C++");
    cout << "1. 下标插入字符串: " << s << endl; // "Hello C++ World"

    // 2. 插入重复字符
    s.insert(0, 3, '!');
    cout << "2. 下标插入字符  : " << s << endl; // "!!!Hello C++ World"

    // 3. [迭代器版] C++11 核心特性：插入并更新迭代器
    // 目的: 在头部插入 '@'
    auto it = s.begin();

    // 关键点：insert 返回指向新插入字符 '@' 的迭代器
    // 如果不接返回值，旧的 it 可能会失效（取决于是否发生扩容）
    it = s.insert(it, '@');

    cout << "3. 迭代器插入单字符: " << s << endl;    // "@!!!Hello C++ World"
    cout << "   当前迭代器指向: " << *it << endl;    // '@'

    // 4. 插入区间
    string sub = "123";
    // 在 '@' 后面插入 "123"
    // 注意：我们将迭代器+1，指向 '@' 的下一个位置
    s.insert(it + 1, sub.begin(), sub.end());
    cout << "4. 迭代器插入区间: " << s << endl;      // "@123!!!Hello C++ World"
}

void test_erase() 
{
    cout << "\n=== 测试 Erase 接口 ===" << endl;
    string s = "0123456789";
    cout << "初始字符串: " << s << endl;

    // 1. 删除指定长度:从下标 0 开始，删除 2 个字符
    s.erase(0, 2);
    cout << "1. 下标删除(0,2) : " << s << endl; // "23456789"

    // 2. 删除到末尾 (利用 npos)  从下标 6 开始，删光后面所有
    s.erase(6); // 等同于 s.erase(6, npos)
    cout << "2. 下标删除(6...) : " << s << endl; // "234567"

    // 3. 删除单个字符 (C++11) 删除开头的 '2'
    auto it = s.begin();
    // 关键点：erase 返回被删元素 *下一个* 位置的迭代器
    // 此时 '2' 被删，it 更新指向 '3'
    it = s.erase(it);

    cout << "3. 迭代器删首字符: " << s << endl;     // "34567"
    cout << "   当前迭代器指向: " << *it << endl;   // '3'

    // 4. 删除区间 删除 [it, it+2) -> 即删除 "34"
    it = s.erase(it, it + 2);
    cout << "4. 迭代器删区间  : " << s << endl;     // "567"
    cout << "   当前迭代器指向: " << *it << endl;   // '5'
}

void test_modifiers_from_image() 
{
    cout << "=== 测试截图中的核心修改器接口 ===" << endl;
    string s = "Hello";
    cout << "初始状态: " << s << endl;

    // 1. operator+= (最常用)
    // 含义: 追加内容 (支持 string, C-string, char)
    s += " ";        // 追加 C-string
    s += "World";    // 追加 string (隐式转换)
    s += '!';        // 追加 char
    cout << "[+=] 追加后: " << s << endl; // "Hello World!"

    // 2. append (更灵活)
    // 含义: 追加内容 (提供比 += 更多的参数选项)
    string suffix = " cplusplus";
    // 只追加 suffix 的前 4 个字符 (" cpl")
    s.append(suffix, 0, 4);
    // 追加 3 个 '.'
    s.append(3, '.');
    cout << "[append] 追加后: " << s << endl; // "Hello World! cpl..."

    // 3. push_back
    // 含义: 尾部追加一个字符 (专门针对 char)
    s.push_back('A');
    cout << "[push_back] 尾插后: " << s << endl; // "Hello World! cpl...A"

    // 4. assign (重置)
    // 含义: 重新赋值内容 (就像把旧的扔了，换新的)
    // 相当于 s = "New Content"; 但 assign 支持更复杂的参数
    s.assign("New Content");
    cout << "[assign] 重置后: " << s << endl; // "New Content"

    // assign 的高级用法：取子串赋值
    string base = "123456789";
    s.assign(base, 2, 4); // 取 base 从下标2开始的4个字符 ("3456")
    cout << "[assign] 子串赋值后: " << s << endl; // "3456"

    // 5. replace (替换)
    // 含义: 替换部分内容 (核心功能)
    // 将 "45" (下标1开始，长度2) 替换为 "XX"
    s.replace(1, 2, "XX");
    cout << "[replace] 替换后: " << s << endl; // "3XX6"

    // 6. swap (交换)
    // 含义: 交换两个字符串的内容 (极快，O(1))
    string other = "I am Other";
    cout << "交换前 -> s: " << s << ", other: " << other << endl;

    s.swap(other); // s 变成 "I am Other", other 变成 "3XX6"

    cout << "[swap] 交换后 -> s: " << s << ", other: " << other << endl;

    // 7. pop_back (C++11)
    // 含义: 删除最后一个字符
    s.pop_back(); // 删掉 'r'
    s.pop_back(); // 删掉 'e'
    cout << "[pop_back] 尾删两次后: " << s << endl; // "I am Oth"
}

void test_string_operations()
{
    string s = "Hello World";
    const char* c_str_ptr = s.c_str();// 返回const char*，兼容 C 语言函数 (如printf)
    printf("c_str output: %s (len=%d)\n", c_str_ptr, (int)strlen(c_str_ptr));

    // data(): C++11 后与 c_str() 几乎一致，返回指向内存数据的指针(很少用)
    const char* data_ptr = s.data();

    // copy(buffer, len, pos): 把 string 的内容拷贝到用户提供的 buffer 中
    // 注意：copy 不会自动添加 '\0'，需要手动处理
    char buffer[20];
    size_t length = s.copy(buffer, 5, 0); // 从下标0开始，拷贝5个字符
    buffer[length] = '\0'; // 手动添加结束符！ "Hello"

    string str = "file.txt.tar.gz";
    cout << "目标字符串: " << str << endl;
    
    size_t pos = str.find("tar");// (1) find: 正向查找 "tar"
    if (pos != string::npos)
        cout << "find(\"tar\")          : " << pos << endl;

    pos = str.rfind('.');// (2) rfind: 反向查找 "." (找最后一个点)
    if (pos != string::npos) 
        cout << "rfind('.')            : " << pos << " (后缀名分割点)" << endl;

    // find_first_of: 查找 "aeiou" 中任意一个字符第一次出现的位置
    // 类似于: "这里面有没有元音字母？在哪？"
    string vowels = "aeiou";
    pos = str.find_first_of(vowels);
    cout << "find_first_of(vowels) : " << pos << " ('" << str[pos] << "')" << endl;

    // find_last_of: 查找 "aeiou" 中任意一个字符最后一次出现的位置
    pos = str.find_last_of(vowels);
    cout << "find_last_of(vowels)  : " << pos << " ('" << str[pos] << "')" << endl;

    // find_first_not_of: 查找第一个不是小写字母的字符
    // 比如找数字、点号等
    string lower = "abcdefghijklmnopqrstuvwxyz";
    pos = str.find_first_not_of(lower);
    cout << "find_first_not_of(a-z): " << pos << " ('" << str[pos] << "')" << endl;

    // find_last_not_of: 查找最后一个 *不是* 小写字母的字符
    pos = str.find_last_not_of(lower);
    cout << "find_last_not_of(a-z) : " << pos << " ('" << str[pos] << "')" << endl;

    // substr(pos, len): 截取子串 常用技巧:配合 rfind 获取文件后缀
    size_t dot_pos = str.rfind('.');
    if (dot_pos != string::npos) 
    {
        string suffix = str.substr(dot_pos); // 从点开始截取到末尾
        cout << "提取后缀名: " << suffix << endl; // ".gz"
    }
}

void test_string_compare()
{
    string s1 = "apple";
    //string s2 = "extreme";
    //string s3 = "marathon";

    string tmp = "this is a long string apple";
    size_t pos = tmp.rfind('a');
    cout << tmp.compare(pos, 5, s1, 0, 5) << endl;

    //cout << s1.compare(s2) << endl;
    //cout << s1.compare(s3) << endl;
    //cout << s1.compare("apple") << endl;
}

void test_compare()
{
    string s1 = "apple";
    string s2 = "banana";
    string s3 = "apple";

    // "apple" vs "banana" -> 'a' < 'b' -> -1
    cout << "1. apple vs banana : " << s1.compare(s2) << " (< 0)" << endl;
    // "banana" vs "apple" -> 'b' > 'a' -> 1
    cout << "2. banana vs apple : " << s2.compare(s1) << " (> 0)" << endl;
    // "apple" vs "apple" -> 0
    cout << "3. apple vs apple  : " << s1.compare(s3) << " (== 0)" << endl;
    // 直接传 "const char*" 即可
    if (s1.compare("apple") == 0)
        cout << "4. s1 等于 \"apple\"" << endl;

    // 子串比较 (这是 compare 最强大的地方！)    
    // 场景：不想创建新 string 对象，只想比其中一部分
    string long_str = "This is a big apple tree";
    // 需求：判断 long_str 中从下标 14 开始的 5 个字符，是不是 "apple"
    // 原型: compare(pos, len, str)
    // 如果不使用 compare，你可能得写 long_str.substr(14, 5) == "apple" (产生了临时对象，慢)
    int result = long_str.compare(14, 5, "apple");
    if (result == 0)
        cout << "[高阶用法] 子串匹配成功: 找到了 apple" << endl;
    else
        cout << "[高阶用法] 子串匹配失败" << endl;
    // 更复杂的重载：子串 vs 子串
    // long_str(14, 5) vs s1(0, 5)
    if (long_str.compare(14, 5, s1, 0, 5) == 0)
        cout << "6. [骨灰用法] 子串 vs 子串: 匹配成功" << endl;
}

void test_non_member_functions()
{
    string s1 = "Hello";
    string s2 = "World";

    // 1. operator+ (拼接)
    // 场景 A: string + string
    string ret1 = s1 + " " + s2;
    // 场景 B: char* + string (成员函数做不到，只能靠非成员函数)
    string ret2 = "My " + s2;

    cout << "[拼接] s1 + s2 : " << ret1 << endl;
    cout << "[拼接] \"My \"+s2: " << ret2 << endl;

    // 2. Relational Operators (关系运算符)
    // 字典序比较: "Hello" < "World"
    cout << "\n[比较] s1 vs s2:" << endl;
    if (s1 != s2) 
        cout << "  s1 != s2" << endl;
    if (s1 < s2)  
        cout << "  s1 < s2 (H 在 W 前面)" << endl;
    if (s1 == "Hello") 
        cout << "  s1 == \"Hello\"" << endl;

    // 3. Global Swap (全局交换)
    cout << "\n[交换] 前: s1=" << s1 << ", s2=" << s2 << endl;
    std::swap(s1, s2);
    cout << "[交换] 后: s1=" << s1 << ", s2=" << s2 << endl;
}

void test_getline()
{
    string s1;
    cin >> s1;
    cout << s1 << endl;
    getline(cin, s1);
    cout << s1 << endl;
    getline(cin, s1, '*');
    cout << s1 << endl;
}

int main()
{
	//test_string1();
    //test_insert();
    //test_erase();
    //test_modifiers_from_image();
    //test_string_operations();
    //test_compare();
    //test_non_member_functions();
    test_getline();
	return 0;
}

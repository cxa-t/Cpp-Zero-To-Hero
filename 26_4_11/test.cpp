#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<memory>
#include<functional>
#include<atomic>
using namespace std;


struct Date
{
    int _year;
    int _month;
    int _day;

    Date(int year = 1, int month = 1, int day = 1)
        :_year(year)
        , _month(month)
        , _day(day)
    {
    }

    ~Date()
    {
        cout << "~Date()" << endl;
    }
};

namespace csa
{
    template<class T>
    class shared_ptr
    {
    public:
        shared_ptr(T* ptr)
            : _ptr(ptr)
            , _pcount(new atomic<int>(1))
        {
        }

        template<class D>
        shared_ptr(T* ptr, D del)
            : _ptr(ptr)
            , _pcount(new atomic<int>(1))
            , _del(del)
        {
        }

        ~shared_ptr()
        {
            if (--(*_pcount) == 0)
            {
                //delete _ptr;
                _del(_ptr);
                delete _pcount;
            }
        }

        shared_ptr(const shared_ptr<T>& sp)
            : _ptr(sp._ptr)
            , _pcount(sp._pcount)
        {
            (*_pcount)++;
        }

        // sp1 = sp4;
        // sp4 = sp4;
        // sp1 = sp2;
        shared_ptr<T>& operator=(const shared_ptr<T>& sp)
        {
            //if (this != &sp)
            if (_ptr != sp._ptr)
            {
                if (--(*_pcount) == 0)
                {
                    delete _ptr;
                    delete _pcount;
                }

                _pcount = sp._pcount;
                _ptr = sp._ptr;
                ++(*_pcount);
            }

            return *this;
        }

        T& operator*()
        {
            return *_ptr;
        }

        T* operator->()
        {
            return _ptr;
        }

        int use_count()
        {
            return *_pcount;
        }
    private:
        T* _ptr;
        //int* _pcount;
        atomic<int>* _pcount;  // 原子操作

        function<void(T*)> _del = [](T* ptr) {delete ptr; };
    };
};

//int main()
//{
//    csa::shared_ptr<Date> sp1(new Date);
//    csa::shared_ptr<Date> sp2(sp1);
//    // 拷贝构造
//    csa::shared_ptr<Date> sp3 = sp2;
//
//    csa::shared_ptr<Date> sp4(new Date);
//
//    sp1->_year++;
//    sp3->_month++;
//
//    // 赋值拷贝
//    //sp1 = sp4;
//    sp4 = sp4;
//    sp1 = sp2;
//
//	return 0;
//}

class Fclose
{
public:
    void operator()(FILE* ptr)
    {
        cout << "fclose:" << ptr << endl;
        fclose(ptr);
    }
};

template<class T>
void DeleteArrayFunc(T* ptr)
{
    delete[] ptr;
}

//int main()
//{
//    csa::shared_ptr<Date> sp1(new Date);
//
//    // 定制删除器 都可以，相对建议lambda
//    csa::shared_ptr<Date> sp3(new Date[10], [](Date* ptr) {delete[] ptr; });
//}

//int main()
//{
//    std::shared_ptr<Date> sp1(new Date);
//    std::shared_ptr<Date[]> sp2(new Date[10]);
//
//    // 定制删除器 都可以，相对建议lambda
//    std::shared_ptr<Date> sp3(new Date[10], [](Date* ptr) {delete[] ptr; });
//    std::shared_ptr<Date> sp4(new Date[5], DeleteArrayFunc<Date>);
//
//    std::shared_ptr<FILE> sp5(fopen("Test.cpp", "r"), Fclose());
//    shared_ptr<FILE> sp6(fopen("Test.cpp", "r"), [](FILE* ptr) {
//        //cout << "fclose:" << ptr << endl;
//        fclose(ptr);
//        });
//
//    std::unique_ptr<Date> up1(new Date);
//    std::unique_ptr<Date[]> up2(new Date[10]);
//    // 定制删除器 建议仿函数
//    std::unique_ptr<FILE, Fclose> up3(fopen("Test.cpp", "r"));
//
//    auto fcloseFunc = [](FILE* ptr) {fclose(ptr); };
//    std::unique_ptr<FILE, decltype(fcloseFunc)> up4(fopen("Test.cpp", "r"), fcloseFunc);
//
//    return 0;
//}

//int main()
//{
//    std::shared_ptr<Date> sp1(new Date(2024, 9, 11));
//    shared_ptr<Date> sp2 = make_shared<Date>(2024, 9, 11);
//    shared_ptr<Date> sp4;
//
//    // if (sp1.operator bool())
//    if (sp1)
//        cout << "sp1 is not nullptr" << endl;
//
//    //if (!sp4)
//    if (!sp4.operator bool())
//        cout << "sp4 is nullptr" << endl;
//
//    //shared_ptr<Date> sp5 = new Date(2024, 9, 11);
//    //unique_ptr<Date> sp6 = new Date(2024, 9, 11);
//
//    return 0;
//}

struct ListNode
{
    int _data;

    /*ListNode* _next;
    ListNode* _prev;*/
    /*std::shared_ptr<ListNode> _next;
    std::shared_ptr<ListNode> _prev;*/

    // 这里改成weak_ptr，当n1->_next = n2;绑定shared_ptr时
    // 不增加n2的引用计数，不参与资源释放的管理，就不会形成循环引用了
    std::weak_ptr<ListNode> _next;
    std::weak_ptr<ListNode> _prev;

    ~ListNode()
    {
        cout << "~ListNode()" << endl;
    }
};

//int main()
//{
//    // 循环引用 -- 内存泄露
//    std::shared_ptr<ListNode> n1(new ListNode);
//    std::shared_ptr<ListNode> n2(new ListNode);
//
//    cout << n1.use_count() << endl;
//    cout << n2.use_count() << endl;
//
//    n1->_next = n2;
//    n2->_prev = n1;
//
//    cout << n1.use_count() << endl;
//    cout << n2.use_count() << endl;
//
//    return 0;
//}

int main()
{
    std::shared_ptr<string> sp1(new string("111111"));
    std::shared_ptr<string> sp2(sp1);

    std::weak_ptr<string> wp = sp1;
    cout << wp.expired() << endl;
    cout << wp.use_count() << endl;

    // sp1和sp2都指向了其他资源，则weak_ptr就过期了
    sp1 = make_shared<string>("222222");
    cout << wp.expired() << endl;
    cout << wp.use_count() << endl;

    sp2 = make_shared<string>("333333");
    cout << wp.expired() << endl;
    cout << wp.use_count() << endl;

    wp = sp1;
    //std::shared_ptr<string> sp3 = wp.lock();
    auto sp3 = wp.lock();
    cout << wp.expired() << endl;
    cout << wp.use_count() << endl;
    sp1 = make_shared<string>("4444444");

    cout << wp.expired() << endl;
    cout << wp.use_count() << endl;

    return 0;
}

#include<thread>
#include<mutex>

struct AA
{
    int _a1 = 0;
    int _a2 = 0;

    ~AA()
    {
        cout << "~AA()" << endl;
    }
};

//int main()
//{
//    csa::shared_ptr<AA> p(new AA);
//    const size_t n = 100000;
//
//    mutex mtx;
//    auto func = [&]()
//    {
//        for (size_t i = 0; i < n; ++i)
//        {
//            // 这里智能指针拷贝会++计数
//            csa::shared_ptr<AA> copy(p);
//            {
//                unique_lock<mutex> lk(mtx);
//                copy->_a1++;
//                copy->_a2++;
//            }
//        }
//    };
//
//    thread t1(func);
//    thread t2(func);
//
//    t1.join();
//    t2.join();
//
//    cout << p->_a1 << endl;
//    cout << p->_a2 << endl;
//
//    cout << p.use_count() << endl;
//
//    return 0;
//}

//int main()
//{
//    // 申请一个1G未释放，这个程序多次运行也没啥危害
//    // 因为程序马上就结束，进程结束各种资源也就回收了
//    char* ptr = new char[1024 * 1024 * 1024];
//    cout << (void*)ptr << endl;
//
//    return 0;
//}
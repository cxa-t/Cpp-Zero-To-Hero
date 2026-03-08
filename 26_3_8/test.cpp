#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution 
{
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped)
    {
        stack<int> st;//辅助栈
        //记录出栈序列的位置
        auto popit = popped.begin();
        auto pushit = pushed.begin();
        while (pushit != pushed.end())
        {
            st.push(*pushit);
            pushit++;

            while (!st.empty() && st.top() == *popit )
            {
                st.pop();
                popit++;
            }
        }

        if (st.empty())
            return true;
        else
            return false;
    }
};

int main()
{
    Solution su;
    vector<int> pushed = { 0,2,1 }, popped = { 0,1,2 };
    su.validateStackSequences(pushed, popped);
    return 0;
}

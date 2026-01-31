#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>
using namespace std;

bool is_letter(const char& ch)
{
    if (ch >= 'a' && ch <= 'z')
    {
        return true;
    }
    if (ch >= 'A' && ch <= 'Z')
    {
        return true;
    }
    return false;
}

string reverseOnlyLetters(string s)
{
    int left = 0;
    int right = s.size() - 1;
    while (left < right)
    {
        while (left < right && !(is_letter(s[left])))
        {
            left++;
        }
        while (left < right && !(is_letter(s[right])))
        {
            right--;
        }
        swap(s[left++], s[right--]);
    }
    return s;
}

int firstUniqChar(string s)
{
    int count[26] = { 0 };
    for (auto letter : s)
    {
        count[letter - 'a']++;
    }
    for (int i = 0; i < s.size(); i++)
    {
        if (count[s[i] - 'a'] == 1)
        {
            return i;
        }
    }
    return -1;
}

string addStrings(string num1, string num2)
{
    string s;
    int end1 = num1.size() - 1;
    int end2 = num2.size() - 1;
    int jin = 0;
    while (end1 >= 0 && end2 >= 0)
    {
        int sum = (num1[end1] - '0') + (num2[end2] - '0') + jin;
        jin = sum / 10;
        sum %= 10;
        s += (sum + '0');
        end1--;
        end2--;
    }
    while (end1 >= 0)
    {
        int sum = (num1[end1] - '0') + jin;
        jin = sum / 10;
        sum %= 10;
        s += (sum + '0');
        end1--;
    }
    while (end2 >= 0)
    {
        int sum = (num2[end2] - '0') + jin;
        jin = sum / 10;
        sum %= 10;
        s += (sum + '0');
        end2--;
    }
    if (jin != 0)
        s += (jin + '0');
    reverse(s.begin(), s.end());
    return s;
}

int main()
{
    //string s("ab-cd");
    //reverseOnlyLetters(s);
    return 0;
}

#pragma once

#include <iostream>
using namespace std;

namespace csa
{
	class string
	{
	public:
		string()
			:_str(new char[1] {'\0'})
		{

		}


	private:
		char* _str;
		size_t _size;
		size_t _capacity;

	};
}
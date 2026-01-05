#pragma once

#include <iostream>
#include <cassert>
#include <stdbool.h>
#include <stdlib.h>

using namespace std;

namespace csa
{
	typedef int STDataType;
	
	typedef struct Stack
	{
		STDataType* a;
		int top;
		int capacity;
	}ST;

	void STInit(ST& ps, int n = 4);
	void STDestroy(ST& ps);
	void STPush(ST& ps, STDataType x);
	void STPop(ST& ps);
	STDataType STTop(ST& ps);
	int STSize(ST& ps);
	bool STEmpty(ST& ps);

	void STModify(ST& ps,STDataType x);
	STDataType& STTop2(ST& ps);
}



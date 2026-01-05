#define _CRT_SECURE_NO_WARNINGS

#include "head.h"

namespace csa
{
	void STInit(ST& ps, int n)
	{
		ps.a = (STDataType*)malloc(n * sizeof(STDataType));
		ps.top = 0;
		ps.capacity = n;
	}

	void STDestroy(ST& ps)
	{
		free(ps.a);
		ps.a = nullptr;
		ps.capacity = ps.top = 0;
	}

	void STPush(ST& ps, STDataType x)
	{
		if (ps.capacity == ps.top)
		{
			int newcapacity = ps.capacity * 2l;
			STDataType* tmp = (STDataType*)realloc(ps.a, sizeof(STDataType) * newcapacity);
			if (tmp == nullptr)
			{
				perror("realloc");
				exit(-1);
			}
			ps.a = tmp;
			ps.capacity = newcapacity;
		}
		ps.a[ps.top++] = x;
	}
	
	int STSize(ST& ps)
	{
		return ps.top;
	}
	
	bool STEmpty(ST& ps)
	{
		return ps.top == 0;
	}

	void STPop(ST& ps)
	{
		assert(!STEmpty(ps));
		ps.top--;
	}

	STDataType STTop(ST& ps)
	{
		assert(!STEmpty(ps));
		return ps.a[ps.top - 1];
	}

	void STModify(ST& ps, STDataType x)
	{
		assert(!STEmpty(ps));
		ps.a[ps.top - 1] = x;
	}

	STDataType& STTop2(ST& ps)
	{
		assert(!STEmpty(ps));
		return ps.a[ps.top - 1];
	}
}
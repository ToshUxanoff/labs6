#include "stdafx.h"
#include <iostream>
#include <vector>

template <class It>
void print(It begin, It end)
{
	for (It i = begin; i != end; ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << std::endl;
}

template<class It, class Cmp>
void qsort(It begin, It end, Cmp cmp)
{
	It ITend = end;
	--end;
	It Iterator = Sorter(begin, end, cmp);
	It ItNext = Iterator;
	if (ItNext != end)
	{
		++ItNext;
	}
	if (begin != Iterator)
	{
		qsort(begin, Iterator, cmp);
	}
	if (ItNext!= end) 
	{
		qsort(ItNext, ITend, cmp);
	}
}

template<class It, class Cmp>
It Sorter(It begin, It end, Cmp cmp)
{
	It Position = begin;
	while (true)
	{
		It i = end;
		while ((Position < i) && cmp(*Position, *i))
		{
			--i;
		}

		if (i != Position)
		{
			std::swap(*Position, *i);
		}
		else
		{
			return Position;
			break;
		}
		Position = i;
		i = begin;
		while ((Position > i) && cmp(*i, *Position))
		{
			++i;
		}
		if (i != Position)
		{
			std::swap(*Position, *i);
		}
		else
		{
			return Position;
			break;
		}
		Position = i;
	}
}

int main() {
	std::vector<int> test{ 11,5,7,12,14,9,4,124,54259,3295803,19,459,53280,10,0 };
	print(test.begin(), test.end());
	qsort(test.begin(), test.end(), std::less<int>());
	std::cout << "\n------------------------\n";
	print(test.begin(), test.end());
	system("pause");
	return 0;
}

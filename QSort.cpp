#include "stdafx.h"
#include <iostream>
#include <vector>

template<class It, class Cmp>
void qsort(It beg, It end, Cmp cmp)
{
	if (beg != end) {
		It Left = beg;
		It Right = end;
		It Piv = beg;
		++Left;
		while (Left != Right) 
		{
			if (cmp(*Left, *Piv))
			{
				++Left;
			}
			else
			{
				--Right;
				while ((Left != Right) && cmp(*Piv, *Right))
				{
					--Right;
				}
				if (Left != Right)
				{
					std::swap(*Left, *Right);
				}
			}
		}
		--Left;
		std::iter_swap(Piv, Left);
		qsort(beg, Left, cmp);
		qsort(Right, end, cmp);
	}
}
template <class T>
void print(std::vector <T> vect)
{
	for (auto& i = vect.begin(); i != vect.end(); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << std::endl;
}


int main() {
	
	std::vector<int> test;
	for (int i = 0; i < 10000; ++i)
	{
		test.push_back(rand() % 1000);
	}
	print(test);
	std::cout << "\n------------------------\n";

	qsort(test.begin(), test.end(), std::less<int>());
	print(test);
	system("pause");
	return 0;
}

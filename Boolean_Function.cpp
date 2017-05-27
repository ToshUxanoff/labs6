#ifndef __BOOLEAN_FUNCTION_INCLUDED__
#define __BOOLEAN_FUNCTION_INCLUDED__

#include <string>
#include <vector>
#include <math.h>
class boolean_function
{
public:
	using value_type = bool;
	using size_type = size_t;
	using reference = std::vector<value_type>::reference;
	using const_reference = std::vector<value_type>::const_reference;

	using iterator = typename std::vector<value_type>::iterator;
	using const_iterator = typename std::vector<value_type>::const_iterator;

	std::vector<bool> ValVect; //Вектор значений функции
	bool FuncLength(size_t length)
	{
		size_t i = 0;
		while (length)
		{
			i += length % 2;
			length /= 2;
		}
		if (i != 1)
		{
			throw std::exception("Wrong size");
		}
		else
		{
			return true;
		}
	}
public:

	// возвращает функцию которая равна xn с размерностью dimension
	// пример 1
	// n = 0
	// dimension = 3
	// вернется функция "01010101"
	// пример 2
	// n = 1
	// dimension = 4
	// вернется функция "0011001100110011"
	static boolean_function var(size_t n, size_t dimension)
	{
		std::vector<bool> table;
		
		do
		{
			for (size_t i = 0; i < pow(2, n); ++i)
			{
				table.push_back(0);
			}
			for (size_t i = 0; i < pow(2, n); ++i)
			{
				table.push_back(1);
			}
		} while (table.size() < pow(2, dimension));
		return boolean_function(table);
	}
	// тождественный ноль "от dimension переменных"
	static boolean_function zero(size_t dimension)
	{	
		return boolean_function(dimension);
	}
	// тождественная единица "от dimension переменных"
	static boolean_function one(size_t dimension)
	{	
		return ~boolean_function(dimension);
	}
	static boolean_function from_anf(std::vector<value_type> v)
	{
		std::vector<bool> ValueVect;
		
		for (size_t i = 0; i < v.size(); ++i)
		{
			ValueVect.push_back(v[0]);
			for (size_t j = 0; j < v.size() - 1; ++j)
			{
				if (v[j] == v[j + 1])
				{
					v[j] = false;
					continue;
				}
				v[j] = v[j] + v[j + 1];
			}
		}
		return boolean_function(ValueVect);
	}
	boolean_function()
	{}
	// задает фунцию тождественного нуля от n переменных
	boolean_function(size_t n) 
	{
		for (int i = 0; i < pow(2, n); ++i)
		{
			ValVect.push_back(false);
		}
	}
//
//	// задает фунцию от n переменных. значение равно value
//	// пример
//	// пусть value = 14, т.е. 0...00001110 в двоичной системе
//	// а n = 3
//	// тогда АНФ boolean_function будет равна x + y + xy + zx + zy + zyx
	boolean_function(unsigned long long value, size_type n)
	{
		
		for (int i = 0; i < pow(2, n); ++i)
		{

			ValVect.push_back(value % 2);
			value /= 2;
		}
		
	}
//
//	// пусть table = "01110000"
//	// тогда АНФ boolean_function будет равна x + y + xy + zx + zy + zyx
	boolean_function(const std::string& table)
	{
		if (FuncLength(table.size()))
		{
			for (size_t i = 0; i < table.size(); ++i)
			{
				if (table[i] == '0')
				{
					ValVect.push_back(0);
				}
				else
				{
					ValVect.push_back(1);
				}

			}
		}
	}
//
//	// пусть table = {true, false, false, true};
//	// тогда АНФ boolean_function будет равна x + y + 1
	boolean_function(const std::vector<value_type>& table)
	{
		if (FuncLength(table.size()))
		{
			ValVect = table;
		}
	}
	boolean_function(const std::initializer_list<bool> vars)
	{
		if (FuncLength(vars.size()))
		{
			for (auto&a : vars)
			{
				ValVect.push_back(a);
			}
		}
	}		////
	boolean_function(const boolean_function& table)
	{
		if (FuncLength(table.size()))
		{
			ValVect = table.ValVect;
		}
	}
//
	boolean_function& operator=(const boolean_function& rhs)
	{
		ValVect = rhs.ValVect;
		return *this;
	}
// сложение по модулю 2
	// если разное количество переменных - исключение
	boolean_function& operator += (const boolean_function& rhs)
	{
		if (ValVect.size() != rhs.ValVect.size())
		{
			throw std::exception("wrong format");
		}
		for (size_t i = 0; i < ValVect.size(); ++i)
		{	
			if (ValVect[i] == rhs.ValVect[i])
			{
				ValVect[i] = false;
			}
			else
			{
				ValVect[i] = ValVect[i] + rhs.ValVect[i];
			}	
		}
		return *this;
	}
	// конъюнкция
	// если разное количество переменных - исключение
	boolean_function& operator *= (const boolean_function& rhs)
	{
		if (ValVect.size() != rhs.ValVect.size())
		{
			throw std::exception("wrong format");
		}
		for (size_t i = 0; i < ValVect.size(); ++i)
		{
			ValVect[i] = ValVect[i] * rhs.ValVect[i];
		}
		return *this;
	}
	// дизъюнкция
	// если разное количество переменных - исключение
	boolean_function& operator |= (const boolean_function& rhs)
	{
		if (ValVect.size() != rhs.ValVect.size())
		{
			throw std::exception("wrong format");
		}
		for (size_t i = 0; i < ValVect.size(); ++i)
		{
			ValVect[i] = ValVect[i] + rhs.ValVect[i];
		}
		return *this;
	}
	// побитовое отрицание
	boolean_function operator ~ ()
	{
		ValVect.flip();
		return *this;
	}
//
// true если функции равны
//  иначе false
	bool operator == (const boolean_function& obj) const
	{
		size_t lessSize;
		if (ValVect.size() < obj.ValVect.size())
		{
			lessSize = ValVect.size();
		}
		else
		{
			lessSize = obj.ValVect.size();
		}
		for (size_t i = 0; i < lessSize; ++i)
		{
			if (ValVect[i] != obj.ValVect[i])
			{
				return false;
			}
		}
		return true;
	}
//
//	// true если одна функция сравнима и больше или равна rhs
//	// false если сравнима и меньше rhs
//	// logic_error если фунции не сравнимы
	bool operator >= (const boolean_function& rhs) const
	{
		if (ValVect.size() != rhs.ValVect.size())
		{
			throw std::logic_error("not comparable");
		}
		int prov = 0;
		if (ValVect == rhs.ValVect)
		{
			return true;
		}
		for (size_t i = 0; i < ValVect.size(); i++)
		{	
			if ((size_t)ValVect[i] < (size_t)rhs.ValVect[i])
			{
				if (prov == 1) 
				{
					throw std::logic_error("not comparable");
				}
				prov = -1;
			}
			else if ((size_t)ValVect[i] > (size_t)rhs.ValVect[i])
			{
				if (prov == -1)
				{
					throw std::logic_error("not comparable");
				}
				prov = 1;
			}
		}
		return (prov == 1);
	}
//
	reference operator[](size_type ind)
	{
		return ValVect[ind];
	}
	const_reference operator[](size_type ind) const
	{
		return ValVect[ind];
	}

	reference at(size_type ind)
	{
		if (ind >= ValVect.size())
		{
			throw std::exception("Out of range");
		}
		return ValVect[ind];
	}
	const_reference at(size_type ind) const
	{
		if (ind >= ValVect.size())
		{
			throw std::exception("Out of range");
		}
		return ValVect[ind];
	}
//
	iterator begin()
	{
		return ValVect.begin();
	}
	iterator end()
	{
		return ValVect.end();
	}
//
	const_iterator cbegin() const
	{
		return ValVect.cbegin();
	}
	const_iterator cend() const
	{
		return ValVect.cend();
	}
//
	// длина столбца функции
	size_type size() const throw()
	{
		return ValVect.size();
	}
	// количество переменных
	size_type dimension() const throw()
	{
		return log2(ValVect.size());
	}

	// возвращает значение функции
	// пусть boolean_function задает функцию f(x, y, z)
	// тогда функция вернет f(vars[0], vars[1], vars[2])
	bool operator()(const std::vector<bool>& vars) const
	{
		size_t result = 0;
		for (size_t i = 0; i < vars.size(); ++i)
		{
			result += pow(2, i)*vars[i];
		}
		return this->at(result);

	}

	bool operator()(const std::initializer_list<bool> vars) const
	{
		int t = 0;
		int i = 0;
		for (auto &it : vars)
		{
			t += pow(2, i)*it;
			++i;
		}
		return this->at(t);
	}


	// T(x1, x2, ..., xN) - текущая функция
	// operator вернет новую функцию, которая равна композиции G = T(fs[0], fs[1], ..., fs[N-1])
	boolean_function operator()(const std::vector<boolean_function>& fs) const
	{
		
		if (fs.size() == 0)
		{
			return boolean_function();
		}

		size_t dim = 0;
		for (auto & function : fs)
		{
			if (function.dimension() > dim) 
			{
				dim= function.dimension();
			}
		}

		boolean_function result(dim);
		std::vector<bool> variables;
		for (size_type i = 0; i < result.ValVect.size(); ++i) 
		{
			variables.clear();
			for (auto & function : fs) 
			{
				variables.push_back(function.ValVect[i % function.size()]);
			}
			result.ValVect[i] = (*this)(variables);
		}

		return result;
	}

	boolean_function operator()(const std::initializer_list<boolean_function> vars) const
	{
		std::vector<boolean_function> fs = vars;
		return (*this)(fs);
	}

	bool is_monotone() const
	{
		if (ValVect.size() == 0)
		{
			throw std::exception("Empty");
		}
		for (size_t i = 0; i < ValVect.size(); ++i) 
		{ 
			for (size_t j = 0; j < dimension(); ++j) 
			{ 
				if ((size_t(pow(2, j)) & i) == 0) 
				{
					if (ValVect[i + size_type(pow(2, j))] < ValVect[i]) 
					{ 
						return false;
					}
				}
			}
		}
		return true;
	}
	bool is_symmetric() const 
	{
		std::vector<bool> BufVect = ValVect;
		for (size_t i = 0; i < BufVect.size(); ++i)
		{
			if (BufVect[i] == BufVect[BufVect.size() - i - 1])
			{
				return false;
			}
		}
		return true;
	}
	bool is_linear() const
	{
		std::vector<bool> Anf = this->anf();
		for (size_t i = 0; i < Anf.size(); ++i)
		{
			if (floor(log2(i)) != log2(i) && Anf[i] == true)
			{
					return false;
			}
		}
		return true;
	}
	bool is_T1() const
	{
		return ValVect[ValVect.size()-1] == 1;
	}
	bool is_T0() const
	{
		return ValVect[0] == 0;
	}
 //равновесная ли
	bool is_balanced() const
	{
		return (weight() == (size() / 2));
	}
	size_t weight() const
	{
		size_t result = 0;
		for (size_t i = 0; i < ValVect.size(); ++i)
		{
			if (ValVect[i] == true)
			{
				++result;
			}
		}
		return result;
	}

	bool is_functionally_complete_system() const
	{
		return (!is_monotone() && !is_symmetric() & !is_linear() && !is_T1() && !is_T0());
	}

	// Возвращает АНФ функции
	std::vector<value_type> anf() const //Метод Паскаля
	{
		std::vector<bool> AnfVect;
		std::vector<bool> BufVect = ValVect;
		for (size_t i = 0; i < size(); ++i)
		{
			AnfVect.push_back(BufVect[0]);
			for (size_t j = 0; j < size() - 1; ++j)
			{
				if (BufVect[j] ==  BufVect[j + 1])
				{
					BufVect[j] = false;
					continue;
				}
				BufVect[j] = BufVect[j] + BufVect[j + 1];
			}
		}
		return AnfVect;
	}
};
boolean_function operator + (const boolean_function& a, const boolean_function& b)
{
	boolean_function newA = a;
	return newA += b;
}
//
boolean_function operator * (const boolean_function& a, const boolean_function& b)
{
	boolean_function newA = a;
	return newA *= b;
}
//
boolean_function operator | (const boolean_function& a, const boolean_function& b)
{
	boolean_function newA = a;
	return newA |= b;
}
//
bool operator != (const boolean_function& a, const boolean_function& b)
{
	return !(a == b);
}
#endif  __BOOLEAN_FUNCTION_INCLUDED__

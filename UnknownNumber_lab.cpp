#include "stdafx.h"
#include <iostream>

#include <string>
#include <vector>
#include <map>

#include <algorithm>
#include <numeric>
#include "cmath"

enum Grade
{
	F = 1,
	D,
	C,
	B,
	A
};

struct Student
{
	std::string FIO;
	std::string Group;
	std::map<std::string, Grade> Grades;
};

std::vector<Student> LoadStudents()
{
	return {
		{
			"Anna", "G7",
			{
				{ "math", Grade::A },
				{ "cs", Grade::A },
				{ "english", Grade::A },
				{ "dutch", Grade::B },
				
			}
		},
		{
			"Petr", "G7",
			{
				{ "math", Grade::A },
				{ "cs", Grade::B },
				{ "dutch", Grade::C },
				
			}
		},
		{
			"Vova", "G1",
			{
				{ "math", Grade::F },
				{ "english", Grade::F },
				
			}
		},
		{
			"Vasya", "G3",
			{
				{ "math", Grade::F },
				{ "english", Grade::F },
				{ "cs", Grade::B },
				{ "dutch", Grade::C },
				
			}
		},
		{
			"Anton", "G4",
			{
				{ "math", Grade::F },
				{ "english", Grade::F },
				{ "dutch", Grade::C },
				{ "cs", Grade::C },
				
			}
		},
		{
			"Masha", "G2",
			{
				{ "math", Grade::A },
				
			}
		},
		{
			"Sasha", "G6",
			{
				{ "english", Grade::F },
				{ "russian", Grade::F },
				{ "dutch", Grade::F },
				
			}
		},
		{
			"Jeka", "G2",
			{
				{ "english", Grade::A },
				
			}
		},
		{
			"Sveta", "G3",
			{
				
			}
		}
	};
}

struct NewSubj
{
	void operator() (Student& a)
	{
		float Mark_Lit = 0;
		for (auto itLit = a.Grades.begin(); itLit != a.Grades.end(); ++itLit)
		{
			Mark_Lit += itLit->second;
		}
		Mark_Lit /= a.Grades.size();
		Grade Mark_Lit2 = (Grade)(int)ceil(Mark_Lit);
		a.Grades.insert(std::pair<std::string, Grade>("Russian Literature", Mark_Lit2));
	}
};

struct mathBcsA
{
	Grade mathgrade = Grade::A;
	Grade csgrade = Grade::B;
	void operator()(const Student& s) const
	{
		if (s.Grades.count("math") && s.Grades.count("cs") && s.Grades.find("math")->second == mathgrade && s.Grades.find("cs")->second == csgrade)
		{
			std::cout << s.FIO << " : Math = A, Cs = B "  << std::endl;
		}
	}
};

struct PrintbyGroup
{
	std::string neededGroup;
	void operator()(const Student& s) const
	{
		if (s.Group == neededGroup)
		{
			std::cout << s.FIO << " studies in " << s.Group << std::endl;
		}
	}
};

struct PrintbyDeutsch
{
	void operator()(const Student& s) const
	{
		if (s.Grades.count("dutch") )
		{
			std::cout << s.FIO << " learns Deutsch " << std::endl;
		}
		else
		{
			std::cout << s.FIO << "  is not learns Deutsch " << std::endl;
		}
	}
};

struct subj_compare
{
	bool operator()(const Student &a, const Student &b)
	{
		return (a.Grades.size() < b.Grades.size());
	}
};
struct math_compare
{
	bool operator()(const Student &a, const Student &b)
	{
		if (a.Grades.count("math") && b.Grades.count("math"))
		{
			return (a.Grades.find("math")->second < b.Grades.find("math")->second);
		}
		else return 0;
	}
};
struct mark_compare
{
	bool operator()(const Student &a, const Student &b)
	{
		float Mark_A = 0;
		float Mark_B = 0;
		for (auto ita = a.Grades.begin(); ita != a.Grades.end(); ++ita)
		{
			Mark_A += ita->second;
		}
		Mark_A /= a.Grades.size();

		for (auto itb = b.Grades.begin(); itb != b.Grades.end(); ++itb)
		{
			Mark_B += itb->second;
		}
		Mark_B /= b.Grades.size();
		return Mark_A < Mark_B;
	}
};
int main()
{
	std::vector<Student> students = LoadStudents();

	std::cout << "------------------\n";
	//Math - A, cs - B
    std::for_each(students.begin(), students.end(), mathBcsA());
	
	std::cout << "------------------\n";
	// find students from G7
	std::for_each(students.begin(), students.end(), PrintbyGroup{ "G7" });
	std::cout << "------------------\n";
	
	// deutsch marks
	std::for_each(students.begin(), students.end(), PrintbyDeutsch());
	std::cout << "------------------\n";

	//insert Litra
	std::for_each(students.begin(), students.end(), NewSubj());


	// max subjects
	auto it = std::max_element(students.begin(), students.end(), subj_compare());
	std::cout <<"More subjects : "<< it->FIO <<std::endl;
	//best matan
	std::cout << "------------------\n";
	auto it2 = std::max_element(students.begin(), students.end(), math_compare());
	std::cout << "Best math : " << it2->FIO << " ; Mark = " << it2->Grades.find("math")->second << std::endl;
	//worst mid mark
	std::cout << "------------------\n";
	auto it3 = std::min_element(students.begin(), students.end(), mark_compare());
	std::cout << "Worst middle mark : " << it3->FIO  << std::endl;
	
	system("pause");
}

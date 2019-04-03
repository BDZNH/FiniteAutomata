#include "FiniteAutomata.h"



FiniteAutomata::FiniteAutomata()
{
}


FiniteAutomata::~FiniteAutomata()
{
}

size_t FiniteAutomata::size()
{
	return num_state;
}

bool check(const state& t)
{
	if (t < 999 && t >= 0)
		return true;
	else
		return false;
}

//friend std::istream &operator>>(std::istream  &input, FiniteAutomata &D)
//{
//	//input >> D.feet >> D.inches;
//	std::cout << "input the number of state of the FA:" << std::endl;
//	input >> D.num_state;
//	return input;
//}
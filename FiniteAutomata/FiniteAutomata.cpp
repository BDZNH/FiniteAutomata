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

bool FiniteAutomata::out()
{
	std::ofstream ofile;
	ofile.open("FA.ADS");
	//应当考虑未能成功打开的情况。
	ofile << "# CTCT ADS auto-generated\n" << std::endl;
	ofile << "FA" << std::endl;
	ofile << "State size:" << std::endl;
	return false;
}

bool FiniteAutomata::check(const state& t)
{
	if (t < 999 && t >= 0)
		return true;
	else
		return false;
}

std::istream& operator>>(std::istream& input, FiniteAutomata& D)
{
	
	std::cout << "input the number of state of the FA (type: unsigned int):" << std::endl;
	input >> D.num_state;
	state temp;
	std::cout << "input the accepted state of the FA(type: unsigned int ,end with -1):" << std::endl;
	while (input >> temp)
	{
		if (temp == -1)
			break;
		if (D.check(temp))
		{
			D.accepting.push_back(temp);
		}
	}
	std::cout << "input the transition relation of the FA(type: unsigned int ,end with -1)" << std::endl;
	std::cout << "Example: 2 0 1 (for transition labeled 0 from state 2 to state 1).  :" << std::endl;
	Trnasition trans;
	while (input >> trans.Q0)
	{
		if (trans.Q0 == -1)
			break;
		input >> trans.T >> trans.Q1;
		if (D.check(trans.Q0) && D.check(trans.T) && D.check(trans.Q1))
		{
			D.Trans.push_back(trans);
		}
		else
		{
			std::cout << "Invalid argument: " << trans.Q0 << " " << trans.T << " " << trans.Q1 << std::endl;
		}
		trans.Q0 = 0;
		trans.T = 0;
		trans.Q1 = 0;
	}
	return input;
}

std::ostream & operator<<(std::ostream & output, FiniteAutomata & D)
{
	output << D.size() << std::endl;
	// TODO: 在此处插入 return 语句
	return output;
}

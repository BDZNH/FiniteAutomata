#include "FiniteAutomata.h"



FiniteAutomata::FiniteAutomata()
{
	quite = false;
}


FiniteAutomata::~FiniteAutomata()
{
}

size_t FiniteAutomata::size()
{
	return Q.size();
}

bool FiniteAutomata::perform()
{
	/*std::ofstream ofile;
	ofile.open("FA.ADS");*/
	////应当考虑未能成功打开的情况。
	//ofile << "# CTCT ADS auto-generated\n" << std::endl;
	//ofile << "FA\n" << std::endl;
	//ofile << "State size (State set will be (0,1....,size-1)):\n# <-- Enter state size, in range 0 to 2000000, on line below." << std::endl;
	//ofile << num_state << std::endl;
	//ofile << "\nMarker states:\n# <-- Enter marker states, one per line.\n# To mark all states, enter *.\n# If no marker states, leave line blank.\n# End marker list with blank line." << std::endl;
	//auto it = F.begin();
	//for (; it != F.end(); ++it)
	//{
	//	ofile << *it << std::endl;
	//}
	//ofile << "\nVocal states:\n# <-- Enter vocal output states, one per line.\n# Format: State  Vocal_Output.Vocal_Output in range 10 to 99.\n# Example : 0 10\n# If no vocal states, leave line blank.\n# End vocal list with blank line." << std::endl;
	//ofile << "Transitions:\n# <-- Enter transition triple, one per line.\n# Format: Exit_(Source)_State  Transition_Label  Entrance_(Target)_State.\n# Transition_Label in range 0 to 999.\n# Example: 2 0 1 (for transition labeled 0 from state 2 to state 1)." << std::endl;
	////auto itt = Trans.begin();
	//for (size_t i = 0; i < Trans.size(); ++i)
	//{
	//	ofile << Trans[i].Q0 << " " << Trans[i].T << " " << Trans[i].Q1 << std::endl;
	//}

	// 输出数据到默认的文件“FA.ADS”
	std::ofstream ofile;
	ofile.open("FA.ADS");
	if (!ofile.is_open())
	{
		std::cout << "Can't open file: FA.ADS" << std::endl;
		return false;
	}
	ofile << (*this);
	ofile.close();
	return true;
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
	if (!D.quite)
	{
		std::cout << "input the number of state of the FA (type: unsigned int):" << std::endl;
	}
	
	input >> D.num_state;
	state temp;
	
	std::vector<state>::iterator result;
	std::vector<label>::iterator result2;
	if (!D.quite)
	{
		std::cout << "input the accepted state of the FA(type: unsigned int ,end with -1):" << std::endl;
	}
	
	while (input >> temp)
	{
		if (temp == -1)
			break;
		if (D.check(temp))
		{
			//D.F.push_back(temp);
			result = std::find(D.F.begin(), D.F.end(), temp);
			if (result == D.F.end())
			{
				D.F.push_back(temp);
			}
		}
		else
		{
			std::cout << "Invalid argument: " << temp << std::endl;
		}

	}

	if (!D.quite)
	{
		std::cout << "input the transition relation of the FA(type: unsigned int ,end with -1)" << std::endl;
		std::cout << "Example: 2 0 1 (for transition labeled 0 from state 2 to state 1).  :" << std::endl;
	}
	
	Trnasition trans;
	
	// 输入转移关系
	while (input >> trans.Q0)
	{
		if (trans.Q0 == -1)
			break;
		input >> trans.T >> trans.Q1;
		if (D.check(trans.Q0) && D.check(trans.T) && D.check(trans.Q1)) //如果输入的转移关系有效
		{
			// 将状态存入状态集
			D.Trans.push_back(trans);
			result = std::find(D.Q.begin(), D.Q.end(), trans.Q0);
			if (result == D.Q.end())
			{
				D.Q.push_back(trans.Q0);
			}
			result = std::find(D.Q.begin(), D.Q.end(), trans.Q1);
			if (result == D.Q.end())
			{
				D.Q.push_back(trans.Q1);
			}

			// 将“输入字符”保存
			result2 = std::find(D.V.begin(), D.V.end(), trans.T);
			if (result2 == D.V.end())
			{
				D.V.push_back(trans.T);
			}
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
	output << "# CTCT ADS auto-generated\n" << std::endl;
	output << "FA\n" << std::endl;
	output << "State size (State set will be (0,1....,size-1)):\n# <-- Enter state size, in range 0 to 2000000, on line below." << std::endl;
	output << D.num_state << std::endl;
	output << "\nMarker states:\n# <-- Enter marker states, one per line.\n# To mark all states, enter *.\n# If no marker states, leave line blank.\n# End marker list with blank line." << std::endl;
	auto it = D.F.begin();
	for (; it != D.F.end(); ++it)
	{
		output << *it << std::endl;
	}
	output << "\nVocal states:\n# <-- Enter vocal output states, one per line.\n# Format: State  Vocal_Output.Vocal_Output in range 10 to 99.\n# Example : 0 10\n# If no vocal states, leave line blank.\n# End vocal list with blank line.\n" << std::endl;
	output << "Transitions:\n# <-- Enter transition triple, one per line.\n# Format: Exit_(Source)_State  Transition_Label  Entrance_(Target)_State.\n# Transition_Label in range 0 to 999.\n# Example: 2 0 1 (for transition labeled 0 from state 2 to state 1)." << std::endl;
	//auto itt = Trans.begin();
	for (size_t i = 0; i < D.Trans.size(); ++i)
	{
		output << D.Trans[i].Q0 << " " << D.Trans[i].T << " " << D.Trans[i].Q1 << std::endl;
	}
	return output;
}

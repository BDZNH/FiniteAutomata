#ifndef FiniteAutomata_H
#define FiniteAutomata_H

#include <vector>
#include <iostream>

using namespace std;

typedef size_t state;
typedef size_t label;

struct Trnasition
{
	state Q0;
	label T;
	state Q1;
	Trnasition() :Q0(0), T(0), Q1(0) {};
};

class FiniteAutomata
{
public:
	FiniteAutomata();
	~FiniteAutomata();
	size_t size();
	bool out();
	friend std::istream &operator>>(std::istream  &input, FiniteAutomata &D)
	{
		//input >> D.feet >> D.inches;
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
				D.accepted.pushback(temp);
			}
		}
		std::cout << "input the accepted state of the FA(type: unsigned int ,end with -1)" << std::endl;
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
	
private:
	bool check(const state& t);
	std::vector<Trnasition> Trans;
	//std::vector<state> initial;
	std::vector<state> accepted;
	rsize_t num_state;
};



#endif // !FiniteAutomata_H


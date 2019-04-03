#ifndef FiniteAutomata_H
#define FiniteAutomata_H

#include <iostream>
#include <vector>
#include <fstream>


//using namespace std;

typedef int state;
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
	friend std::istream& operator>>(std::istream& input, FiniteAutomata& D);
	friend std::ostream& operator<<(std::ostream& output, FiniteAutomata& D);
	
private:
	bool check(const state& t);
	std::vector<Trnasition> Trans;
	//std::vector<state> initial;
	std::vector<int> F;
	std::vector<state> Q;
	std::vector<label> V;
	size_t num_state;
};



#endif // !FiniteAutomata_H


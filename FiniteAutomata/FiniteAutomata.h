/******************************************************************
一个用来生成TCT自动工具箱所用的ADS文件的小工具。
******************************************************************/


#ifndef FiniteAutomata_H
#define FiniteAutomata_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <assert.h>
#include "DFA.h"


typedef int state;
typedef int label;

struct Transition
{
	state stprime;
	label T;
	state stdest;
	Transition() :stprime(0), T(0), stdest(0) {};
	bool operator==(const Transition &D)
	{
		return (stprime == D.stprime&&T == D.T&&stdest == D.stdest);
	}
	bool operator!=(const Transition &D)
	{
		return !(*this==D);
	}
	bool operator<(const Transition &D)
	{
		if (stprime == D.stprime)
		{
			return (T < D.T);
		}
		else
		{
			return (stprime < D.stprime);
		}
	}
};

class FiniteAutomata
{
public:
	FiniteAutomata();
	FiniteAutomata(std::string str);
	FiniteAutomata(DFA &dfa);
	~FiniteAutomata();
	FiniteAutomata& reconstruct(std::string str);
	size_t size();
	std::string FA();
	bool perform();
	bool perform(std::string filepath);
	bool perform(DFA &dfa, std::string filepath);
	FiniteAutomata& clear();
	friend std::istream& operator>>(std::istream& input, FiniteAutomata& D);  
	friend std::ostream& operator<<(std::ostream& output, FiniteAutomata& D); 
	bool operator==(FiniteAutomata& D);                                       
	bool quite;
private:
	bool analyze(std::string& str);
	bool check(const state& t);
	std::vector<Transition> Trans;
	//std::vector<state> initial;
	std::vector<state> F;
	std::vector<state> Q;
	std::vector<label> V;
	std::string theFA;
	size_t num_state;
};



#endif // !FiniteAutomata_H


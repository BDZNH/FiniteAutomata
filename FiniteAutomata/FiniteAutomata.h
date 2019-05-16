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
#include <assert.h>


typedef int state;
typedef int label;

struct Trnasition
{
	state Q0;
	label T;
	state Q1;
	Trnasition() :Q0(0), T(0), Q1(0) {};
	bool operator==(const Trnasition &D)
	{
		return (Q0 == D.Q0&&T == D.T&&Q1 == D.Q1);
	}
	bool operator!=(const Trnasition &D)
	{
		return !(Q0 == D.Q0&&T == D.T&&Q1 == D.Q1);
	}
};

class FiniteAutomata
{
public:
	FiniteAutomata();
	FiniteAutomata(std::string &str);
	~FiniteAutomata();
	size_t size();
	bool analy(std::string str);
	std::string FA();
	bool perform();
	bool perform(char *filepath);
	friend std::istream& operator>>(std::istream& input, FiniteAutomata& D);
	friend std::ostream& operator<<(std::ostream& output, FiniteAutomata& D);
	bool operator==(FiniteAutomata& D);
	bool quite;
private:
	bool check(const state& t);
	std::vector<Trnasition> Trans;
	//std::vector<state> initial;
	std::vector<state> F;
	std::vector<state> Q;
	std::vector<label> V;
	std::string theFA;
	size_t num_state;
	//static int g_nStatus;
};



#endif // !FiniteAutomata_H


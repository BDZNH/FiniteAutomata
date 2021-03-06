﻿/******************************************************************
一个用来生成 TCT 工具所用的 ADS 文件的小工具。

这里还提供一个生成 FIRE engine 中的类 DFA 的方法，也即成员函数 getDFA()。

不过在执行这个函数之前，得先确保已经有了一个 FiniteAutomata 对象，无论是通过键盘键入，还是通过另外一个DFA对象进行解析。

因为类 DFA 要求label 为一个 char 变量，而 TCT tools 要求label 为正整数，所以使用这个类的要求是，label为[0,9]，算是一点妥协。


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
#include "DFA.h"             // FIRE engine's header
#include "DFA_components.h"  // FIRE engine's header


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
		return !(*this == D);
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
	DFA getDFA();
	bool perform();
	bool perform(std::string filepath);
	bool perform(DFA &dfa, std::string filepath);
	FiniteAutomata& clear();
	friend std::istream& operator>>(std::istream& input, FiniteAutomata& D);
	friend std::ostream& operator<<(std::ostream& output, FiniteAutomata& D);
	bool operator==(FiniteAutomata& D);
	bool quite;  // 这里是为命令参数设置的一个选项。
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


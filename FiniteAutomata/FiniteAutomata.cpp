#include "FiniteAutomata.h"


FiniteAutomata::FiniteAutomata()
{
	quite = false;
}

FiniteAutomata::FiniteAutomata(std::string str)
{
	analyze(str);
}

FiniteAutomata::FiniteAutomata(DFA & dfa)
{
	std::stringstream ss;
	ss << dfa;
	std::string temp = ss.str();
	analyze(temp);
	ss.str("");
}


FiniteAutomata::~FiniteAutomata()
{
}

FiniteAutomata & FiniteAutomata::reconstruct(std::string str)
{
	this->Trans.clear();
	this->F.clear();
	this->Q.clear();
	this->V.clear();
	this->theFA = "";
	this->num_state = 0;
	analyze(str);
	return (*this);
}

size_t FiniteAutomata::size()
{
	return num_state;
}

// 将 FIRE engine 的输出解析成为当前项目可以识别的格式。
bool FiniteAutomata::analyze(std::string& str)
{
	theFA = str;
	size_t len = str.size();
	size_t i = 0;
	
	// 解析状态数量
	i = str.find("Q =");
	assert(i != -1);
	std::string temp;
	std::stringstream ss;
	while (str.at(i) != ',' && i < len)
	{
		i++;
	}
	i++;
	while (str.at(i) != ')' && i < len)
	{
		temp.push_back(str.at(i));
		i++;
	}
	ss << temp;
	ss >> num_state;
	ss.str("");
	temp = "";


	// 解析结束状态集合
	i = str.find("F = {");
	assert(i != -1);
	i = i + 6;
	state n;
	bool flagf = false;
	while (str.at(i) != '}' && i < len)
	{
		if (str.at(i) == ' '&& flagf)
		{
			std::stringstream ss;
			ss << temp;
			ss >> n;
			F.push_back(n);
			ss.str("");
			temp = "";
			flagf = false;
		}
		else
		{
			flagf = true;
			temp.push_back(str.at(i));
		}
		i++;
	}
	
	// 解析转移状态
	i = str.find("Transitions =");
	assert(i != -1);
	i = i + 14;
	Transition T1;
	//std::string lable;
	bool flag = false;// 标记是否是目标状态，用来区分是 label 还是 deststate

	bool special = false;
	std::vector<label> la;
	bool secondsymbol = false;
	//state dest;
	while (i<len)
	{
		if (str.at(i) == '[')
		{
			special = true;
		}
		if (special)  // 针对类似 2->{ ['0','1']->2 }  的 label 在一起的情况
		{
			if (str.at(i) == ']')
			{
				flag = true;
			}
			else if (str.at(i) == '\'' && secondsymbol && !flag) //第二次遇到字符中括号内的 ' 
			{
				label n = atoi(temp.c_str());
				la.push_back(n);
				temp = "";
				secondsymbol = false;
			}
			else if (str.at(i) == '\'' && !secondsymbol && !flag) // 第一次遇到字符中括号内的 '
			{
				secondsymbol = true;
			}
			else if (str.at(i) == ' ' && (str.at(i-1) >= '0' && str.at(i-1) <= '9') && secondsymbol && flag) //提取目标状态
			{
				T1.stdest = atoi(temp.c_str());
				temp = "";
				secondsymbol = false;
			}
			else if (str.at(i) == '-' && str.at(i+1) == '>' && !secondsymbol && flag) // 第一次遇到字符 '
			{
				secondsymbol = true;
			}
			else if (str.at(i) == '}')  // 结束当前状态的转移关系。
			{
				special = false;
				flag = false;
				secondsymbol = false;
				for (auto iter = la.begin(); iter != la.end(); iter++)
				{
					T1.T = *iter;
					Trans.push_back(T1);
				}
				temp = "";
				la.clear();
			}
			else if (str.at(i) >= '0' && str.at(i) <= '9')
			{
				temp.push_back(str.at(i));
			}
		}
		else  //  针对类似 1->{ '0'->1  '1'->2 }  的 label 不在一起的情况
		{
			if (str.at(i) == '-' && str.at(i + 1) == '>' && !flag)
			{
				T1.stprime = atoi(temp.c_str());
				temp = "";
				
			}
			else if (str.at(i) == '\'' && str.at(i + 1) == '-')
			{
				T1.T = atoi(temp.c_str());
				ss.str("");
				temp = "";
				flag = true;
			}
			else if (str.at(i) == '\'' && str.at(i - 1) == ' ')
			{
				temp = "";
				i++;
				continue;
			}
			else if (str.at(i) == ' ' && str.at(i - 1) >= '0' && str.at(i - 1) <= '9')
			{
				T1.stdest = atoi(temp.c_str());
				ss.str("");
				temp = "";
				Trans.push_back(T1);
			}
			else if (str.at(i) == '}')
			{
				flag = false;
				temp = "";
			}
			else if (str.at(i) >= '0' && str.at(i) <= '9')
			{
				temp.push_back(str.at(i));
			}
		}
		i++;
	}

	std::sort(F.begin(), F.end());

	std::sort(Trans.begin(), Trans.end());

	return false;
}

std::string FiniteAutomata::FA()
{
	return theFA;
}

bool FiniteAutomata::perform()
{
	// 输出数据到默认的文件“FA.ADS”
	assert(num_state > 0);
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



bool FiniteAutomata::perform(std::string filepath)
{
	assert(num_state > 0);
	std::ofstream ofile;
	ofile.open(filepath.c_str());
	if (!ofile.is_open())
	{
		std::cout << "Can't open file: " << filepath << std::endl;
		return false;
	}
	ofile << (*this);
	ofile.close();
	return true;
}

bool FiniteAutomata::perform(DFA & dfa, std::string filepath)
{
	clear();
	std::string temp;
	std::stringstream ss;
	ss << dfa;
	temp = ss.str();
	analyze(temp);
	perform(filepath);
	return true;
}

FiniteAutomata& FiniteAutomata::clear()
{
	this->Trans.clear();
	this->F.clear();
	this->Q.clear();
	this->V.clear();
	this->theFA = "";
	this->num_state = 0;
	return (*this);
}

bool FiniteAutomata::operator==(FiniteAutomata & D)
{
	if (num_state != D.num_state)
		return false;
	if (F.size() != D.F.size())
		return false;
	for (auto iter = F.begin(), iter2 = D.F.begin() ; iter != F.end() && iter2 != D.F.end(); iter++,iter2++)
	{
		if (*iter != *iter2)
			return false;
	}

	if (Trans.size() != D.Trans.size())
		return false;
	for (auto iter = Trans.begin(), iter2 = D.Trans.begin(); iter != Trans.end() && iter2 != D.Trans.end(); iter++, iter2++)
	{
		if (*iter != *iter2)
			return false;
	}
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
	
	Transition trans;
	
	// 输入转移关系
	while (input >> trans.stprime)
	{
		if (trans.stprime == -1)
			break;
		input >> trans.T >> trans.stdest;
		if (D.check(trans.stprime) && D.check(trans.T) && D.check(trans.stdest)) //如果输入的转移关系有效
		{
			// 将状态存入状态集
			D.Trans.push_back(trans);
			result = std::find(D.Q.begin(), D.Q.end(), trans.stprime);
			if (result == D.Q.end())
			{
				D.Q.push_back(trans.stprime);
			}
			result = std::find(D.Q.begin(), D.Q.end(), trans.stdest);
			if (result == D.Q.end())
			{
				D.Q.push_back(trans.stdest);
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
			std::cout << "Invalid argument: " << trans.stprime << " " << trans.T << " " << trans.stdest << std::endl;
		}
		trans.stprime = 0;
		trans.T = 0;
		trans.stdest = 0;
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
	
	for (auto it = D.F.begin(); it != D.F.end(); ++it)
	{
		output << *it << std::endl;
	}
	output << "\nVocal states:\n# <-- Enter vocal output states, one per line.\n# Format: State  Vocal_Output.Vocal_Output in range 10 to 99.\n# Example : 0 10\n# If no vocal states, leave line blank.\n# End vocal list with blank line.\n" << std::endl;
	output << "Transitions:\n# <-- Enter transition triple, one per line.\n# Format: Exit_(Source)_State  Transition_Label  Entrance_(Target)_State.\n# Transition_Label in range 0 to 999.\n# Example: 2 0 1 (for transition labeled 0 from state 2 to state 1)." << std::endl;
	////auto itt = Trans.begin();
	//for (size_t i = 0; i < D.Trans.size(); ++i)
	//{
	//	output << D.Trans[i].Q0 << " " << D.Trans[i].T << " " << D.Trans[i].stdest << std::endl;
	//}

	for (auto iter = D.Trans.begin(); iter != D.Trans.end(); iter++)
	{
		output << iter->stprime << " " << iter->T << " " << iter->stdest << std::endl;
	}
	
	return output;
}

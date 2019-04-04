#include <iostream>
#include <fstream>
#include "FiniteAutomata.h"

int main(size_t argc,char *argv[])
{
	FiniteAutomata fa1;
	if (argc > 1)
	{
		if (strcmp(argv[1], "-f")==0 && argc==3)
		{
			std::ifstream infile;
			infile.open(argv[2]);
			infile >> fa1;

		}
		else
		{
			std::cout << "Usage: command -f <filepath> (FiniteAutomata.exe -f data.txt)" << std::endl;
			return 0;
		}
	}
	else
	{
		std::cin >> fa1;
	}
	fa1.perform();
	//std::cout << fa1.size() << std::endl;
	return 0;
}
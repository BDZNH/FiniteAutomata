#include <iostream>
#include <fstream>
#include "FiniteAutomata.h"

void usage();

int main(size_t argc,char *argv[])
{
	FiniteAutomata fa1;
	if (argc > 1)
	{
		if (argc>=3 && strcmp(argv[1], "-i")==0)
		{
			std::ifstream infile;
			if (strcmp(argv[2], "") == 0)
			{
				usage();
				return 1;
			}
			infile.open(argv[2]);
			if (!infile.is_open())
			{
				std::cout << "No such a file: " << argv[2] << std::endl;
				usage();
				return 1;
			}
			fa1.quite = true;
			infile >> fa1;
			if (argc == 5 && strcmp(argv[3], "-o") == 0 )
			{
				if (strcmp(argv[4], "") == 0)
				{
					usage();
					return 1;
				}
				std::ofstream outfile;
				outfile.open(argv[4]);
				if (!outfile.is_open())
				{
					std::cout << "No such a file: " << argv[4] << std::endl;
					usage();
					return 1;
				}
				outfile << fa1;
				outfile.close();
				std::cout << "Success!" << std::endl;
				return 0;
			}
		}
		else
		{
			usage();
			return 0;
		}
	}
	else
	{
		std::cin >> fa1;
	}
	if (!fa1.perform())
	{
		return 1;
	}
	std::cout << fa1 << std::endl;
	return 0;
}


void usage()
{
	std::cout << "\n____ A tiny tool that generate ADS file for TCT tool____ " << std::endl;
	std::cout << "Usage: command option argument " << std::endl;
	std::cout << "    option: -i , the input file " << std::endl;
	std::cout << "            -o , the output file " << std::endl;
	std::cout << "Example: FiniteAutomata.exe -i data.txt -o FA.ADS \n" << std::endl;
}
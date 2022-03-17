#include "advent_code.hpp"

int main ()
{
	// Test load input 1
	{
		AC::Timer timer;
		
		std::ifstream inputFile(AC::getInputFile("2021", "1"));
		for (int i = 0; i < 10; ++i){
			std::string s;
			inputFile >> s;
			std::cout << i << ": " << s << std::endl;
		}
		std::cout << "----------";
	}
	// test load input 2 and split it
	{
		AC::Timer timer;
		std::ifstream inputFile(AC::getInputFile("2021","2"));
		std::stringstream ss;
		ss << inputFile.rdbuf();
		std::string s = ss.str();
		AC::VecStrView tokens = AC::split(s);
		std::cout << "SIZE: " << tokens.size() << std::endl;
		int i = 0;
		for (const auto token : tokens){
			std::cout << token << std::endl;
			if(++i > 10)
				break;
		}
		std::cout << "----------";
	}
	return 0;
}

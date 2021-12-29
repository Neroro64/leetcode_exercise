#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <stdint.h>
#include <chrono>

using VecStrView = std::vector<std::string_view>;

struct Timer{
	public:
		Timer(){
			clock = std::chrono::steady_clock::now();
		}
		~Timer(){
			std::chrono::duration<float> duration = std::chrono::steady_clock::now() - clock;
			std::cout << "Elapsed time: " << duration.count() << std::endl;
		}
	private:
		std::chrono::time_point<std::chrono::steady_clock> clock;
};

inline static VecStrView split(std::string_view& inputStr, char delimiter=' '){
	VecStrView vecStrView;
	vecStrView.reserve(10);
	size_t strSize = inputStr.size();

	uint32_t offset = 0, pos=0;
	while((pos = inputStr.find(delimiter, offset)) && pos < strSize){
		vecStrView.emplace_back(inputStr.substr(offset, pos - offset));
		offset = pos + 1;
	}

	vecStrView.emplace_back(inputStr.substr(offset, strSize - offset));
	return vecStrView;
}

inline static std::vector<std::string> split_slow(std::string& inputStr, char delimiter=' '){
	std::vector<std::string> vecStrView;
	vecStrView.reserve(10);
	size_t strSize = inputStr.size();

	uint32_t offset = 0, pos=0;
	while((pos = inputStr.find(delimiter, offset)) && pos < strSize){
		vecStrView.emplace_back(inputStr.substr(offset, pos - offset));
		offset = pos + 1;
	}

	vecStrView.emplace_back(inputStr.substr(offset, strSize - offset));
	return vecStrView;
}



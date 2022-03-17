#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <stdint.h>
#include <chrono>
#include <optional>
#include <algorithm>

namespace AC {
#if __linux__
static const std::string ROOT_PATH = "/home/nuoc/dev/leetcode_exercise/advent_of_code/inputs/";
#elif _WIN32
static const std::string ROOT_PATH = "e:/dev/leetcode_exercise/advent_of_code/inputs/";
#endif
typedef std::vector<std::string_view> VecStrView;

struct Timer{
	public:
		Timer(){
			clock = std::chrono::steady_clock::now();
		}
		Timer(std::optional<float>& resultPtr)
			:m_resultPtr(resultPtr)
		{
			Timer();
		}
		~Timer(){
			std::chrono::duration<float> duration = std::chrono::steady_clock::now() - clock;
			float elapsedTime = m_resultPtr.emplace(duration.count());
			std::cout << "Elapsed time: " << elapsedTime << std::endl;
		}
	private:
		std::chrono::time_point<std::chrono::steady_clock> clock;
		std::optional<float> m_resultPtr;
};

static VecStrView split(std::string_view inputStr, char delimiter=' '){
	size_t charCount = std::count(inputStr.cbegin(), inputStr.cend(), delimiter);
	VecStrView vecStrView;
	vecStrView.reserve(charCount+1);
	size_t strSize = inputStr.size();

	uint32_t offset = 0, pos=0;
	while((pos = inputStr.find(delimiter, offset)) && pos < strSize){
		vecStrView.emplace_back(inputStr.substr(offset, pos - offset));
		offset = pos + 1;
	}

	vecStrView.emplace_back(inputStr.substr(offset, strSize - offset));
	return vecStrView;
}
inline static std::string getInputFile(std::string&& year, std::string&& day){
	std::stringstream filepath;
	filepath << ROOT_PATH << year << "/" << day << ".txt";
	return filepath.str();
}
} // namespace AC

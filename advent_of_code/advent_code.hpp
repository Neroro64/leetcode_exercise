#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <stdint.h>
#include <chrono>
#include <optional>

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
			m_resultPtr = duration.count();
			std::cout << "Elapsed time: " << m_resultPtr.value_or(-1) << std::endl;
		}
	private:
		std::chrono::time_point<std::chrono::steady_clock> clock;
		std::optional<float> m_resultPtr;
};

using VecStrView = std::vector<std::string_view>;
inline static VecStrView split(std::string_view& inputStr, char delimiter=' '){
	VecStrView vecStrView;
	vecStrView.reserve(100);
	size_t strSize = inputStr.size();

	uint32_t offset = 0, pos=0;
	while((pos = inputStr.find(delimiter, offset)) && pos < strSize){
		vecStrView.emplace_back(inputStr.substr(offset, pos - offset));
		offset = pos + 1;
	}

	vecStrView.emplace_back(inputStr.substr(offset, strSize - offset));
	return vecStrView;
}



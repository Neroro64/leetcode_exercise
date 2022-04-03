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
#include <unordered_map>
#include <charconv>
#include <cmath>
#include <stdio.h>
#include <queue>
#include <unordered_set>

template <typename DataType, typename ResultType> struct InputData {
  DataType data;
  ResultType result;
};

template <typename DataType, typename ResultType>
void solution(InputData<DataType, ResultType> &);

template <typename DataType, typename ResultType>
bool test(void (*func)(InputData<DataType, ResultType> &),
          InputData<DataType, ResultType> &data, ResultType answer) {
  func(data);
  if (answer != data.result) {
    std::cout << "TEST FAILED" << std::endl;
    std::cout << "Expected: " << answer << std::endl;
    std::cout << "Received: " << data.result << std::endl;
    return false;
  }
  std::cout << "TEST PASSED" << std::endl;
  return true;
}

typedef std::vector<std::string_view> VecStrView;
typedef std::vector<std::string> VecStr;
typedef std::vector<int> VecInt;
typedef std::vector<unsigned int> VecUInt;
typedef unsigned int uint;

namespace AC {
#if __linux__
static const std::string ROOT_PATH =
    "/home/nuoc/dev/leetcode_exercise/advent_of_code/inputs/";
#elif _WIN32
static const std::string ROOT_PATH =
    "e:/dev/leetcode_exercise/advent_of_code/inputs/";
#endif

struct Timer {
public:
  Timer() { clock = std::chrono::steady_clock::now(); }
  Timer(std::optional<float> &resultPtr) : m_resultPtr(resultPtr) { Timer(); }
  ~Timer() {
    std::chrono::duration<float> duration =
        std::chrono::steady_clock::now() - clock;
    float elapsedTime = m_resultPtr.emplace(duration.count());
    std::cout << "Elapsed time: " << elapsedTime << std::endl;
  }

private:
  std::chrono::time_point<std::chrono::steady_clock> clock;
  std::optional<float> m_resultPtr;
};

static VecStrView split(std::string_view inputStr, char delimiter = ' ') {
  size_t charCount = std::count(inputStr.cbegin(), inputStr.cend(), delimiter);
  VecStrView vecStrView;
  vecStrView.reserve(charCount + 1);
  size_t strSize = inputStr.size();

  uint32_t offset = 0, pos = 0;
  while ((pos = inputStr.find(delimiter, offset)) && pos < strSize) {
    vecStrView.emplace_back(inputStr.substr(offset, pos - offset));
    offset = pos + 1;
  }

  vecStrView.emplace_back(inputStr.substr(offset, strSize - offset));
  return vecStrView;
}
inline static std::string getInputFile(std::string &&year, std::string &&day) {
  std::stringstream filepath;
  filepath << ROOT_PATH << year << "/" << day << ".txt";
  return filepath.str();
}

inline static std::string getInputDataAsStr(std::string &&year,
                                            std::string &&day) {
  std::stringstream filepath;
  filepath << ROOT_PATH << year << "/" << day << ".txt";
  std::ifstream inputFile = std::ifstream{filepath.str()};
  std::string inputString((std::istreambuf_iterator<char>(inputFile)),
                          std::istreambuf_iterator<char>());
  return inputString;
}
} // namespace AC

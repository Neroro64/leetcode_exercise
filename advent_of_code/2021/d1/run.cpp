#include "../../advent_code.hpp"

struct InputData {
  std::vector<int> data;
};

bool test();
int solution(InputData &);

bool test() {
  InputData data{{199, 200, 208, 210, 200, 207, 240, 269, 260, 263}};
  const int answer = 7;
  int output = solution(data);
  if (answer != output) {
    std::cout << "TEST FAILED" << std::endl;
    std::cout << "Expected: " << answer << std::endl;
    std::cout << "Received: " << output << std::endl;
    return false;
  }
  std::cout << "TEST PASSED" << std::endl;
  return true;
}

int solution(InputData &inputData) {
  size_t N{inputData.data.size()};

  if (N < 1)
    return 0;

  int n = 0;
  for (std::uint32_t i = 1; i < N; ++i) {
    if (inputData.data[i] > inputData.data[i - 1])
      ++n;
  }
  return n;
}

int main() {
  if (test()) {

    std::ifstream inputFile = std::ifstream{AC::getInputFile("2021", "1")};
    InputData inputData;
    std::string s;

    while (inputFile >> s) {
      inputData.data.emplace_back(stoi(s));
    }
    int result = solution(inputData);

    std::cout << result << std::endl;
  }
}

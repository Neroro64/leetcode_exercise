#include "../../advent_code.hpp"

typedef InputData<VecInt, int> IData;
void solution(IData &inputData) {
  size_t N{inputData.data.size()};
  if (N < 1)
    return;

  int n = 0;
  for (std::uint32_t i = 1; i < N; ++i) {
    if (inputData.data[i] > inputData.data[i - 1])
      ++n;
  }
  inputData.result = n;
}

int main() {
  IData data = {{199, 200, 208, 210, 200, 207, 240, 269, 260, 263}, 0};
  if (test(data, 7)) {
    std::ifstream inputFile = std::ifstream{AC::getInputFile("2021", "1")};
    IData inputData;
    std::string s;

    while (inputFile >> s) {
      inputData.data.emplace_back(stoi(s));
    }
    solution(inputData);

    std::cout << inputData.result << std::endl;
  }
}

#include "../../advent_code.hpp"
#include <cmath>
#include <string>

typedef InputData<VecStrView, int> IData;

void solution(IData &inputData) {
  size_t digitCount = inputData.data[0].length();
  size_t readingCountHalf = inputData.data.size() / 2;
  VecUInt reading(digitCount, 0);
  for (const std::string_view ite : inputData.data) {
    for (unsigned int i = 0; i < digitCount; ++i) {
      reading[i] += (ite[i] - 48) % 2;
    }
  }

  unsigned int gamma = 0, epsilon = 0;
  unsigned int power = std::pow(2, digitCount - 1);
  for (unsigned int &r : reading) {
    r = (r > readingCountHalf) ? 1 : 0;
    gamma += r * power;
    epsilon += !r * power;
    power >>= 1u;
  }
  inputData.result = gamma * epsilon;
  printf("Gamma: %u, Epsilon: %u, Result: %u\n", gamma, epsilon,
         inputData.result);
}

int main() {
  IData testData = {{"00100", "11110", "10110", "10111", "10101", "01111",
                     "00111", "11100", "10000", "11001", "00010", "01010"},
                    0};

  std::string inputString = AC::getInputDataAsStr("2021", "3");
  if (test(&solution, testData, 198)) {
    IData inputData{AC::split(inputString, '\n'), 0};
    solution(inputData);
    std::cout << "#1 Result: " << inputData.result << std::endl;
  }
  return 0;
}

#include "../../advent_code.hpp"

typedef InputData<VecStrView, int> IData;

void solution(IData &inputData) {
  AC::Timer timer;
  size_t digitCount = inputData.data[0].length();
  size_t readingCountHalf = inputData.data.size() / 2;
  VecUInt reading(digitCount, 0);
  for (const std::string_view ite : inputData.data) {
    for (uint i = 0; i < digitCount; ++i) {
      reading[i] += (ite[i] - 48) % 2;
    }
  }

  uint gamma = 0, epsilon = 0;
  uint power = std::pow(2, digitCount - 1);
  for (uint &r : reading) {
    r = (r > readingCountHalf) ? 1 : 0;
    gamma += r * power;
    epsilon += !r * power;
    power >>= 1u;
  }
  inputData.result = gamma * epsilon;
  printf("Gamma: %u, Epsilon: %u, Result: %u\n", gamma, epsilon,
         inputData.result);
}
void solution2(IData &inputData) {
  AC::Timer timer;
  size_t digitCount = inputData.data[0].length();
  size_t readingCount = inputData.data.size();
  size_t readingCountHalf = readingCount / 2;

  VecUInt reading(digitCount, 0);
  uint setSize = 0, digit_ptr = 0;
  std::vector<std::unordered_set<uint>> indexSet{
      std::unordered_set<uint>{},
      std::unordered_set<uint>{}}; // [0/1]{ index }

  for (uint i = 0; i < readingCount; ++i) {
    uint d = (inputData.data[i][0] - 48) % 2;
    reading[i] += d;
    indexSet[d].insert(i);
  }

  uint selector  = (reading[digit_ptr] >= readingCountHalf) ? 1 : 0;
  setSize = indexSet[selector].size();
  ++digit_ptr;
  indexSet[!selector].clear();

  do {
	  for (uint i = 0; i < setSize; ++i){
		
	  }
  } while (setSize > 1);
  uint oxygen = 0, co2 = 0;
  uint power = std::pow(2, digitCount - 1);
  for (uint &r : reading) {
    r = (r >= readingCountHalf) ? 1 : 0;
    gamma += r * power;
    epsilon += !r * power;
    power >>= 1u;
  }
  inputData.result = gamma * epsilon;
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

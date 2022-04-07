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
  auto get_selector = [](uint digit, bool reverse = false, size_t setSize = 0) {
    if (reverse)
      return (digit < setSize) ? 1 : 0;
    else
      return (digit >= setSize) ? 1 : 0;
  };

  uint digit_ptr = 0, setSize0 = 0, setSize1 = 0;
  std::vector<std::unordered_set<uint>> indexSet{
      std::unordered_set<uint>{}, std::unordered_set<uint>{}}; // [0/1]{ index }

  // split the dataset into two sets depending on the first digit
  for (uint i = 0; i < readingCount; ++i) {
    uint d = (inputData.data[i][digit_ptr] - 48) % 2;
    reading[digit_ptr] += d;
    indexSet[d].insert(i);
  }

  // decide the most common digit and increment the ptr to point to the second
  // digit
  uint selector = get_selector(reading[digit_ptr++], false, readingCountHalf);
  setSize0 = indexSet[selector].size();
  setSize1 = indexSet[!selector].size();
  auto process_set = [&](std::unordered_set<uint> &set, bool reverse) {
    reading[digit_ptr] = 0;
    for (uint id : set) {
      uint d = (inputData.data[id][digit_ptr] - 48) % 2;
      reading[digit_ptr] += d;
    }
    uint sel = get_selector(reading[digit_ptr], reverse,
                            (set.size() / 2) + (set.size() % 2));
    for (auto ite = set.cbegin(); ite != set.cend();) {
      uint d = (inputData.data[*ite][digit_ptr] - 48) % 2;
      if (d != sel) {
        ite = set.erase(ite);
      } else
        ++ite;
    }
  };
  do {
    // the most common bit policy
    if (setSize0 > 1)
      process_set(indexSet[selector], false);
    // the least common bit policy
    if (setSize1 > 1)
      process_set(indexSet[!selector], true);

    setSize0 = indexSet[selector].size();
    setSize1 = indexSet[!selector].size();
    ++digit_ptr;
  } while (setSize0 + setSize1 != 2 && digit_ptr < digitCount);

  auto strToInt = [&digitCount](std::string_view &str) {
    uint power = std::pow(2, digitCount - 1);
    uint r = 0;
    for (char c : str) {
      r += ((c - 48) % 2) * power;
      power >>= 1;
    }
    return r;
  };
  uint oxygen = strToInt(inputData.data[*(indexSet[selector].begin())]);
  uint co2 = strToInt(inputData.data[*(indexSet[!selector].begin())]);

  inputData.result = oxygen * co2;
  printf("Oxygen: %u, CO2: %u, Result: %u\n", oxygen, co2, inputData.result);
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
  if (test(&solution2, testData, 230)) {
    IData inputData{AC::split(inputString, '\n'), 0};
    solution2(inputData);
    std::cout << "#2 Result: " << inputData.result << std::endl;
  }
  return 0;
}

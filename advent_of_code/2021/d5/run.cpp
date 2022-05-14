#include "../../advent_code.hpp"

typedef InputData<std::string, uint> IData;

VecStrView parseInput(std::string filePath){
  std::ifstream inputFile = std::ifstream{filePath};
  std::string str;
  while(std::getline(inputFile, str)){
    VecStrView tokens = AC::split(str, ' ');
    VecStrView x1y1 = AC::split(tokens[0], ',');
    VecStrView x2y2 = AC::split(tokens[tokens.size()-1], ',');

  }

}
void solution(IData &inputData) {
  VecStrView inputs = AC::split(inputData.data, '\n');
}
void solution2(IData &inputData);

int main() {
  std::string rawTestInput = R"(
0,9 -> 5,9
8,0 -> 0,8
9,4 -> 3,4
2,2 -> 2,1
7,0 -> 7,4
6,4 -> 2,0
0,9 -> 2,9
3,4 -> 1,4
0,0 -> 8,8
5,5 -> 8,2
  )";
  IData testData = {rawTestInput, 0};

  std::string inputString = AC::getInputDataAsStr("2021", "4");
  if (test(&solution, testData, 5u)) {
    IData inputData = {inputString, 0u};
    solution(inputData);
    std::cout << "#1 Result: " << inputData.result << std::endl;
  }
  // if (test(&solution2, testData, 1924u)) {
  //   IData inputData = {inputString, 0u};
  //   solution2(inputData);
  //   std::cout << "#2 Result: " << inputData.result << std::endl;
  // }
  return 0;
}

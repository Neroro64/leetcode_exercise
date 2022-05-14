#include "../../advent_code.hpp"

typedef InputData<std::string, uint> IData;
typedef std::set<uint> uint_set;

struct Board {
  uint grid[5][5];
  uint minDrawRowCol[10];
};

void solution(IData &inputData) {
  std::unordered_map<uint, uint> inputNumbers; // (number, index)
  std::vector<Board> boards = {
      Board{}}; // Initialize the vector with one default board

  std::istringstream stream(inputData.data);
  std::string str;

  // find the first non-empty row, that is our numbers to be drawed.
  do {
    std::getline(stream, str);
    if (!str.empty()) {
      VecStrView numbers = AC::split(str, ',');
      for (uint i = 0; i < numbers.size(); ++i) {
        inputNumbers.insert({atoi(numbers[i].data()), i});
      }
    }
  } while (str.empty());
  std::getline(stream, str); // the very next line is an empty line
  size_t inputSize = inputNumbers.size();

  // Foreach row of the grid input,
  // 	for each number, find the index of that number in the input sequence.
  uint boardID = 0, minBoardID = 0, rowColID = 0, minDraw = inputSize;
  auto minElementID = [&inputSize](uint *ptr, uint *out) {
    uint minVal = inputSize;
    uint minID = 0;
    for (int i = 0; i < 5; ++i) {
      if (*(ptr + i) < minVal) {
        minVal = *(ptr + i);
        minID = i;
      }
    }
    *out = minVal;
    return minID;
  };
  auto updateMinVal = [&minDraw, &rowColID, &minBoardID, &boardID, &boards,
                       &minElementID]() {
    uint minVal = 0, colMinVal = 0;
    uint minValID = minElementID(&boards[boardID].minDrawRowCol[0], &minVal);
    uint colMinValID =
        minElementID(&boards[boardID].minDrawRowCol[5], &colMinVal) + 5;

    // find the row/col with minimum draw
    if (minVal > colMinVal) {
      minVal = colMinVal;
      minValID = colMinValID;
    }

    // replace the global min if this board has shorter path to success
    if (minVal < minDraw) {
      minDraw = minVal;
      minBoardID = boardID;
      rowColID = minValID;
    }
  };

  uint r = 0, c = 0;
  std::_List_iterator ite = inputNumbers.begin();
  do {
    if (std::getline(stream, str)) {
      if (str.empty()) {
        updateMinVal();

        r = 0;
        c = 0;
        boards.push_back(Board{});
        ++boardID;
      } else {
        VecStrView line = AC::split(str);
        c = 0;
        for (auto token : line) {
          if (token.empty())
            continue;

          uint num = atoi(token.data());

          if ((ite = inputNumbers.find(num)) != inputNumbers.end()) {
            boards[boardID].minDrawRowCol[c] =
                std::max(ite->second, boards[boardID].minDrawRowCol[c]);
            boards[boardID].minDrawRowCol[5 + r] =
                std::max(ite->second, boards[boardID].minDrawRowCol[5 + r]);
          }
          else{
            boards[boardID].minDrawRowCol[c] = inputSize;
            boards[boardID].minDrawRowCol[5+r] = inputSize;
          }


          boards[boardID].grid[r][c] = num;
          ++c;
        }
        ++r;
      }
    } else {
      updateMinVal();
      break;
    }
  } while (true);

  std::cout << "Finished Iterating the boards" << std::endl;
  std::cout << "Found board ID: " << minBoardID << std::endl;
  std::cout << "Found minimum draws: " << minDraw << std::endl;

  uint sumOfUnmarked = 0;
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      uint n = boards[minBoardID].grid[i][j];
      if ((ite = inputNumbers.find(n)) != inputNumbers.end() &&
          ite->second > minDraw) {
        sumOfUnmarked += n;
      }
    }
  }
  uint lastDrawnNumber =
      std::find_if(
          inputNumbers.begin(), inputNumbers.end(),
          [&minDraw](const std::unordered_map<uint, uint>::value_type &entry) {
            return entry.second == minDraw;
          })
          ->first;
  inputData.result = sumOfUnmarked * lastDrawnNumber;

  std::cout << "Found sum of the unmarked values: " << sumOfUnmarked
            << std::endl;
  std::cout << "Found the last draw: " << lastDrawnNumber << std::endl;
  return;
}
void solution2(IData &inputData) {}

int main() {
  std::string rawTestInput = R"(
7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1

22 13 17 11  0
 8  2 23  4 24
21  9 14 16  7
 6 10  3 18  5
 1 12 20 15 19

 3 15  0  2 22
 9 18 13 17  5
19  8  7 25 23
20 11 10 24  4
14 21 16 12  6

14 21 17 24  4
10 16 15  9 19
18  8 23 26 20
22 11 13  6  5
 2  0 12  3  7)";
  IData testData = {rawTestInput, 0};

  std::string inputString = AC::getInputDataAsStr("2021", "4");
  if (test(&solution, testData, 4512u)) {
    IData inputData = {inputString, 0u};
    solution(inputData);
    std::cout << "#1 Result: " << inputData.result << std::endl;
  }
  // if (test(&solution2, testData, 230)) {
  //   IData inputData{AC::split(inputString, '\n'), 0};
  //   solution2(inputData);
  //   std::cout << "#2 Result: " << inputData.result << std::endl;
  // }
  return 0;
}

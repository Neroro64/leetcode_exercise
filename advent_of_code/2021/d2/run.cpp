#include "../../advent_code.hpp"

typedef InputData<VecStrView, int> IData;
static const std::unordered_map<std::string_view, VecInt> opts{
    {"forward", {1, 0}}, {"up", {0, -1}}, {"down", {0, 1}}};
// [ ] operator for map is not const. It can add the key if not found.
const VecInt *const_fd(std::string_view key) {
  auto ite = opts.find(key);
  if (ite != opts.end()) {
    return &ite->second;
  }
  return nullptr;
}

void solution(IData &inputData) {
  VecInt record = {0, 0};
  for (const auto str : inputData.data) {
    if (str == "")
      continue;
    VecStrView tokens = AC::split(str); // ( direction,  steps )

    int step;
    auto dir = const_fd(tokens[0]);
    // Convert from string_view to int
    std::from_chars(tokens[1].data(), tokens[1].data() + tokens[1].size(),
                    step);

    record[0] += (*dir)[0] * step;
    record[1] += (*dir)[1] * step;
  }
  std::cout << record[0] << " : " << record[1] << std::endl;
  inputData.result = record[0] * record[1];
}

void solution2(IData &inputData) {
  VecInt record = {0, 0, 0}; // horizontal, aim, vertical
  for (const auto str : inputData.data) {
    if (str == "")
      continue;
    VecStrView tokens = AC::split(str); // ( direction,  steps )

    int step;
    auto dir = const_fd(tokens[0]);
    // Convert from string_view to int
    std::from_chars(tokens[1].data(), tokens[1].data() + tokens[1].size(),
                    step);

    record[0] += (*dir)[0] * step;
    record[1] += (*dir)[1] * step;
    if (tokens[0] == "forward")
      record[2] += record[1] * step;
  }
  std::cout << record[0] << " : " << record[1] << " : " << record[2]
            << std::endl;
  inputData.result = record[0] * record[2];
}
int main() {
  IData data = {
      {"forward 5", "down 5", "forward 8", "up 3", "down 8", "forward 2"}, 0};
  std::ifstream inputFile = std::ifstream{AC::getInputFile("2021", "2")};
  std::string inputString((std::istreambuf_iterator<char>(inputFile)),
                          std::istreambuf_iterator<char>());
  if (test(&solution, data, 150)) {
    IData inputData{AC::split(inputString, '\n'), 0};
    solution(inputData);

    std::cout << "#1 Result: " << inputData.result << std::endl;
  }
  if (test(&solution2, data, 900)) {
    IData inputData{AC::split(inputString, '\n'), 0};
    solution2(inputData);

    std::cout << "#2 Result: " << inputData.result << std::endl;
  }
  return 0;
}

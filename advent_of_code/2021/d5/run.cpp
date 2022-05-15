#include "../../advent_code.hpp"

struct Point {
  int x, y;
  Point operator+(const Point &rhs) { return Point{x + rhs.x, y + rhs.y}; }
  Point operator-(const Point &rhs) { return Point{x - rhs.x, y - rhs.y}; }
  float operator*(const Point &rhs) { return x * rhs.x + y * rhs.y; }
  float cross(const Point &rhs) { return x * rhs.y - y * rhs.x; }
};
struct Segment {
  Point p0, p1, k;
  Segment(Point p0, Point p1) {
    this->p0 = p0;
    this->p1 = p1;
    k = Point{p1.x - p0.x, p1.y - p0.y};
  }
  bool getIntersection(Segment &rhs, Point *out = nullptr) {
    Point dS1{p1.x - p0.x, p1.y - p0.y};
    Point dS2{rhs.p1.x - rhs.p0.x, rhs.p1.y - rhs.p0.y};
    float s, t, k = (-dS2.x * dS1.y + dS1.x * dS2.y);
    s = (-dS1.y) * (p0.x - rhs.p0.x) + dS1.x * (p0.y - rhs.p0.y) / k;
    t = (dS2.y) * (p0.y - rhs.p0.y) - dS2.y * (p0.x - rhs.p0.x) / k;
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
      if (out != nullptr) {
        out->x = p0.x + (t * dS1.x);
        out->y = p0.y + (t * dS1.y);
      }
      return true;
    }
    return false;
  }
};

typedef InputData<std::vector<Segment>, uint> IData;
std::vector<Segment> parseInput(std::string inputString,
                                bool onlyStraight = false) {
  std::istringstream inputStream {inputString};
  std::string str;
  std::vector<Segment> segments;
  while (std::getline(inputStream, str)) {
    VecStrView tokens = AC::split(str, ' ');
    VecStrView x1y1 = AC::split(tokens[0], ',');
    VecStrView x2y2 = AC::split(tokens[tokens.size() - 1], ',');
    if (onlyStraight) {
      if (x1y1[0] == x2y2[0] || x1y1[1] == x2y2[1]) {
        segments.emplace_back(
            Point{std::atoi(x1y1[0].data()), std::atoi(x1y1[1].data())},
            Point{std::atoi(x2y2[0].data()), std::atoi(x2y2[1].data())});
      }
    }
    else{
      segments.emplace_back(
          Point{std::atoi(x1y1[0].data()), std::atoi(x1y1[1].data())},
          Point{std::atoi(x2y2[0].data()), std::atoi(x2y2[1].data())});
    }
  }
  return segments;
}
void solution(IData &inputData) {
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
  auto t1 = parseInput(rawTestInput, false);
  auto t2 = parseInput(rawTestInput, true);
  IData testData = {t1, 0u};

  std::string inputFile = AC::getInputDataAsStr("2021", "5");
  if (test(&solution, testData, 5u)) {
    IData inputData = {parseInput(inputFile), 0u};
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

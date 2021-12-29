#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <string_view>
#include <ranges>
using namespace std;

int main() {
  ifstream inputFile("input.txt");
  vector<string> inputs;
  string dir, steps;
  vector<int> start {0,0};
  unordered_map<string, vector<int>> opts {
    {"forward",{1,0}},
    {"up", {0,-1}},
    {"down", {0,1}}
  };

  while (inputFile >> dir){
    if (dir == "")
      continue;
    inputFile >> steps;
    int s = stoi(steps);
    start[0] += opts[dir][0] * s;
    start[1] += opts[dir][1] * s;
  }
  cout << start[0] << " * " << start[1] << " = " << start[0]*start[1] << endl;
  return 0;
}

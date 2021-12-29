#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  ifstream inputFile("input.txt");
  vector<int> nums;
  string s;
  int n{1};

  while (inputFile >> s)
    nums.push_back(stoi(s));
  size_t N{nums.size()};

  if (N < 1)
    return 0;

  for (int i = 1, n=1; i < nums.size(); ++i) {
    if (nums[i] > nums[i - 1])
      ++n;
  }
  cout << n << endl;
  return 0;
}

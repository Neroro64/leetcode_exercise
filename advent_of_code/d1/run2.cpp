#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  ifstream inputFile("Input2.txt");
  string s;
  int counter      = 0,
      numIncreases = 0,
      prevSum      = 0,
      currentSum   = 0,
      measurement  = 0;

  vector<int> sliding_window {0,0,0};
  for (int i = 0; i < 3; ++i){
    inputFile >> s;
    measurement = stoi(s);
    sliding_window[i] = measurement;
    prevSum += measurement;
  }
  currentSum = prevSum;

  while (inputFile >> s){
    measurement = stoi(s);

    currentSum = currentSum - sliding_window[counter] + measurement;
    if (currentSum > prevSum)
      ++numIncreases;

    prevSum = currentSum;
    sliding_window[counter] = measurement;
    
    counter = (counter + 1) % 3;
  }

  cout << numIncreases << endl;
  return 0;
}

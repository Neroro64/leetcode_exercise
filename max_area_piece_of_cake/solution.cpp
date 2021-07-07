#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Solution {
public:
  int maxArea(int h, int w, std::vector<int> &horizontalCuts,
              std::vector<int> &verticalCuts) {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    std::sort(horizontalCuts.begin(), horizontalCuts.end(), std::less<int>());
    std::sort(verticalCuts.begin(), verticalCuts.end(), std::less<int>());


    long h_max_dist = horizontalCuts[0], dist = 0;
    for (auto it = horizontalCuts.begin() + 1; it != horizontalCuts.end();
         ++it) {
      dist = *it - *(it - 1);
      if (dist > h_max_dist)
        h_max_dist = dist;
    }
    dist = h - *(horizontalCuts.end()-1);
    if (dist > h_max_dist)
      h_max_dist = dist;

    long v_max_dist = verticalCuts[0];
    for (auto it = verticalCuts.begin() + 1; it != verticalCuts.end(); ++it) {
      dist = *it - *(it - 1);
      if (dist > v_max_dist)
        v_max_dist = dist;
    }
    dist = w - *(verticalCuts.end()-1);
    if (dist > v_max_dist)
      v_max_dist = dist;
    
    long mod = 1000000007l;
    h_max_dist *= v_max_dist;
    return (h_max_dist < mod)? static_cast<int>(h_max_dist) : static_cast<int>(h_max_dist % mod);
  }
};

#include <algorithm>
#include <cmath>
#include <vector>

class Solution {
public:
  int maxArea(int h, int w, std::vector<int> &horizontalCuts,
              std::vector<int> &verticalCuts) {
    std::sort(horizontalCuts.begin(), horizontalCuts.end(), std::less<int>());
    std::sort(verticalCuts.begin(), verticalCuts.end(), std::less<int>());

    horizontalCuts.insert(horizontalCuts.begin(), 0);
    horizontalCuts.push_back(h);
    verticalCuts.insert(verticalCuts.begin(), 0);
    verticalCuts.push_back(w);

    long long h_max_dist = -1, dist = 0;
    for (auto it = horizontalCuts.begin() + 1; it != horizontalCuts.end();
         ++it) {
      dist = std::abs(*it - *(it - 1));
      if (dist > h_max_dist)
        h_max_dist = dist;
    }
    long long v_max_dist = -1;
    for (auto it = verticalCuts.begin() + 1; it != verticalCuts.end(); ++it) {
      dist = std::abs(*it - *(it - 1));
      if (dist > v_max_dist)
        v_max_dist = dist;
    }
    return static_cast<int>((h_max_dist * v_max_dist) %
                            static_cast<long long>(std::pow(10, 9) + 7));
  }
};

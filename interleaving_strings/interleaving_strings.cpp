#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
  bool isInterleave(string s1, string s2, string s3) {
    size_t l1 = s1.size(), l2 = s2.size(), l3 = s3.size();
    bool dp[l1 + 1][l2 + 1];

    if ((l1 + l2 + l3) == 0)
      return true;
    else if (l3 == 0 || l1 + l2 != l3 || l1 + l2 == 0)
      return false;
    else if (l1 == 0)
      return s2 == s3;
    else if (l2 == 0)
      return s1 == s3;

    for (size_t i = 0; i <= l1; ++i) {
      for (size_t j = 0; j <= l2; ++j)
        dp[i][j] = false;
    }

    dp[0][0] = true;

    for (size_t i = 0; i < l1; ++i) {
      if (s1[i] == s3[i])
        dp[i + 1][0] = dp[i][0];
    }
    for (size_t j = 0; j < l2; ++j) {
      if (s2[j] == s3[j])
        dp[0][j + 1] = dp[0][j];
    }

    if (!dp[0][1] && !dp[1][0])
      return false;

    int z = 0;
    for (size_t i = 1; i <= l1; ++i) {
      for (size_t j = 1; j <= l2; ++j) {
        z = i + j - 1;
        dp[i][j] = (dp[i][j - 1] && s2[j - 1] == s3[z]) ||
                   (dp[i - 1][j] && s1[i - 1] == s3[z]);
      }
    }
    return dp[l1][l2];
  }
};

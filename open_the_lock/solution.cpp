#include <string.h>
#include <vector>
#include<limits>

using namespace std;

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
      char pos[4] = {'0', '0', '0', '0'};
      const char *target = target.c_str();
      int moves[4] = {0};
      bool success = false;
      int steps = 0;
      while (strcmp(pos, target) != 0) {
        success = find_best_move(moves, pos, target);  
        if (!success) {
          steps = -1;
          break;
        } 
        else ++steps;
      }
      return steps;
    }

    inline void find_best_move(char *pos, const char *target){
      int min_cost, cost = INT_MAX, 0;
      vector<int> moves = {0,0,0,0}; 
      vector<int> best_moves = {0,0}; 

      int possible_move = {-1, 1};

      for (int i = 0; i < 4; ++i)
      {
        for (int m : possible_move)
        {
          moves[i] = m;
          char p[4] = {pos[0], pos[1], pos[2], pos[3]};
          p[i] += moves[i];
          if (p[i] < '0') p[i] = '9';
          else if (p[i] > '9') p[i] = '0';

          cost = g(p, target) + h(p,target);
          if (cost <= 0)  continue;
          else if (cost < min_cost)
          {
            min_cost = cost;
            best_moves[0] = i;
            best_moves[1] = p[i];
          }
        }
      }

      if (min_cost == INT_MAX) return false;
      else  pos[best_moves[0]] = (char) best_moves[1];
      return true;
    }

    inline void g(char *pos, const char *target){

    }  
};

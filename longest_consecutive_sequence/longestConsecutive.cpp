#include <vector>
#include <unordered_set>
using namespace std;
class Solution {
	public:
		int longestConsecutive(vector<int>& nums){
			unordered_set<int> hashset;
			for (int n : nums){
				hashset.insert(n);
			}
			
			int longest_sequence = 0;
			for (int n : nums) {
				if (!hashset.contains(n-1)){
					int current_num = n;
					int current_sequence = 1;

					while (hashset.contains(current_num+1)){
						current_num += 1;
						current_sequence += 1;
					}

					longest_sequence = (current_sequence > longest_sequence)? current_sequence : longest_sequence;
				}
			}

			return longest_sequence;
		}
};

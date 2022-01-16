from typing import List
class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        hashset = set(nums)
        longest_sequence = 0
        for n in nums:
            if n-1 not in hashset:
                current_num = n
                current_sequence = 1

                while current_num + 1 in hashset:
                    current_num += 1
                    current_sequence += 1
                longest_sequence = max(longest_sequence, current_sequence)
        return longest_sequence


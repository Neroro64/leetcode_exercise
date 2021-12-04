#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
from typing import List
class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        self.radixSort(nums)
        max_length, cur_length = 0,0

        prev = nums[0]
        for i in range(1, len(nums)):
            cur = nums[i]
            if cur - prev == 1:
                cur_length += 1
            else:
                if cur_length > max_length:
                    max_length = cur_length
                cur_length = 0
        return max_length

    def radixSort(self, nums: List[int]):
        max_elem = max(nums)
        digit = 1
        N = len(nums)
        while max_elem / digit >= 1:    # O(log10(max(nums)))
            counts = [0]*10
            for n in nums:              # O(n)
                idx = int((n / digit) % 10)
                counts[idx] += 1
            for j in range(1,10):       # O(10)
                counts[j] += counts[j-1]

            s = 0
            elem = nums[0]
            while s < N:
                d = int((elem / digit) % 10)
                counts[d] -= 1
                pos = counts[d]
                prev_elem = nums[pos]
                nums[pos] = elem
                elem = prev_elem
                s += 1
            digit *= 10


if __name__ == "__main__":
   arr = np.random.randint(1,100,10)
   print("Before: ", arr)
   Solution().radixSort(arr)
   print("After: ", arr)


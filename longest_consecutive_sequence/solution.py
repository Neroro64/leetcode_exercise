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
        N = len(nums)
        if N <= 1:
            return

        max_elem = max(nums)
        digit = 1
        while max_elem / digit >= 1:    # O(log10(max(nums)))
            counts = [0]*11
            for n in nums:              # O(n)
                idx = int((n / digit) % 10)
                counts[idx+1] += 1
            for j in range(1,11):       # O(10)
                counts[j] += counts[j-1]

            elem_id = 0
            d = 0
            while elem_id < N:
                elem = nums[elem_id]
                d = int((elem / digit) % 10)
                pos = counts[d]

                if pos <= elem_id:
                    elem_id += 1
                    continue

                counts[d] += 1
                prev_elem = nums[pos]
                nums[pos] = elem
                nums[elem_id] = prev_elem
            digit *= 10

    def test(self):
        def test_case(_id, name, arr): self.radixSort(arr); print("T{0}: {1} [{2}]".format(_id, name, self.validate(arr)))
        _id = 0
        test_case(_id, "empty", [])
        _id+=1
        test_case(_id, "one elem", [1])
        _id+=1
        test_case(_id, "two elems", [2,1])
        _id+=1
        test_case(_id, "ten elems with nine same elem", [2]+[1]*9)
        _id+=1
        test_case(_id, "alread_sorted", [i for i in range(10)])
        _id+=1
        test_case(_id, "reversed", [i for i in range(10, 0, -1)])
        _id+=1
        test_case(_id, "already_sorted 1 000", [i for i in range(1000)])
        _id+=1
        test_case(_id, "reversed 1 000", [i for i in range(1000,0,-1)])
        _id+=1
        test_case(_id, "uniformly random 10 000", np.random.uniform(0,1000,1000).tolist())
        _id+=1
        test_case(_id, "gaussian random 100 000", np.random.normal(0,1000,10000).tolist())

    def validate(self, arr:List[int]) -> bool:
        flag = False
        if(all(arr[i] <= arr[i + 1] for i in range(len(arr)-1))):
            flag = True
        return flag

if __name__ == "__main__":
    #  Solution().test()
    arr = np.random.randint(0,20,10).tolist()
    print("Before: ", arr)
    Solution().radixSort(arr)
    print("After: ", arr)

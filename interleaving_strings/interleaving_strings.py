import numpy as np

class Solution:
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
        l1, l2, l3 = len(s1), len(s2), len(s3)
        dp = np.zeros((l1+1,l2+1))
        
        if l1+l2+l3 == 0: return True
        elif l3 == 0 or l1+l2 != l3 or l1+l2 == 0: return False
        elif l1 == 0: return s2 == s3
        elif l2 == 0: return s1 == s3

        dp[0,0] = 1
        for i in range(l1):
            if s1[i] == s3[i]:
                dp[i+1][0] = dp[i][0]
        for j in range(l2):
            if s2[j] == s3[j]:
                dp[0][j+1] = dp[0][j]
        
        if dp[0,1] != 1 and dp[1,0] != 1:
            return False
        
        z = 0
        for i in range(1,l1+1):
            for j in range(1,l2+1):
                z = i+j-1
                if (dp[i,j-1] == 1 and s2[j-1]==s3[z]) or \
                    (dp[i-1,j]==1 and s1[i-1]==s3[z]):
                    dp[i][j] = 1
    
        return dp[l1,l2]




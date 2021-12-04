class Solution:
    def compare(self, s1,s2,s3, p1,p2,p3, check_head):
        if p3[0] >= p3[1]:
            return True
        
        if check_head:
            idx = 0
            inc = 1
        else:
            idx = 1
            inc = -1
        _p1, _p2, _p3 = p1[idx], p2[idx], p3[idx]
        
        print(p1," | ", p2, " | ", p3)
        if s1[_p1] == s3[_p3]:
            p1[idx] += inc 
            p3[idx] += inc 
            return self.compare(s1,s2,s3, p1,p2,p3, not check_head)
        elif s2[_p2] == s3[_p3]:
            p2[idx] += inc 
            p3[idx] += inc
            return self.compare(s1,s2,s3,p1,p2,p3, not check_head)
        return False
    
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
        p1,p2,p3 = [0, len(s1)-1], [0,len(s2)-1], [0,len(s3)-1]
        return self.compare(s1,s2,s3,p1,p2,p3,True)

#  a = "aabcc"
#  b = "dbbca"
#  c = "aadbbcbcac"
#  print(Solution().isInterleave(a,b,c))

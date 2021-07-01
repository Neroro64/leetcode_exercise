class Solution {
public:
    struct ptr {
      int head;
      int tail;
    };
    bool isInterleave(string s1, string s2, string s3) {
        ptr p1 = {0,s1.size()-1}, p2 = {0,s2.size()-1}, p3 = {0,s3.size()-1};
        return compare(s1,s2,s3, ptr1,ptr2,ptr3);   
    }

    bool compare (string &s1, string &s2, string &s3, ptr p1, ptr p2, ptr p3){
        if (p3.head >= p3.tail)
            return true;

        if (s1[p1.head] == s3[p3.head]){
            ++p1.head;
            ++p3.head;
        }
        else if (s2[p2.head] == s3[p3.head]){
            ++p2.head;
            ++p3.head;
        }
        else{
            return false;
        }
        
        if (s1[p1.tail] == s3[p3.tail]){
            --p1.tail;
            --p3.tail;
        }
        else if (s2[p2.tail] == s3[p3.tail]){
            --p2.tail;
            --p3.tail;
        }
        else{
            sreturn false;
        }
        
        return compare(s1,s2,s3, p1, p2, p3);
        





    }


};

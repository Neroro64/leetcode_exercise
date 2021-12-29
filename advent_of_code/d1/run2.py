_in = open("input2.txt", 'r').read().split("\n")
N = len(_in)
if N >= 1:
    num_inc = 0
    prevSum = 0
    for i in range(0,len(_in), 3):
        if not _in[i].isnumeric(): continue
        if not _in[i+1].isnumeric(): continue
        if not _in[i+2].isnumeric(): continue
        currSum = int(_in[i]) + int(_in[i+1]) + int(_in[i+2])
        if prevSum > 0 and currSum > prevSum:
            num_inc += 1
        prevSum = currSum
    print(num_inc)

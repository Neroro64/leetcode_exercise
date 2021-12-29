_in = open("input.txt", 'r').read().split("\n")
N = len(_in)
if N >= 1:
    num_inc = 1
    for i in range(1,len(_in)):
        if not _in[i].isnumeric(): continue
        if int(_in[i]) > int(_in[i-1]): num_inc += 1

    print(num_inc)

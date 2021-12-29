with open("input.txt", 'r') as f:
    ops = {"forward":[ 1,0 ], "up":[ 0,-1 ], "down":[ 0,1 ]} # (horizontal, vertical)
    start = [0,0]
    inputs = f.read().split("\n")
    for move in inputs:
        if move == "":
            continue
        dir,step = move.split(" ")
        step = int(step)
        action = ops[dir]
        start[0] += action[0] * step
        start[1] += action[1] * step
    print(start, " = ", start[0]*start[1])




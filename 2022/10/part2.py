program = []

with open("input.txt") as inp:
    for line in inp:
        parts = line.strip().split()
        if parts[0] == "noop":
            program.append(("noop", None))
        else:
            program.append(("addx", int(parts[1])))


def log_cycle(cycle, x):
    pos = (cycle-1) % 40
    if pos == x or pos == x-1 or pos == x+1:
        print("#",end="")
    else:
        print(".",end="")
    if pos==39:
        print("")

x = 1
cycle = 1
for op, val in program:
    if op == "noop":
        log_cycle(cycle, x)
        cycle+=1
    else:
        log_cycle(cycle, x)
        cycle+=1
        log_cycle(cycle, x)
        cycle+=1
        x+=val

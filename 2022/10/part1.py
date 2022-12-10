program = []

with open("input.txt") as inp:
    for line in inp:
        parts = line.strip().split()
        if parts[0] == "noop":
            program.append(("noop", None))
        else:
            program.append(("addx", int(parts[1])))


total = 0
def log_cycle(cycle, x):
    print((cycle, x))
    global total
    if cycle in (20, 60, 100, 140, 180, 220):
        total += cycle * x

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

print(total)

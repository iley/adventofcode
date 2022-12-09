moves = []
with open("input.txt") as inp:
    for line in inp:
        direction, nsteps = line.split()
        moves.append((direction, int(nsteps)))


def print_pos(rope, width, height):
    for row in reversed(range(height)):
        for col in range(width):
            if (col, row) == rope[0]:
                print("H", end="")
                continue
            for i in range(1, len(rope)):
                if (col, row) == rope[i]:
                    print(i, end="")
                    break
            else:
                if (col, row) == (0, 0):
                    print("s", end="")
                else:
                    print(".", end="")
        print("")
    print("")

shifts = {
    (0, 2): (0, 1),
    (0, -2): (0, -1),
    (2, 0): (1, 0),
    (-2, 0): (-1, 0),
    (1, 2): (1, 1),
    (1, -2): (1, -1),
    (2, 1): (1, 1),
    (-2, 1): (-1, 1),
    (-1, 2): (-1, 1),
    (-2, -1): (-1, -1),
    (-1, -2): (-1, -1),
    (2, -1): (1, -1),
    (2, 2): (1, 1),
    (2, -2): (1, -1),
    (-2, 2): (-1, 1),
    (-2, -2): (-1, -1),
}


rope = [(0, 0)] * 10

visited = set([(0, 0)])

# print_pos(rope, 20, 20)
for direction, nsteps in moves:
    # print("== %s %s ==" % (direction, nsteps))
    for i in range(nsteps):
        if direction == "R":
            rope[0] = (rope[0][0] + 1, rope[0][1])
        elif direction == "L":
            rope[0] = (rope[0][0] - 1, rope[0][1])
        elif direction == "U":
            rope[0] = (rope[0][0], rope[0][1] + 1)
        elif direction == "D":
            rope[0] = (rope[0][0], rope[0][1] - 1)
        for i in range(1, len(rope)):
            hx, hy = rope[i-1]
            tx, ty = rope[i]
            diff = ((hx - tx), (hy - ty))
            shift = shifts.get(diff, (0, 0))
            tx += shift[0]
            ty += shift[1]
            rope[i] = (tx, ty)
        # print_pos(rope, 20, 20)
        visited.add(rope[-1])

print(len(visited))

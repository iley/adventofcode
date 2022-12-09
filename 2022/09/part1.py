moves = []
with open("input.txt") as inp:
    for line in inp:
        direction, nsteps = line.split()
        moves.append((direction, int(nsteps)))


def print_pos(hx, hy, tx, ty, width, height):
    for row in reversed(range(height)):
        for col in range(width):
            if (col, row) == (hx, hy):
                print("H", end="")
            elif (col, row) == (tx, ty):
                print("T", end="")
            elif (col, row) == (0, 0):
                print("s", end="")
            else:
                print(".", end="")
        print("")
    print("")

def print_visited(visited, width, height):
    for row in reversed(range(height)):
        for col in range(width):
            if (col, row) in visited:
                print("#", end="")
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
}


hx, hy = (0, 0)
tx, ty = (0, 0)

visited = set([(0, 0)])

#print_pos(hx, hy, tx, ty, 10, 10)
for direction, nsteps in moves:
    #print("== %s %s ==" % (direction, nsteps))
    for i in range(nsteps):
        if direction == "R":
            hx += 1
        elif direction == "L":
            hx -= 1
        elif direction == "U":
            hy += 1
        elif direction == "D":
            hy -= 1
        diff = ((hx - tx), (hy - ty))
        shift = shifts.get(diff, (0, 0))
        tx += shift[0]
        ty += shift[1]
        #print_pos(hx, hy, tx, ty, 10, 10)
        visited.add((tx, ty))

#print_visited(visited, 10, 10)
print(len(visited))

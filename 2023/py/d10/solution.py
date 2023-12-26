start = (0, 0)
m: dict[tuple[int, int], list[tuple[int, int]]] = {}

def add_connection(a: tuple[int, int], b: tuple[int, int]):
    m[a] = list(set(m.get(a, []) + [b]))

with open("input.txt") as f:
    lines = f.readlines()
    for row, line in enumerate(lines):
        for col, char in enumerate(line.strip()):
            if char == "S":
                start = (row, col)
                continue
            if char == "|":
                a = (row - 1, col)
                b = (row + 1, col)
            elif char == "-":
                a = (row, col - 1)
                b = (row, col + 1)
            elif char == "L":
                a = (row - 1, col)
                b = (row, col + 1)
            elif char == "F":
                a = (row + 1, col)
                b = (row, col + 1)
            elif char == "7":
                a = (row + 1, col)
                b = (row, col - 1)
            elif char == "J":
                a = (row - 1, col)
                b = (row, col - 1)
            else:
                continue
            cur = (row, col)
            add_connection(cur, a)
            add_connection(cur, b)

for node, neighbors in list(m.items()):
    if start in neighbors:
        m[start] = m.get(start, []) + [node]

def loop_length(node: tuple[int, int]):
    visited = set()
    steps = 0
    while True:
        print("curent node: %s" % (node,))
        possible_next_nodes = [n for n in m[node] if n not in visited]
        print("possible next nodes: %s" % (possible_next_nodes,))
        if possible_next_nodes:
            node = possible_next_nodes[0]
            visited.add(node)
            steps += 1
        else:
            return steps

grid = [[ ch for ch in line ] for line in lines]
grid2 = [[ ch for ch in line ] for line in lines]

def rotate_right(direction: tuple[int, int]):
    if direction == (1, 0):
        return (0, -1)
    if direction == (-1, 0):
        return (0, 1)
    if direction == (0, 1):
        return (1, 0)
    if direction == (0, -1):
        return (-1, 0)
    raise Exception("Invalid direction")

def rotate_left(direction: tuple[int, int]):
    if direction == (1, 0):
        return (0, 1)
    if direction == (-1, 0):
        return (0, -1)
    if direction == (0, 1):
        return (-1, 0)
    if direction == (0, -1):
        return (1, 0)
    raise Exception("Invalid direction")

def traverse(node: tuple[int, int]):
    visited = set([node])
    steps = 0
    while True:
        row, col = node
        grid[row][col] = "#"
        possible_next_nodes = [n for n in m[node] if n not in visited]
        if possible_next_nodes:
            node = possible_next_nodes[0]
            drow, dcol = node[0] - row, node[1] - col
            dir = (drow, dcol)
            dir_side = rotate_right(dir)
            side_node = (row + dir_side[0], col + dir_side[1])
            grid2[side_node[0]][side_node[1]] = "I"

            visited.add(node)
            steps += 1
        else:
            return steps

# length = loop_length(start)
# print("Loop length is %d" % length)
# print("Part 1 solution is %d"  % ((length + 1) // 2))

traverse(start)

for row in range(len(grid2)):
    for col in range(len(grid2[row])):
        if grid[row][col] != "#" and grid2[row][col] == "I":
            grid[row][col] = "I"

while True:
    changed = False
    for row in range(len(grid)):
        for col in range(len(grid[row])):
            if grid[row][col] == "I":
                if grid[row - 1][col] == ".":
                    grid[row - 1][col] = "I"
                    changed = True
                if grid[row + 1][col] == ".":
                    grid[row + 1][col] = "I"
                    changed = True
                if grid[row][col - 1] == ".":
                    grid[row][col - 1] = "I"
                    changed = True
                if grid[row][col + 1] == ".":
                    grid[row][col + 1] = "I"
                    changed = True
    if not changed:
        break

c = 0
for row in range(len(grid)):
    for col in range(len(grid[row])):
        if grid[row][col] == "I":
            c += 1
print(c)

for row in range(len(grid)):
    for col in range(len(grid[row])):
        if grid[row][col] != "I":
            grid[row][col] = lines[row][col]

with open("output.txt", "w") as f:
    for line in grid:
        f.write("".join(line))

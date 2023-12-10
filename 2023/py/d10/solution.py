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

length = loop_length(start)
print("Loop length is %d" % length)
print("Part 1 solution is %d"  % ((length + 1) // 2))

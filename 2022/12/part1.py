heightmap = []
startpos = None
endpos = None

with open("input.txt") as inp:
    for line in inp:
        row = []
        for char in line.strip():
            if char.islower():
                row.append(ord(char) - ord('a'))
            elif char == 'S':
                startpos = (len(heightmap), len(row))
                row.append(0)
            elif char == 'E':
                endpos = (len(heightmap), len(row))
                row.append(25)
        heightmap.append(row)


rows = len(heightmap)
cols = len(heightmap[0])

unvisited = set((row, col) for row in range(rows) for col in range(cols))
current = startpos
moves = ((0, 1), (1, 0), (0, -1), (-1, 0))
INF = 1000000

distances = {}
for row in range(rows):
    for col in range(cols):
        distances[(row, col)] = INF
distances[startpos] = 0

while endpos in unvisited:
    row, col = current
    for move in moves:
        nrow, ncol = (row + move[0], col + move[1])
        if nrow < 0 or nrow >= rows or ncol < 0 or ncol >= cols:
            continue
        if heightmap[nrow][ncol] - heightmap[row][col] > 1:
            continue
        neighbour = (nrow, ncol)
        if neighbour not in unvisited:
            continue
        if distances[current] + 1 < distances[neighbour]:
            distances[neighbour] = distances[current] + 1

    unvisited.remove(current)

    for row in range(rows):
        for col in range(cols):
            if (row, col) == current:
                print("X", end="")
            elif (row, col) not in unvisited:
                print(".", end="")
            elif distances[(row, col)] == INF:
                print("#", end="")
            else:
                print("X", end="")
        print("")
    print("")

    mindist = INF
    for pos in unvisited:
        if distances[pos] < mindist:
            mindist = distances[pos]
            current = pos

print(distances[endpos])

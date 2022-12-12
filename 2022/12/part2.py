heightmap = []
endpos = None
INF = 1000000

with open("input.txt") as inp:
    for line in inp:
        row = []
        for char in line.strip():
            if char.islower():
                row.append(ord(char) - ord('a'))
            elif char == 'S':
                row.append(0)
            elif char == 'E':
                endpos = (len(heightmap), len(row))
                row.append(25)
        heightmap.append(row)


rows = len(heightmap)
cols = len(heightmap[0])

def shortest_distance(startpos):
    unvisited = set((row, col) for row in range(rows) for col in range(cols))
    current = startpos
    moves = ((0, 1), (1, 0), (0, -1), (-1, 0))

    distances = {}
    for row in range(rows):
        for col in range(cols):
            distances[(row, col)] = INF
    distances[startpos] = 0

    mindist = 0
    while endpos in unvisited and mindist != INF:
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

        mindist = INF
        for pos in unvisited:
            if distances[pos] < mindist:
                mindist = distances[pos]
                current = pos

    return distances[endpos]

mindist = INF
for row in range(rows):
    for col in range(cols):
        if heightmap[row][col] != 0:
            continue
        dist = shortest_distance((row, col))
        if dist < mindist:
            mindist = dist
        print((row, col), dist, mindist)

print(mindist)

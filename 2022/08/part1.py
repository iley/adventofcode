grid = []

with open("input.txt") as inp:
    for line in inp:
        grid.append([int(h) for h in line.strip()])

def print_vis():
    for row in range(rows):
        for col in range(cols):
            if vis[row][col]:
                print(1, end="")
            else:
                print(0, end="")
        print("")

rows = len(grid)
cols = len(grid[0])

vis = []
for row in grid:
    vis.append([False] * cols)

for col in range(cols):
    vis[0][col-1] = True
    vis[rows-1][col] = True

for row in range(rows):
    vis[row][0] = True
    vis[row][cols-1] = True

for row in range(rows):
    for col in range(cols):
        if (all(grid[r][col] < grid[row][col] for r in range(row)) or
            all(grid[r][col] < grid[row][col] for r in range(row+1, rows)) or
            all(grid[row][c] < grid[row][col] for c in range(col)) or
            all(grid[row][c] < grid[row][col] for c in range(col+1, cols))):
            vis[row][col] = True

count = 0
for row in range(rows):
    for col in range(cols):
        if vis[row][col]:
            count += 1

print_vis()

print(count)

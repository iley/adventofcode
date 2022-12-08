grid = []

with open("input.txt") as inp:
    for line in inp:
        grid.append([int(h) for h in line.strip()])

rows = len(grid)
cols = len(grid[0])

scores = []
for row in grid:
    scores.append([0] * cols)

for row in range(rows):
    for col in range(cols):
        up = 0
        for r in reversed(range(row)):
            up+=1
            if grid[r][col] >= grid[row][col]:
                break
        down = 0
        for r in range(row+1, rows):
            down+=1
            if grid[r][col] >= grid[row][col]:
                break
        left = 0
        for c in reversed(range(col)):
            left += 1
            if grid[row][c] >= grid[row][col]:
                break
        right = 0
        for c in range(col+1, cols):
            right += 1
            if grid[row][c] >= grid[row][col]:
                break
        scores[row][col] = up * down * left * right

max_score = 0
for row in range(rows):
    for col in range(cols):
        if scores[row][col] > max_score:
            max_score = scores[row][col]

print(max_score)

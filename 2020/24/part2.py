#!/usr/bin/env python3
from collections import defaultdict
import sys


steps = 100


def move(x, y, d):
    # print('move(%d, %d, %s)' % (x, y, d))
    even = (y % 2) == 0
    if d == 'w':
        return x-1, y
    if d == 'e':
        return x+1, y
    if d == 'nw':
        if even:
            return x-1, y+1
        else:
            return x, y+1
    if d == 'ne':
        if even:
            return x, y+1
        else:
            return x+1, y+1
    if d == 'sw':
        if even:
            return x-1, y-1
        else:
            return x, y-1
    if d == 'se':
        if even:
            return x, y-1
        else:
            return x+1, y-1


def directions(line):
    while len(line) > 0:
        if line.startswith('n') or line.startswith('s'):
            yield line[0:2]
            line = line[2:]
        else:
            yield line[0]
            line = line[1:]


def neighbours(x, y):
    if y % 2 == 0:
        return ( (x-1, y), (x-1, y+1), (x, y+1), (x+1, y), (x, y-1), (x-1, y-1) )
    else:
        return ( (x-1, y), (x, y+1), (x+1, y+1), (x+1, y), (x+1, y-1), (x, y-1) )

def neighbour_count(grid, x, y):
    s = 0
    for nx, ny in neighbours(x, y):
        s += grid[(nx,ny)]
    return s


def step(grid):
    for pos in list(grid.keys()):
        x, y = pos
        for nx, ny in neighbours(x, y):
            grid[(nx,ny)] = grid[(nx,ny)]

    newgrid = defaultdict(int)
    for pos, val in list(grid.items()):
        x, y = pos
        n = neighbour_count(grid, x, y)
        if val == 1 and (n == 0 or n > 2):
            newgrid[(x,y)] = 0
        elif val == 0 and n == 2:
            newgrid[(x,y)] = 1
        else:
            newgrid[(x,y)] = val
    return newgrid


lines = []

for line in sys.stdin:
    line = line.strip()
    if line != "":
        lines.append(line)

# print(lines)

grid = defaultdict(int)

for line in lines:
    x, y = 0, 0
    for d in directions(line):
        x, y = move(x, y, d)
    grid[(x,y)] = 1 - grid[(x,y)]
    # print('flip (%d, %d)' % (x, y))

for i in range(steps):
    grid = step(grid)
    print('day %d: %d' % (i+1, sum(grid.values())))

s = sum(grid.values())
print(s)

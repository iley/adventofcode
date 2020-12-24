#!/usr/bin/env python3
from collections import defaultdict
import sys


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


s = sum(grid.values())
print(s)

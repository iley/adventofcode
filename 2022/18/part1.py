import sys
import itertools

voxels = set()

with open(sys.argv[1]) as inp:
    for line in inp:
        parts = line.split(",")
        x, y, z = (int(p) for p in parts)
        voxels.add((x, y, z))


shifts = [
    (0, 0, 1),
    (0, 0, -1),
    (-1, 0, 0),
    (1, 0, 0),
    (0, 1, 0),
    (0, -1, 0),
]

area = 0
for x, y, z in voxels:
    for dx, dy, dz in shifts:
        x1, y1, z1 = x+dx, y+dy, z+dz
        if (x1, y1, z1) not in voxels:
            area += 1 


print(area)

import sys
import itertools
import functools

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

minx, miny, minz = 1000, 1000, 1000
maxx, maxy, maxz = 0, 0, 0
for x, y, z in voxels:
    if x < minx:
        minx = x
    if x > maxx:
        maxx = x
    if y < miny:
        miny = y
    if y > maxy:
        maxy = y
    if z < minz:
        minz = z
    if z > maxz:
        maxz = z


voxel_outside = (maxx+1, maxy+1, maxz+1)
grid = {}
for x in range(minx-1, maxx+1):
    for y in range(miny-1, maxy+1):
        for z in range(minz-1, maxz+1):
            grid[x,y,z] = 0

for x, y, z in voxels:
    grid[x,y,z] = 1

def path_exists(from_voxel):
    visited = set()
    def dfs(from_voxel):
        if from_voxel not in grid:
            return True
        if from_voxel in visited:
            return False
        visited.add(from_voxel)
        x, y, z = from_voxel
        for dx, dy, dz in shifts:
            x1, y1, z1 = x+dx, y+dy, z+dz
            if (x1, y1, z1) not in voxels and dfs((x1,y1,z1)):
                return True
        return False
    return dfs(from_voxel)


inner_cells = set()

for x in range(maxx):
    for y in range(maxy):
        for z in range(maxz):
            if (x,y,z) in voxels:
                continue
            if not path_exists((x,y,z)):
                inner_cells.add((x,y,z))

area = 0
for x, y, z in voxels:
    for dx, dy, dz in shifts:
        x1, y1, z1 = x+dx, y+dy, z+dz
        if (x1, y1, z1) not in voxels and (x1, y1, z1) not in inner_cells:
            area += 1 


print(area)

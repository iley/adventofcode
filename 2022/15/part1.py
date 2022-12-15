import re

inp_re = re.compile(r"Sensor at x=(-?\d+), y=(-?\d+): closest beacon is at x=(-?\d+), y=(-?\d+)")

sensors = []
beacons = []
dists = []

def dist(x1, y1, x2, y2):
    return abs(x1 - x2) + abs(y1 - y2)

with open("input.txt") as inp:
    for line in inp:
        m = inp_re.match(line)
        assert m is not None
        sx, sy, bx, by = int(m.group(1)), int(m.group(2)), int(m.group(3)), int(m.group(4))
        sensors.append((sx, sy))
        beacons.append((bx, by))
        dists.append(dist(sx, sy, bx, by))


def can_contain_beacon(x, y):
    if (x, y) in beacons:
        return True
    for i in range(len(sensors)):
        sx, sy = sensors[i]
        if dist(sx, sy, x, y) <= dists[i]:
            return False
    return True


maxx = max(x for x, _ in sensors) + max(dists)
minx = min(x for x, _ in sensors) - max(dists)

search_y = 2000000

s = 0
for x in range(minx, maxx+1):
    if can_contain_beacon(x, search_y):
        continue
    s+=1
print(s)

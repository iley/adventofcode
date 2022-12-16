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
    for i in range(len(sensors)):
        sx, sy = sensors[i]
        if dist(sx, sy, x, y) <= dists[i]:
            return False
    return True


def edge_points(sx, sy, dist):
    x = sx
    y = sy - (dist + 1)
    for i in range(dist+1):
        x += 1
        y += 1
        yield x, y

    x = sx + dist + 1
    y = sy
    for i in range(dist+1):
        x -= 1
        y += 1
        yield x, y

    x = sx
    y = sy + (dist + 1)
    for i in range(dist+1):
        x -= 1
        y -= 1
        yield x, y

    x = sx - (dist + 1)
    y = sy
    for i in range(dist+1):
        x += 1
        y -= 1
        yield x, y



maxcoord = 4000000
#maxcoord = 20

for i in range(len(sensors)):
    print("%d out of %d" % (i, len(sensors)))
    sx, sy = sensors[i]
    d = dists[i]
    for x, y in edge_points(sx, sy, d):
        if x > maxcoord or y > maxcoord or x < 0 or y < 0:
            continue
        if can_contain_beacon(x, y):
            bx, by = x, y

print(bx, by)
print(bx * 4000000 + by)

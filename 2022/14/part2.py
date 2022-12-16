def draw_line(m, start, end):
    sx, sy = start
    ex, ey = end
    if sx == ex:
        y1 = min(sy, ey)
        y2 = max(sy, ey)
        for y in range(y1, y2+1):
            m[y][sx] = "#"
    else:
        x1 = min(sx, ex)
        x2 = max(sx, ex)
        for x in range(x1, x2+1):
            m[sy][x] = "#"

def print_map(m):
    for y in range(height):
        for x in range(width):
            print(m[y][x], end="")
        print("")
    print("")


def simulate(m, x, y):
    if m[y][x] == "o":
        return False
    if m[y+1][x] == ".":
        return simulate(m, x, y+1)
    elif m[y+1][x-1] == ".":
        return simulate(m, x-1, y+1)
    elif m[y+1][x+1] == ".":
        return simulate(m, x+1, y+1)
    else:
        m[y][x] = "o"
        return True


lines = []
with open("input.txt") as inp:
    for line in inp:
        line = line.strip()
        tokens = line.split(" -> ")
        points = []
        for tok in tokens:
            x, y = tok.split(",")
            points.append((int(x), int(y)))
        lines.append(points)


maxx = 0
maxy = 0
for line in lines:
    for point in line:
        x, y = point
        if x > maxx:
            maxx = x
        if y > maxy:
            maxy = y

width = 2*(maxx + 1)
height = maxy + 3

m = []
for y in range(height):
    row = []
    for x in range(width):
        row.append(".")
    m.append(row)

for x in range(width):
    m[height-1][x] = "#"


for points in lines:
    for i in range(1, len(points)):
        start = points[i-1]
        end = points[i]
        draw_line(m, start, end)

#print_map(m)

units = 0
while True:
    landed = simulate(m, 500, 0)
    #print_map(m)
    if landed:
        units += 1
    else:
        break
print(units)

def prio(item):
    if ord('a') <= ord(item) <= ord('z'):
        return 1 + ord(item) - ord('a')
    return 27 + ord(item) - ord('A')


lines = []
with open("input.txt") as inp:
    for line in inp:
        line = line[:-1]
        lines.append(line)

s = 0
i = 0
while i < len(lines):
    set1 = set(lines[i])
    set2 = set(lines[i+1])
    set3 = set(lines[i+2])

    item = list(set1.intersection(set2).intersection(set3))[0]
    s += prio(item)

    i+=3

print(s)

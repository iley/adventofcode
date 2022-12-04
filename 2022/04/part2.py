def parse_range(s):
    start, end = s.split('-')
    return int(start), int(end)

def overlaps(range1, range2):
    s1, e1 = range1
    s2, e2 = range2
    return s1 <= e2 and s2 <= e1

s = 0
with open('input.txt') as inp:
    for line in inp:
        line = line[:-1]
        first, second = line.split(',')
        first = parse_range(first)
        second = parse_range(second)
        if overlaps(first, second):
            s += 1

print(s)

def parse_range(s):
    start, end = s.split('-')
    return int(start), int(end)

def includes(range1, range2):
    s1, e1 = range1
    s2, e2 = range2
    return s1 <= s2 and e1 >= e2

s = 0
with open('input.txt') as inp:
    for line in inp:
        line = line[:-1]
        first, second = line.split(',')
        first = parse_range(first)
        second = parse_range(second)
        if includes(first, second) or includes(second, first):
            s += 1

print(s)

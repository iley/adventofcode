def prio(item):
    if ord('a') <= ord(item) <= ord('z'):
        return 1 + ord(item) - ord('a')
    return 27 + ord(item) - ord('A')


s = 0
with open("input.txt") as inp:
    for line in inp:
        line = line[:-1]
        x = int(len(line)/2)
        first = line[:x]
        second = line[x:]

        item = list(set(first).intersection(set(second)))[0]
        s += prio(item)

print(s)

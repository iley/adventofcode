import json

def compare_lists(left, right):
    for i in range(min(len(left), len(right))):
        cmp = compare(left[i], right[i])
        if cmp != 0:
            return cmp
    return len(left) - len(right)

def compare(left, right):
    if isinstance(left, int) and isinstance(right, list):
        left = [left]
    if isinstance(left, list) and isinstance(right, int):
        right = [right]
    if isinstance(left, int) and isinstance(right, int):
        return left - right
    if isinstance(left, list) and isinstance(right, list):
        return compare_lists(left, right)
    assert False



with open("input.txt") as inp:
    lines = [line.strip() for line in inp]

pairs = []
for i in range(0, len(lines), 3):
    left = json.loads(lines[i])
    right = json.loads(lines[i+1])
    pairs.append((left, right))

s = 0
for i in range(len(pairs)):
    left, right = pairs[i]
    if compare(left, right) < 0:
        s += i + 1

print(s)

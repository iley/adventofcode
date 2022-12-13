import json
from functools import cmp_to_key

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


divider1 = [[2]]
divider2 = [[6]]

packets = [divider1, divider2]
with open("input.txt") as inp:
    for line in inp:
        line = line.strip()
        if line == "":
            continue
        packets.append(json.loads(line))

packets.sort(key=cmp_to_key(compare))

div1_index = None
div2_index = None
for i in range(len(packets)):
    if packets[i] == divider1:
        assert div1_index is None
        div1_index = i + 1
    if packets[i] == divider2:
        assert div2_index is None
        div2_index = i + 1

print(div1_index*div2_index)

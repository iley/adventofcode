#!/usr/bin/env python3
import sys

def read_groups(input_file):
    group = []
    for line in input_file:
        line = line.rstrip()
        if line == "":
            yield group
            group = []
        else:
            group.append(line)
    if len(group) > 0:
        yield group


def union(group):
    union = set(group[0])
    for other in group[1:]:
        union = union | set(other)
    return union


answer = 0

for group in read_groups(sys.stdin):
    matches = union(group)
    # print("group %s has %d matches" % (group, len(matches)))
    answer += len(matches)

print(answer)

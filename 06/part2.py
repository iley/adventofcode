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


def intersection(group):
    intersection = set(group[0])
    for other in group[1:]:
        intersection = intersection & set(other)
    return intersection


answer = 0

for group in read_groups(sys.stdin):
    matches = intersection(group)
    answer += len(matches)

print(answer)

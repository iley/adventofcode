#!/usr/bin/env python3
import os
import sys

joltages = [0]

for line in sys.stdin:
    try:
        n = int(line)
    except ValueError:
        continue
    joltages.append(n)

joltages.sort()
joltages.append(joltages[-1] + 3)


def combinations(joltages, start=1):
    # find first adapter that can be omitted
    for i in range(start, len(joltages)-1):
        if joltages[i+1] - joltages[i-1] <= 3:
            return combinations(joltages, i+1) + combinations(joltages[0:i] + joltages[i+1:], i)
    else:
        return 1


def parts(joltages):
    i = 0
    for j in range(i+1, len(joltages)):
        if joltages[j] - joltages[j-1] == 3:
            yield joltages[i:j+1]
            i = j


c = 1
for p in parts(joltages):
    c *= combinations(p)

print(c)

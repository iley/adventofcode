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

diff1 = 0
diff3 = 0

for i in range(1, len(joltages)):
    diff = joltages[i] - joltages[i-1]
    if diff == 1:
        diff1 += 1
    elif diff == 3:
        diff3 += 1

print(diff1 * diff3)

#!/usr/bin/env python3
import os
import sys

if len(sys.argv) != 3:
    print("Usage %s N INPUT_FILE", file=sys.stderr)
    os.exit(1)

window = int(sys.argv[1])
numbers = []

with open(sys.argv[2]) as inp:
    for line in inp:
        try:
            n = int(line)
        except ValueError:
            continue
        numbers.append(n)


def valid(n, prev):
    for i in range(len(prev)):
        for j in range(i+1, len(prev)):
            if n == prev[i] + prev[j]:
                return True
    return False


for i in range(window, len(numbers)):
    if not valid(numbers[i], numbers[i-window:i]):
        print(numbers[i])
        break

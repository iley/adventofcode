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


invalid_number = None

for i in range(window, len(numbers)):
    if not valid(numbers[i], numbers[i-window:i]):
        invalid_number = numbers[i]
        break


for i in range(len(numbers)):
    s = 0
    seq = []
    for j in range(i, len(numbers)):
        s += numbers[j]
        seq.append(numbers[j])
        if s >= invalid_number:
            break
    if s == invalid_number and len(seq) >= 2:
        print(min(seq) + max(seq))
        break
else:
    print('not found')

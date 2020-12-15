#!/usr/bin/env python3
import re
import sys


cmd_re = re.compile('([NSEWLRF])(\d+)')


def load(input_file):
    instructions = []
    for line in input_file:
        m = cmd_re.match(line)
        if m is None:
            continue
        cmd, arg = m.group(1), int(m.group(2))
        instructions.append((cmd, arg))
    return instructions


deltas = {
    'N': ( 0, 1),
    'E': ( 1, 0),
    'S': ( 0,-1),
    'W': (-1, 0),
}

ang_to_dir = {
    0: 'N',
    90: 'E',
    180: 'S',
    270: 'W',
}


def solve(instructions):
    x, y = 0, 0
    ang = 90
    for cmd, arg in instructions:
        if cmd == 'F':
            cmd = ang_to_dir[ang]

        if cmd in 'NSEW':
            dx, dy = deltas[cmd]
            x += dx * arg
            y += dy * arg
        elif cmd == 'L':
            ang = (ang - arg) % 360
        elif cmd == 'R':
            ang = (ang + arg) % 360

    return abs(x) + abs(y)


if len(sys.argv) < 2:
    print("Usage: %s FILE" % sys.argv[0], file=sys.stderr)
    sys.exit(1)


with open(sys.argv[1]) as inp:
    instructions = load(inp)


print(solve(instructions))

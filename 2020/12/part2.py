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


def solve(instructions):
    x = 0
    y = 0
    wx = 10
    wy = 1

    for cmd, arg in instructions:
        if cmd in 'NSEW':
            dx, dy = deltas[cmd]
            wx += dx * arg
            wy += dy * arg
        elif cmd == 'L':
            if arg == 90:
                (wx, wy) = (-wy, wx)
            elif arg == 180:
                (wx, wy) = (-wx, -wy)
            elif arg == 270:
                (wx, wy) = (wy, -wx)
            else:
                assert False
        elif cmd == 'R':
            if arg == 90:
                (wx, wy) = (wy, -wx)
            elif arg == 180:
                (wx, wy) = (-wx, -wy)
            elif arg == 270:
                (wx, wy) = (-wy, wx)
            else:
                assert False
        elif cmd == 'F':
            x += wx * arg
            y += wy * arg
        else:
            assert False
    return abs(x) + abs(y)



if len(sys.argv) < 2:
    print("Usage: %s FILE" % sys.argv[0], file=sys.stderr)
    sys.exit(1)


with open(sys.argv[1]) as inp:
    instructions = load(inp)


print(solve(instructions))

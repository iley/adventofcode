#!/usr/bin/env python3
import sys


def seat(s):
    rowstr = s[0:7]
    colstr = s[7:10]

    rowstr = rowstr.replace('F', '0')
    rowstr = rowstr.replace('B', '1')
    row = int('0b' + rowstr, 2)

    colstr = colstr.replace('L', '0')
    colstr = colstr.replace('R', '1')
    col = int('0b' + colstr, 2)

    return row, col


def seat_id(row, col):
    return row * 8 + col


all_ids = set()


for line in sys.stdin:
    row, col = seat(line)
    id = seat_id(row, col)
    all_ids.add(id)


for id in range(min(all_ids), max(all_ids)):
    if id not in all_ids:
        print(id)

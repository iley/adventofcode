#!/usr/bin/env python3
import string
import re
from dataclasses import dataclass


@dataclass
class Problem:
    numbers: list[int]
    operation: str


def is_number(s: str) -> bool:
    return all(ch in string.digits for ch in s)


def is_separator(s: str) -> bool:
    return re.match(r"^\s*$", s) is not None


def read_input(path: str) -> list[Problem]:
    matrix = []
    with open(path) as inp:
        for line in inp:
            line = line.rstrip()
            matrix.append(line)

    width = max(len(row) for row in matrix)
    height = len(matrix)

    transposed: list[list[str]] = []

    for col in reversed(range(width)):
        transposed.append([])
        for row in range(height):
            try:
                val = matrix[row][col]
            except IndexError:
                val = ' '
            transposed[-1].append(val)

    lines = [''.join(line) for line in transposed] + [''] # add a separator at the end
    print(lines)

    problems = []
    p = Problem(numbers=[], operation='?')
    for line in lines:
        if is_separator(line):
            problems.append(p)
            p = Problem(numbers=[], operation='?')
            continue

        if '+' in line:
            p.operation = '+'
        if '*' in line:
            p.operation = '*'

        digits = ''.join(ch for ch in line if ch in string.digits)
        number = int(digits)
        p.numbers.append(number)

    return problems


def solve(p: Problem) -> int:
    if p.operation == "+":
        return sum(p.numbers)
    # operation == "*"
    res = 1
    for n in p.numbers:
        res *= n
    return res


def main():
    # input_path = "sample.txt" # "input.txt"
    input_path = "input.txt"
    problems = read_input(input_path)
    # print(problems)
    total = sum(solve(p) for p in problems)
    print(total)


if __name__ == '__main__':
    main()

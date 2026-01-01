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


def read_input(path: str) -> list[Problem]:
    number_rows = []
    operations = []

    with open(path) as inp:
        for line in inp:
            line = line.rstrip()
            tokens = re.split(r"\s+", line)
            tokens = [t for t in tokens if t]
            if tokens and is_number(tokens[0]):
                number_rows.append([int(t) for t in tokens])
            elif tokens:
                operations = tokens

    problems = [Problem(numbers=[], operation = op) for op in operations]
    for i in range(len(problems)):
        for row in number_rows:
            problems[i].numbers.append(row[i])

    return problems


def solve(p: Problem) -> int:
    if p.operation == "+":
        return sum(p.numbers)
    # operation == "*"
    res = 1
    for n in p.numbers:
        res *= n
    return res


def part1(problems: list[Problem]) -> int:
    return sum(solve(p) for p in problems)


def main():
    problems = read_input("input.txt")
    print(f"part 1: {part1(problems)}")


main()

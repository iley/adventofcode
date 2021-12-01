#!/usr/bin/env python3
import sys

FLOOR = '.'
EMPTY = 'L'
OCCUPIED = '#'


def rows(plan):
    return len(plan)


def cols(plan):
    return len(plan[0])


def copy(plan):
    new_plan = []
    for row in plan:
        new_row = []
        for cell in row:
            new_row.append(cell)
        new_plan.append(new_row)
    return new_plan


def display(plan):
    for row in plan:
        for ch in row:
            print(ch, end='')
        print()


def equal(plan1, plan2):
    for row in range(rows(plan1)):
        for col in range(cols(plan1)):
            if plan1[row][col] != plan2[row][col]:
                return False
    return True


def neighbours(plan, row, col):
    def get(r, c):
        if r < 0 or r >= rows(plan):
            return FLOOR
        if c < 0 or c >= cols(plan):
            return FLOOR
        return plan[r][c]

    s = 0
    for dr, dc in ((-1, -1), (-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1), (0, -1)):
        if get(row+dr, col+dc) == OCCUPIED:
            s += 1
    return s


def step(plan):
    new_plan = copy(plan)
    for row in range(rows(plan)):
        for col in range(cols(plan)):
            if plan[row][col] == FLOOR:
                continue
            if plan[row][col] == EMPTY:
                if neighbours(plan, row, col) == 0:
                    new_plan[row][col] = OCCUPIED
            if plan[row][col] == OCCUPIED:
                if neighbours(plan, row, col) >= 4:
                    new_plan[row][col] = EMPTY
    return new_plan

plan = []

with open(sys.argv[1]) as inp:
    for line in inp:
        row = []
        for ch in line:
            if ch in [FLOOR, EMPTY, OCCUPIED]:
                row.append(ch)
        if len(row) > 0:
            plan.append(row)


while True:
    # print(" ------------------------------------ ")
    # display(plan)

    # print(" ------------------------------------ ")
    # occ_grid = copy(plan)
    # for row in range(rows(occ_grid)):
        # for col in range(cols(occ_grid)):
            # occ_grid[row][col] = neighbours(plan, row, col)
    # display(occ_grid)

    old_plan = copy(plan)
    plan = step(plan)
    if equal(old_plan, plan):
        break

s = 0
for row in plan:
    for ch in row:
        if ch == OCCUPIED:
            s += 1

print(s)

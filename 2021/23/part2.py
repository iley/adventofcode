#!/usr/bin/env python3
import sys

INF = 999999999

matrix = [
    [ 0,  0,  0,  0,  0,  0,  0,  3,  4,  5,  6,  5,  6,  7,  8,  7,  8,  9, 10,  9, 10, 11, 12],
    [ 0,  0,  0,  0,  0,  0,  0,  2,  3,  4,  5,  4,  5,  6,  7,  6,  7,  8,  9,  8,  9, 10, 11],
    [ 0,  0,  0,  0,  0,  0,  0,  2,  3,  4,  5,  2,  3,  4,  5,  4,  5,  6,  7,  6,  7,  8,  9],
    [ 0,  0,  0,  0,  0,  0,  0,  4,  5,  6,  7,  2,  3,  4,  5,  2,  3,  4,  5,  4,  5,  6,  7],
    [ 0,  0,  0,  0,  0,  0,  0,  6,  7,  8,  9,  4,  5,  6,  7,  2,  3,  4,  5,  2,  3,  4,  5],
    [ 0,  0,  0,  0,  0,  0,  0,  8,  9, 10, 11,  6,  7,  8,  9,  4,  5,  6,  7,  2,  3,  4,  5],
    [ 0,  0,  0,  0,  0,  0,  0,  9, 10, 11, 12,  7,  8,  9, 10,  5,  6,  7,  8,  3,  4,  5,  6],
    [ 3,  2,  2,  4,  6,  8,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
    [ 4,  3,  3,  5,  7,  9, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
    [ 5,  4,  4,  6,  8, 10, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
    [ 6,  5,  5,  7,  9, 11, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
    [ 5,  4,  2,  2,  4,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
    [ 6,  5,  3,  3,  5,  7,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
    [ 7,  6,  4,  4,  6,  8,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
    [ 8,  7,  5,  5,  7,  9, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
    [ 7,  6,  4,  2,  2,  4,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
    [ 8,  7,  5,  3,  3,  5,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
    [ 9,  8,  6,  4,  4,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
    [10,  9,  7,  5,  5,  7,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
    [ 9,  8,  6,  4,  2,  2,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
    [10,  9,  7,  5,  3,  3,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
    [11, 10,  8,  6,  4,  4,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
    [12, 11,  9,  7,  5,  5,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
]

for i in range(23):
    for j in range(23):
        assert matrix[i][j] == matrix[j][i]

obstacles = {
    (0, 7): (1,),
    (0, 8): (1, 7),
    (0, 9): (1, 7, 8),
    (0, 10): (1, 7, 8, 9),
    (0, 11): (1, 2),
    (0, 12): (1, 2, 11),
    (0, 13): (1, 2, 11, 12),
    (0, 14): (1, 2, 11, 12, 13),
    (0, 15): (1, 2, 3),
    (0, 16): (1, 2, 3, 15),
    (0, 17): (1, 2, 3, 15, 16),
    (0, 18): (1, 2, 3, 15, 16, 17),
    (0, 19): (1, 2, 3, 4),
    (0, 20): (1, 2, 3, 4, 19),
    (0, 21): (1, 2, 3, 4, 19, 20),
    (0, 22): (1, 2, 3, 4, 19, 20, 21),

    (1, 7): (),
    (1, 8): (7,),
    (1, 9): (7, 8),
    (1, 10): (7, 8, 9),
    (1, 11): (2,),
    (1, 12): (2, 11),
    (1, 13): (2, 11, 12),
    (1, 14): (2, 11, 12, 13),
    (1, 15): (2, 3),
    (1, 16): (2, 3, 15),
    (1, 17): (2, 3, 15, 16),
    (1, 18): (2, 3, 15, 16, 17),
    (1, 19): (2, 3, 4),
    (1, 20): (2, 3, 4, 19),
    (1, 21): (2, 3, 4, 19, 20),
    (1, 22): (2, 3, 4, 19, 20, 21),

    (2, 7): (),
    (2, 8): (7,),
    (2, 9): (7, 8),
    (2, 10): (7, 8, 9),
    (2, 11): (),
    (2, 12): (11,),
    (2, 13): (11, 12),
    (2, 14): (11, 12, 13),
    (2, 15): (3,),
    (2, 16): (3, 15),
    (2, 17): (3, 15, 16),
    (2, 18): (3, 15, 16, 17),
    (2, 19): (3, 4),
    (2, 20): (3, 4, 19),
    (2, 21): (3, 4, 19, 20),
    (2, 22): (3, 4, 19, 20, 21),

    (3, 7): (2,),
    (3, 8): (2,7),
    (3, 9): (2,7, 8),
    (3, 10): (2,7, 8, 9),
    (3, 11): (),
    (3, 12): (11,),
    (3, 13): (11, 12),
    (3, 14): (11, 12, 13),
    (3, 15): (),
    (3, 16): (15,),
    (3, 17): (15, 16),
    (3, 18): (15, 16, 17),
    (3, 19): (4,),
    (3, 20): (4, 19),
    (3, 21): (4, 19, 20),
    (3, 22): (4, 19, 20, 21),

    (4, 7): (2, 3),
    (4, 8): (2, 3, 7),
    (4, 9): (2, 3, 7, 8),
    (4, 10): (2, 3, 7, 8, 9),
    (4, 11): (3,),
    (4, 12): (3, 11),
    (4, 13): (3, 11, 12),
    (4, 14): (3, 11, 12, 13),
    (4, 15): (),
    (4, 16): (15,),
    (4, 17): (15, 16),
    (4, 18): (15, 16, 17),
    (4, 19): (),
    (4, 20): (19,),
    (4, 21): (19, 20),
    (4, 22): (19, 20, 21),

    (5, 7): (2, 3, 4),
    (5, 8): (2, 3, 4, 7),
    (5, 9): (2, 3, 4, 7, 8),
    (5, 10): (2, 3, 4, 7, 8, 9),
    (5, 11): (3, 4),
    (5, 12): (3, 4, 11),
    (5, 13): (3, 4, 11, 12),
    (5, 14): (3, 4, 11, 12, 13),
    (5, 15): (4,),
    (5, 16): (4, 15),
    (5, 17): (4, 15, 16),
    (5, 18): (4, 15, 16, 17),
    (5, 19): (),
    (5, 20): (19,),
    (5, 21): (19, 20),
    (5, 22): (19, 20, 21),

    (6, 7): (5, 2, 3, 4),
    (6, 8): (5, 2, 3, 4, 7),
    (6, 9): (5, 2, 3, 4, 7, 8),
    (6, 10): (5, 2, 3, 4, 7, 8, 9),
    (6, 11): (5, 3, 4),
    (6, 12): (5, 3, 4, 11),
    (6, 13): (5, 3, 4, 11, 12),
    (6, 14): (5, 3, 4, 11, 12, 13),
    (6, 15): (5, 4,),
    (6, 16): (5, 4, 15),
    (6, 17): (5, 4, 15, 16),
    (6, 18): (5, 4, 15, 16, 17),
    (6, 19): (5,),
    (6, 20): (5, 19,),
    (6, 21): (5, 19, 20),
    (6, 22): (5, 19, 20, 21),
}

for x, y in list(obstacles.keys()):
    obstacles[(y, x)] = obstacles[(x, y)]

amphcost = { "A": 1, "B": 10, "C": 100, "D": 1000 }


target = ".......AAAABBBBCCCCDDDD"

def setchar(string, i, char):
    return string[:i] + char + string[i+1:]

def there_are_obstacles(state, startpos, endpos):
    if (startpos, endpos) in obstacles:
        for obst in obstacles[(startpos, endpos)]:
            if state[obst] != ".":
                return True
    return False

def room_occupied(state, amph):
    for i in range(len(target)):
        if target[i] == amph and state[i] != amph and state[i] != ".":
            return True
    return False

def is_final_pos(state, amph, pos):
    if amph != target[pos]:
        return False
    if pos < 11:
        return all(state[p] == amph for p in range(pos+1, 11))
    elif pos < 15:
        return all(state[p] == amph for p in range(pos+1, 15))
    elif pos < 19:
        return all(state[p] == amph for p in range(pos+1, 19))
    else:
        return all(state[p] == amph for p in range(pos+1, 23))

def print_state(state):
    print("#############")
    print("#" + state[:2] + "." + state[2:3] + "." + state[3:4] + "." + state[4:5] + "." + state[5:7] + "#")
    print("###" + "#".join((state[7], state[11], state[15], state[19])) + "###")
    print("  #" + "#".join((state[8], state[12], state[16], state[20])) + "#  ")
    print("  #" + "#".join((state[9], state[13], state[17], state[21])) + "#  ")
    print("  #" + "#".join((state[10], state[14], state[18], state[22])) + "#  ")
    print("  #########")
    print()

cache = {}

def search(state, depth=0):
    if state in cache:
        return cache[state]

    # print("%d: %s" % (depth, state))
    # print_state(state)

    if state == target:
        return 0, []

    mincost = INF
    minpath = []
    for pos in range(len(state)):
        amph = state[pos]
        if state[pos] == "." or is_final_pos(state, amph, pos):
            continue
        for newpos in range(len(state)):
            if matrix[pos][newpos] == 0:
                continue
            if state[newpos] != ".":
                continue
            if newpos >= 7 and not is_final_pos(state, amph, newpos):
                continue
            if there_are_obstacles(state, pos, newpos):
                continue

            newstate = setchar(setchar(state, newpos, amph), pos, ".")
            cost_left, path_left = search(newstate, depth+1)
            cost = amphcost[amph] * matrix[pos][newpos] + cost_left
            path = [state] + path_left

            if cost < mincost:
                mincost = cost
                minpath = path

    cache[state] = (mincost, minpath)
    return mincost, minpath


start = "DDDCACBCABABDACB" # my input
# start = "BDDACCBDBBACDACA" # sample
state = "......." + start
sys.setrecursionlimit(2000)
cost, path = search(state)
for i, state in enumerate(path):
    print(i)
    print_state(state)
print(cost)

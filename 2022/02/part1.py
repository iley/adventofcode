score = 0

shape_score = {
    'X': 1,
    'Y': 2,
    'Z': 3,
}

winner_score = {
    ('A', 'X'): 3,
    ('B', 'Y'): 3,
    ('C', 'Z'): 3,
    ('A', 'Y'): 6,
    ('B', 'Z'): 6,
    ('C', 'X'): 6,
    ('A', 'Z'): 0,
    ('B', 'X'): 0,
    ('C', 'Y'): 0,
}

with open("input.txt") as inp:
    for line in inp:
        they = line[0]
        us = line[2]
        score += shape_score[us] + winner_score[(they, us)]

print(score)

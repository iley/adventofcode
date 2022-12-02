score = 0

shape_score = {
    'A': 1,
    'B': 2,
    'C': 3,
}

winner_score = {
    ('A', 'A'): 3,
    ('B', 'B'): 3,
    ('C', 'C'): 3,
    ('A', 'B'): 6,
    ('B', 'C'): 6,
    ('C', 'A'): 6,
    ('A', 'C'): 0,
    ('B', 'A'): 0,
    ('C', 'B'): 0,
}

our_choice = {
    ('A', 'X'): 'C',
    ('B', 'Y'): 'B',
    ('C', 'Z'): 'A',
    ('A', 'Y'): 'A',
    ('B', 'Z'): 'C',
    ('C', 'X'): 'B',
    ('A', 'Z'): 'B',
    ('B', 'X'): 'A',
    ('C', 'Y'): 'C',
}

with open("input.txt") as inp:
    for line in inp:
        they = line[0]
        outcome = line[2]
        us = our_choice[(they, outcome)]
        score += shape_score[us] + winner_score[(they, us)]

print(score)

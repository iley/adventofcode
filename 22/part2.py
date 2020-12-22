#!/usr/bin/env python3
import time
from functools import lru_cache

SAMPLE_DECK1 = ( 9, 2, 6, 3, 1 )
SAMPLE_DECK2 = ( 5, 8, 4, 7, 10 )

RECURSIVE_DECK1 = ( 43, 19 )
RECURSIVE_DECK2 = ( 2, 29, 14 )

INPUT_DECK1 = (26, 14, 6, 34, 37, 9, 17, 39, 4, 5, 1, 8, 49, 16, 18, 47, 20, 31, 23, 19, 35, 41, 28, 15, 44)
INPUT_DECK2 = (7, 2, 10, 25, 29, 46, 40, 45, 11, 50, 42, 24, 38, 13, 36, 22, 33, 3, 43, 21, 48, 30, 32, 12, 27)

# deck1, deck2 = SAMPLE_DECK1, SAMPLE_DECK2
# deck1, deck2 = RECURSIVE_DECK1, RECURSIVE_DECK2
deck1, deck2 = INPUT_DECK1, INPUT_DECK2

previous_games = set()

def game(deck1, deck2):
    previous_decks = set()

    while True:
        # print('%s %s' % (deck1, deck2))

        if (deck1, deck2) in previous_decks:
            return 0, deck1

        if len(deck1) == 0:
            return 1, deck2
        if len(deck2) == 0:
            return 0, deck1

        previous_decks.add((deck1, deck2))

        p1 = deck1[0]
        deck1 = deck1[1:]
        p2 = deck2[0]
        deck2 = deck2[1:]

        if len(deck1) >= p1 and len(deck2) >= p2:
            winner, _ = game(deck1[:p1], deck2[:p2])
        elif p1 > p2:
            winner = 0
        else:
            winner = 1

        if winner == 0:
            deck1 = deck1 + (p1, p2)
        else:
            deck2 = deck2 + (p2, p1)

winner, winning_deck = game(deck1, deck2)

print('player %d won' % (winner+1))
print('winning deck: %s' % (deck2,))

score = 0
for i, card in enumerate(reversed(winning_deck)):
    score += (i+1) * card

print(score)

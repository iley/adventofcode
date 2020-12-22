#!/usr/bin/env python3

SAMPLE_DECK1 = [ 9, 2, 6, 3, 1 ]
SAMPLE_DECK2 = [ 5, 8, 4, 7, 10 ]

INPUT_DECK1 = [ 26, 14, 6, 34, 37, 9, 17, 39, 4, 5, 1, 8, 49, 16, 18, 47, 20, 31, 23, 19, 35, 41, 28, 15, 44 ]
INPUT_DECK2 = [ 7, 2, 10, 25, 29, 46, 40, 45, 11, 50, 42, 24, 38, 13, 36, 22, 33, 3, 43, 21, 48, 30, 32, 12, 27 ]

# deck1, deck2 = SAMPLE_DECK1, SAMPLE_DECK2
deck1, deck2 = INPUT_DECK1, INPUT_DECK2

while len(deck1) > 0 and len(deck2) > 0:
    #print('P1: %s' % deck1)
    #print('P2: %s' % deck2)
    p1 = deck1[0]
    deck1 = deck1[1:]
    p2 = deck2[0]
    deck2 = deck2[1:]

    if p1 > p2:
        deck1.append(p1)
        deck1.append(p2)
    else:
        deck2.append(p2)
        deck2.append(p1)


if len(deck1) > 0:
    winning_deck = deck1
else:
    winning_deck = deck2

score = 0
for i, card in enumerate(reversed(winning_deck)):
    score += (i+1) * card

print(score)

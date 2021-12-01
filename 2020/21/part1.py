#!/usr/bin/env python3
import re
import sys
from collections import defaultdict


line_re = re.compile(r'(.+) \(contains (.+)\)')


def load(input_file):
    data = []

    for line in input_file:
        m = line_re.match(line)
        if m is None:
            continue
        left, right = m.group(1), m.group(2)
        ingridients = set( word.strip() for word in left.split(' ') if word.strip() != '' )
        allergens = set( word.strip() for word in right.split(', ') if word.strip() != '' )

        data.append((ingridients, allergens))

    return data


data = load(sys.stdin)

ing_set_lists = defaultdict(list) # list of sets per allergen
for ingridients, allergens in data:
    for allergen in allergens:
        ing_set_lists[allergen].append(set(ingridients))

# print('ingridient sets')
# for k, v in ing_set_lists.items():
    # print("%s -> %s" % (k, v))

possible_ingridients = {} # set per allergen
for allergen, ing_sets in ing_set_lists.items():
    for ing_set in ing_sets:
        if allergen not in possible_ingridients:
            possible_ingridients[allergen] = ing_set
        else:
            possible_ingridients[allergen] = possible_ingridients[allergen].intersection(ing_set)

# print('possible ingridients')
# for k, v in possible_ingridients.items():
    # print("%s -> %s" % (k, v))

candidate_ingridients = set()
for ing_set in possible_ingridients.values():
    candidate_ingridients = candidate_ingridients.union(ing_set)

print('ingridients which might have allergens: %s' % ', '.join(candidate_ingridients))

occurences = 0
for ingridients, _ in data:
    for ing in ingridients:
        if ing not in candidate_ingridients:
            occurences += 1

print(occurences)

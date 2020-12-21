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
        ingridients = [ word.strip() for word in left.split(' ') if word.strip() != '' ]
        allergens = [ word.strip() for word in right.split(', ') if word.strip() != '' ]

        data.append((ingridients, allergens))

    return data


data = load(sys.stdin)
# for ing, allerg in data:
    # print("%s | %s" % (','.join(ing), ','.join(allerg)))

allergen_sets = {}

for ingridients, allergens in data:
    for ing in ingridients:
        if ing not in allergen_sets:
            allergen_sets[ing] = []
        allergen_sets[ing].append(set(allergens))

print(allergen_sets)


allergen_free_ingridients = []


for ingridient, sets in allergen_sets.items():
    possible_allergens = set()
    for s in sets:
        possible_allergens = possible_allergens.intersection(s)
    if len(possible_allergens) == 0:
        allergen_free_ingridients.append(ingridient)
    print('possible allergens for %s are %s' % (ingridient, ', '.join(possible_allergens)))


print('allergen-free ingridients are: ' + ', '. join(allergen_free_ingridients))

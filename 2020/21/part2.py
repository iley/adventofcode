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

possible_ingridients = {} # set per allergen
for allergen, ing_sets in ing_set_lists.items():
    for ing_set in ing_sets:
        if allergen not in possible_ingridients:
            possible_ingridients[allergen] = ing_set
        else:
            possible_ingridients[allergen] = possible_ingridients[allergen].intersection(ing_set)

ingridient_to_allergen = {}

while True:
    for allergen, ingridients in possible_ingridients.items():
        if len(ingridients) == 1:
            progress = True
            ingridient = list(ingridients)[0]
            ingridient_to_allergen[ingridient] = allergen
            break
    else:
        break

    new_possible_ingridients = {}
    for allergen, ingridients in possible_ingridients.items():
        new_ingridients = set( ing for ing in ingridients if ing != ingridient )
        if len(new_ingridients) > 0:
            new_possible_ingridients[allergen] = new_ingridients

    possible_ingridients = new_possible_ingridients


assert len(possible_ingridients) == 0

for ingridient, allergen in ingridient_to_allergen.items():
    print('%s contains %s' % (ingridient, allergen))

canonical_list = sorted(ingridient_to_allergen.keys(), key=lambda ing: ingridient_to_allergen[ing])
print(','.join(canonical_list))

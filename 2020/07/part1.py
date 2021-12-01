#!/usr/bin/env python3
import re
import sys
from collections import defaultdict


outer_re = re.compile("^(\w+ \w+) bags contain (.+)\.")
inner_re = re.compile("(\d+) (\w+ \w+) bags?")


def read(input_file):
    graph = defaultdict(list)
    for line in input_file:
        line = line.rstrip()
        m = outer_re.match(line)
        if m is None:
            continue
        outer_bag, rest = m.group(1), m.group(2)
        parts = [s.strip() for s in rest.split(",")]
        for part in parts:
            if part == "no other bags":
                continue
            m = inner_re.match(part)
            assert m is not None
            n, inner_bag = m.group(1), m.group(2)
            graph[inner_bag].append(outer_bag)
            # graph[outer_bag].append(inner_bag)
            # print("%s can be in %s" % (inner_bag, outer_bag))
    return graph


def possible_outer_bags(graph, inner_bag, result=None):
    if result is None:
        result = frozenset()
    for outer in graph.get(inner_bag, []):
        if outer in result:
            continue
        result = result | frozenset([outer])
        result = result | possible_outer_bags(graph, outer, result)
    return result


graph = read(sys.stdin)
#for k, v in graph.items():
    #print("%s -> %s" % (k, ', '.join(v)))

bags = possible_outer_bags(graph, "shiny gold")
print(len(bags))

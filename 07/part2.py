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
            graph[outer_bag].append((int(n), inner_bag))
    return graph


def inner_bags_count(graph, bag):
    total = 0
    for n, inner_bag in graph[bag]:
        total += n * (inner_bags_count(graph, inner_bag) + 1)
    return total


graph = read(sys.stdin)
#for k, v in graph.items():
    #print("%s -> %s" % (k, v))


print(inner_bags_count(graph, "shiny gold"))

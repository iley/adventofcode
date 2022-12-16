import re
import functools
import itertools

inp_re = re.compile(r'Valve ([A-Z]{2}) has flow rate=(\d+); (?:tunnels lead to valves|tunnel leads to valve) ([A-Z ,]+)')

valves = {}
with open("input.txt") as inp:
    for line in inp:
        line = line.strip()
        m = inp_re.match(line)
        assert m is not None
        valve = m.group(1)
        rate = int(m.group(2))
        links = m.group(3).split(", ")
        valves[valve] = (rate, links)


@functools.cache
def traverse(my_valve, elephant_valve, open_valves, time_left):
    if time_left == 0:
        return 0

    possible_moves = []
    possible_elephant_moves = []

    my_valve_rate, my_links = valves[my_valve]
    elephant_valve_rate, elephant_links = valves[elephant_valve]

    if my_valve not in open_valves and my_valve_rate > 0:
        possible_moves.append((True, my_valve))

    if elephant_valve not in open_valves and elephant_valve_rate > 0:
        possible_elephant_moves.append((True, elephant_valve))

    for other_valve in my_links:
        possible_moves.append((False, other_valve))

    for other_valve in elephant_links:
        possible_elephant_moves.append((False, other_valve))

    totals = []
    for my_move, elephant_move in itertools.product(possible_moves, possible_elephant_moves):
        open_valve, next_valve = my_move
        elephant_open_valve, elephant_next_valve = elephant_move
        total = 0
        next_open_valves = open_valves
        if open_valve:
            total += my_valve_rate * (time_left - 1)
            next_open_valves += (my_valve,)
        if elephant_open_valve and (not open_valve or my_valve != elephant_valve):
            total += elephant_valve_rate * (time_left - 1)
            next_open_valves += (elephant_valve,)
        total += traverse(next_valve, elephant_next_valve, next_open_valves, time_left-1)
        totals.append(total)

    if len(totals) == 0:
        return 0
    return max(totals)


print(traverse('AA', 'AA', (), 26))

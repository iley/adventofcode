import re
import functools

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
def traverse(valve, open_valves, time_left):
    if time_left == 0:
        return 0
    totals = []
    rate, links = valves[valve]
    if valve not in open_valves and rate > 0:
        totals.append(rate * (time_left - 1) +
                      traverse(valve, open_valves + (valve,), time_left-1))
    for other_valve in links:
        totals.append(traverse(other_valve, open_valves, time_left-1))
    if totals == []:
        return 0
    return max(totals)


print(traverse('AA', (), 30))

import re
import sys
from collections import namedtuple

input_re = re.compile(r'Blueprint (\d+): Each ore robot costs (\d+) ore. Each clay robot costs (\d+) ore. Each obsidian robot costs (\d+) ore and (\d+) clay. Each geode robot costs (\d+) ore and (\d+) obsidian.')


Blueprint = namedtuple(
    'Blueprint',
    ['ore_robot_ore',
     'clay_robot_ore',
     'obsidian_robot_ore',
     'obsidian_robot_clay',
     'geode_robot_ore',
     'geode_robot_obsidian'])


blueprints = []
with open(sys.argv[1]) as inp:
    for line in inp:
        match = input_re.match(line)
        assert match is not None
        blueprint_no = int(match.group(1))
        blueprints.append(
            Blueprint(
                ore_robot_ore=int(match.group(2)),
                clay_robot_ore=int(match.group(3)),
                obsidian_robot_ore=int(match.group(4)),
                obsidian_robot_clay=int(match.group(5)),
                geode_robot_ore=int(match.group(6)),
                geode_robot_obsidian=int(match.group(7))))


print(blueprints)

import re
import sys
import functools
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


State = namedtuple(
    'State',
    ['time_left', 'ore', 'clay', 'obsidian', 'geodes',
     'ore_robots', 'clay_robots', 'obsidian_robots', 'geode_robots'])


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


class Solver:
    def __init__(self, blueprint):
        self.blueprint = blueprint
        self.cache = {}

    def find_max_score(self, start_state):
        cached_result = self.cache.get(start_state)
        if cached_result is not None:
            return cached_result

        blueprint = self.blueprint

        # print(start_state)

        if start_state.time_left == 0:
            return start_state.geodes

        next_states = []
        # next state if no robot is built
        end_state = start_state._replace(
            time_left=start_state.time_left - 1,
            ore=start_state.ore + start_state.ore_robots,
            clay=start_state.clay + start_state.clay_robots,
            obsidian=start_state.obsidian + start_state.obsidian_robots,
            geodes=start_state.geodes + start_state.geode_robots,
        )

        if start_state.ore >= blueprint.geode_robot_ore and start_state.obsidian >= blueprint.geode_robot_obsidian:
            next_state = end_state._replace(
                ore=end_state.ore - blueprint.geode_robot_ore,
                obsidian=end_state.obsidian - blueprint.geode_robot_obsidian,
                geode_robots=end_state.geode_robots + 1)
            next_states.append(next_state)
        else: 
            if start_state.ore >= blueprint.obsidian_robot_ore and start_state.clay >= blueprint.obsidian_robot_clay:
                next_state = end_state._replace(
                    ore=end_state.ore - blueprint.obsidian_robot_ore,
                    clay=end_state.clay - blueprint.obsidian_robot_clay,
                    obsidian_robots=end_state.obsidian_robots + 1)
                next_states.append(next_state)
            if start_state.ore >= blueprint.ore_robot_ore:
                next_state = end_state._replace(
                    ore=end_state.ore - blueprint.ore_robot_ore,
                    ore_robots=end_state.ore_robots + 1)
                next_states.append(next_state)
            if start_state.ore >= blueprint.clay_robot_ore:
                next_state = end_state._replace(
                    ore=end_state.ore - blueprint.clay_robot_ore,
                    clay_robots=end_state.clay_robots + 1)
                next_states.append(next_state)
            next_states.append(end_state)

        result = max(self.find_max_score(next_state) for next_state in next_states)
        self.cache[start_state] = result
        return result


initial_state = State(
    time_left=24,
    ore=0,
    clay=0,
    obsidian=0,
    geodes=0,
    ore_robots=1,
    clay_robots=0,
    obsidian_robots=0,
    geode_robots=0)

quality_level_sum = 0
for i, blueprint in enumerate(blueprints):
    solver = Solver(blueprint)
    score = solver.find_max_score(initial_state)
    blueprint_no = i + 1
    quality_level = score * blueprint_no
    print("blueprint %d: max. geodes = %d; quality level = %d" % (blueprint_no, score, quality_level))
    quality_level_sum += quality_level

print(quality_level_sum)

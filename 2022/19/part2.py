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
        # only use first 3
        if len(blueprints) == 3:
            break
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
        idle_state = start_state._replace(
            time_left=start_state.time_left - 1,
            ore=start_state.ore + start_state.ore_robots,
            clay=start_state.clay + start_state.clay_robots,
            obsidian=start_state.obsidian + start_state.obsidian_robots,
            geodes=start_state.geodes + start_state.geode_robots,
        )

        if start_state.time_left == 1:
            # on last turn there's no point in building any robots
            next_states.append(idle_state)
        else:
            if start_state.ore >= blueprint.geode_robot_ore and start_state.obsidian >= blueprint.geode_robot_obsidian:
                # always build obsidian robots if we can
                next_states.append(idle_state._replace(
                    ore=idle_state.ore - blueprint.geode_robot_ore,
                    obsidian=idle_state.obsidian - blueprint.geode_robot_obsidian,
                    geode_robots=idle_state.geode_robots + 1))
            else:
                if start_state.ore >= blueprint.obsidian_robot_ore and start_state.clay >= blueprint.obsidian_robot_clay:
                    next_states.append(idle_state._replace(
                        ore=idle_state.ore - blueprint.obsidian_robot_ore,
                        clay=idle_state.clay - blueprint.obsidian_robot_clay,
                        obsidian_robots=idle_state.obsidian_robots + 1))
                if start_state.ore >= blueprint.clay_robot_ore:
                    next_states.append(idle_state._replace(
                        ore=idle_state.ore - blueprint.clay_robot_ore,
                        clay_robots=idle_state.clay_robots + 1))
                # only build ore robots if there's enough time for it to earn back the ore spent
                if start_state.ore >= blueprint.ore_robot_ore and start_state.time_left > blueprint.ore_robot_ore + 1:
                    next_states.append(idle_state._replace(
                        ore=idle_state.ore - blueprint.ore_robot_ore,
                        ore_robots=idle_state.ore_robots + 1))

                next_states.append(idle_state)

        result = max(self.find_max_score(next_state) for next_state in next_states)
        self.cache[start_state] = result
        return result


initial_state = State(
    time_left=32,
    ore=0,
    clay=0,
    obsidian=0,
    geodes=0,
    ore_robots=1,
    clay_robots=0,
    obsidian_robots=0,
    geode_robots=0)

answer = 1
for i, blueprint in enumerate(blueprints):
    solver = Solver(blueprint)
    score = solver.find_max_score(initial_state)
    blueprint_no = i + 1
    answer *= score
    print("blueprint %d: max. geodes = %d; answer = %d" % (blueprint_no, score, answer))


print(answer)

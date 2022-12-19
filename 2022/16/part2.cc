#include <cassert>
#include <climits>
#include <compare>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <vector>

// "infinity" value for graph distances
constexpr int DIST_INF = 1000;

typedef std::tuple<std::string, int> Neighbour;

struct Valve {
  std::string name;
  int rate;
  std::vector<Neighbour> neighbours;

  Valve(std::string name, int rate, std::vector<Neighbour> neighbours)
    : name(name), rate(rate), neighbours(neighbours) {}

  Valve(const Valve& other) = default;
  Valve& operator=(const Valve& other) = default;
};

struct PlayerState {
  std::string location;
  int steps_left;
  int opened_valve;

  std::strong_ordering operator<=>(const PlayerState& other) const = default;
};

struct SearchState {
  int time_left;
  std::set<std::string> open_valves;
  PlayerState human;
  PlayerState elephant;

  std::strong_ordering operator<=>(SearchState const& other) const = default;
};

class Optimizer {
public:
  explicit Optimizer(const std::vector<Valve> valves)
    : valves_(valves) {
    for (const auto& valve: valves) {
      valves_map_.emplace(std::make_pair(valve.name, valve));
    }
  }

  int solve(const SearchState& state);

private:
  const std::vector<Valve> valves_;
  std::unordered_map<std::string, Valve> valves_map_;
  std::map<SearchState, int> past_results_;

  std::vector<PlayerState> next_player_states(const PlayerState& player_state, const std::set<std::string>& open_valves);
};

int Optimizer::solve(const SearchState& state) {
  if (state.time_left == 0) {
    return 0;
  }

  auto pos = past_results_.find(state);
  if (pos != past_results_.end()) {
    return pos->second;
  }

  const auto next_human_states = next_player_states(state.human, state.open_valves);
  const auto next_elephant_states = next_player_states(state.elephant, state.open_valves);

  int max_score = 0;
  for (const auto& next_human_state : next_human_states) {
    for (const auto& next_elephant_state : next_elephant_states) {
      if (next_human_state.opened_valve &&
          next_elephant_state.opened_valve &&
          next_human_state.location == next_elephant_state.location) {
        // Cannot both open the same valve.
        continue;
      }

      std::set<std::string> open_valves = state.open_valves;
      int score = 0;

      if (next_human_state.opened_valve) {
        score += valves_map_.at(next_human_state.location).rate * (state.time_left - 1);
        open_valves.insert(next_human_state.location);
      }

      if (next_elephant_state.opened_valve) {
        score += valves_map_.at(next_elephant_state.location).rate * (state.time_left - 1);
        open_valves.insert(next_elephant_state.location);
      }

      SearchState next_state = {
        .time_left = state.time_left - 1,
        .open_valves = open_valves,
        .human = next_human_state,
        .elephant = next_elephant_state,
      };

      score += solve(next_state);

      if (score > max_score) {
        max_score = score;
      }
    }
  }

  past_results_.emplace(std::make_pair(state, max_score));
  if (past_results_.size() % 1000000 == 0) {
    std::cout << past_results_.size() << " states explored" << std::endl;
  }
  return max_score;
}

std::vector<PlayerState> Optimizer::next_player_states(const PlayerState& player_state, const std::set<std::string>& open_valves) {
  std::vector<PlayerState> next_states;
  if (player_state.steps_left > 0) {
    next_states.push_back({
      .location = player_state.location,
      .steps_left = player_state.steps_left - 1,
      .opened_valve = false,
    });
  } else {
    const auto valve = valves_map_.at(player_state.location);
    // only open a valve if it's nonzero (excludes AA) and wasn't open before.
    if (valve.rate > 0 && open_valves.find(player_state.location) == open_valves.end()) {
      next_states.push_back({
        .location = player_state.location,
        .steps_left = 0,
        .opened_valve = true,
      });
    }
    for (const auto& neighbour : valve.neighbours) {
      const auto [neighbour_name, distance] = neighbour;
      next_states.push_back({
        .location = neighbour_name,
        .steps_left = distance - 1,
        .opened_valve = false,
      });
    }
  }
  return next_states;
}

std::vector<std::string> split_by_delimeter(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}


std::vector<Neighbour> parse_neighbours(const std::string& str) {
  std::vector<Neighbour> neighbours;
  auto parts = split_by_delimeter(str, ", ");
  for (const auto& part : parts) {
    neighbours.emplace_back(part, 1);
  }
  return neighbours;
}

std::vector<Valve> read_input(std::istream& input) {
  std::regex re("Valve ([A-Z]{2}) has flow rate=(\\d+); (?:tunnels lead to valves|tunnel leads to valve) ([A-Z ,]+)");
  std::vector<Valve> valves;

  std::string line;
  while (std::getline(input, line)) {
    std::smatch match;
    bool got_match = std::regex_search(line, match, re);
    assert(got_match);
    std::string name = match[1];
    int rate = std::atoi(match[2].str().c_str());
    auto neighbours = parse_neighbours(match[3].str());
    valves.emplace_back(name, rate, std::move(neighbours));
  }

  return valves;
}

// returns distances from every valve to every valve
std::unordered_map<std::string, int> floyd(const std::vector<Valve>& valves) {
  std::unordered_map<std::string, int> distances;

  for (const auto& valve : valves) {
    for (const auto& other_valve : valves) {
      distances[valve.name + other_valve.name] = DIST_INF;
    }
  }

  for (const auto& valve : valves) {
    distances[valve.name + valve.name] = 0;
    for (const auto& neighbour : valve.neighbours) {
      const auto& neighbour_name = std::get<0>(neighbour);
      distances[valve.name + neighbour_name] = 1;
    }
  }

  for (const auto& va : valves) {
    for (const auto& vb : valves) {
      for (const auto& vc : valves) {
        int ab = distances[va.name + vb.name];
        int bc = distances[vb.name + vc.name];
        int ca = distances[vc.name + va.name];
        if (ab > bc + ca) {
          distances[va.name + vb.name] = bc + ca;
        }
      }
    }
  }

  return distances;
}

std::vector<Valve> remove_useless_valves(const std::vector<Valve>& valves) {
  std::unordered_map<std::string, int> distances = floyd(valves);

  std::set<std::string> remaining_valve_names { "AA" };
  for (const auto& valve : valves) {
    if (valve.rate > 0) {
      remaining_valve_names.insert(valve.name);
    }
  }

  std::vector<Valve> remaining_valves;
  for (const auto& valve : valves) {
    if (remaining_valve_names.find(valve.name) == remaining_valve_names.end()) {
      continue;
    }
    std::vector<Neighbour> neighbours;
    for (const auto& other_valve_name : remaining_valve_names) {
      int dist = distances[valve.name + other_valve_name];
      if (other_valve_name == valve.name || dist == DIST_INF) {
        continue;
      }
      neighbours.emplace_back(other_valve_name, dist);
    }
    remaining_valves.emplace_back(valve.name, valve.rate, neighbours);
  }
  return remaining_valves;
}

void print_valves(const std::vector<Valve>& valves) {
  for (const auto& valve : valves) {
    std::cout << valve.name << " " << valve.rate << " ";
    for (const auto& neighbour : valve.neighbours) {
      auto [name, distance] = neighbour;
      std::cout << "(" << name << " " << distance << ") ";
    }
    std::cout << std::endl;
  }
}


int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: part2 INPUT" << std::endl;
    return 1;
  }

  std::ifstream input(argv[1]);
  auto valves = read_input(input);
  auto non_zero_valves = remove_useless_valves(valves);

  SearchState initial_state = {
    .time_left = 26,
    .open_valves = {},
    .human = {
      .location = "AA",
      .steps_left = 0,
      .opened_valve = false,
    },
    .elephant = {
      .location = "AA",
      .steps_left = 0,
      .opened_valve = false,
    },
  };

  print_valves(non_zero_valves);
  Optimizer optimizer(non_zero_valves);
  std::cout << optimizer.solve(initial_state) << std::endl;
}

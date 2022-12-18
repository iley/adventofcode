#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <regex>
#include <tuple>
#include <vector>

typedef std::tuple<std::string, int> Neighbour;

struct Valve {
  std::string name;
  int rate;
  std::vector<Neighbour> neighbours;

  Valve(std::string name, int rate, std::vector<Neighbour> neighbours)
    : name(name), rate(rate), neighbours(neighbours) {}
};

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

void print_valves(const std::vector<Valve>& valves) {
  for (const auto& valve : valves) {
    std::cout << valve.name << " " << valve.rate << " ";
    for (const auto& neighbour : valve.neighbours) {
      std::cout << "(" << std::get<0>(neighbour) << " " << std::get<1>(neighbour) << ") ";
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
  print_valves(valves);
}

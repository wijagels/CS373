#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>

struct State {
  State(size_t idx) : State({}, false, false, idx) {}
  State(const std::multimap<char, size_t>& transitions, bool start, bool accept,
        size_t idx)
      : transitions_{transitions}, start_{start}, accept_{accept}, idx_{idx} {}
  void add_transition(const std::pair<char, size_t>& t) {
    transitions_.insert(t);
  }
  std::multimap<char, size_t>
      transitions_;  // Mapping of symbols to destinations
  bool start_;
  bool accept_;
  size_t idx_;
};

void fucking_nfa_function(const std::unordered_map<size_t, State>& shittynfa,
                          std::string shitfromuser) {
  std::set<size_t> accepts, rejects;
  std::queue<std::pair<std::string, State>> q{};
  for (auto it : shittynfa) {
    if (it.second.start_) q.push({shitfromuser, it.second});
  }
  while (!q.empty()) {
    State s = q.front().second;
    std::string str = q.front().first;
    q.pop();
    if (str.size() == 0) {
      if (s.accept_) {
        accepts.insert(s.idx_);
      } else {
        rejects.insert(s.idx_);
      }
    } else {
      char symbol = str.front();
      str = str.substr(1, str.size());
      auto rng = s.transitions_.equal_range(symbol);
      for (auto it = rng.first; it != rng.second; it++) {
        q.push({str, shittynfa.at(it->second)});
      }
    }
  }
  if (!accepts.empty()) {
    std::cout << "accept";
    for (auto e : accepts) {
      std::cout << " " << e;
    }
  } else {
    std::cout << "reject";
    for (auto e : rejects) {
      std::cout << " " << e;
    }
  }
  std::cout << std::endl;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    exit(1);
  }
  char* fuckingfilename = argv[1];
  std::string input{argv[2]};
  std::ifstream file{fuckingfilename};
  if (!file.is_open()) {
    exit(1);
  }
  std::string line;
  std::unordered_map<size_t, State> shittynfa;
  while (std::getline(file, line)) {
    std::stringstream ss{line};
    std::string command;
    ss >> command;
    if (command == "state") {
      size_t fuckingstate;
      std::string isitstartoraccept;
      ss >> fuckingstate;
      ss >> isitstartoraccept;
      bool st = false;
      bool ac = false;
      if (isitstartoraccept == "start") {
        st = true;
        if (!ss.eof()) {
          ss >> isitstartoraccept;
          if (isitstartoraccept == "accept") {
            ac = true;
          }
        }
      } else if (isitstartoraccept == "accept") {
        ac = true;
        if (!ss.eof()) {
          ss >> isitstartoraccept;
          if (isitstartoraccept == "start") {
            st = true;
          }
        }
      } else if (isitstartoraccept == "acceptstart") {
        ac = true;
        st = true;
      } else {
        exit(1);
      }
      State muhstate{{}, st, ac, fuckingstate};
      shittynfa.insert({fuckingstate, muhstate});
    } else if (command == "transition") {
      size_t from, to;
      char sym;
      ss >> from;
      ss >> sym;
      ss >> to;
      if (shittynfa.find(from) == shittynfa.end())
        shittynfa.emplace(from, from);
      shittynfa.at(from).add_transition({sym, to});
    }
  }
  fucking_nfa_function(shittynfa, input);
}

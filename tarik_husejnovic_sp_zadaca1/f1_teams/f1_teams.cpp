#include "f1_teams.hpp"
#include <fstream>
#include <numeric>
#include <sstream>

bool F1_teams::ucitaj_timove(const std::string& file) {
  F1 f;
  std::string s;
  std::ifstream input_file{file};
  if (!input_file) {
    std::cout << "Nije moguce otvoriti file!" << std::endl;
    return false;
  }
  std::getline(input_file, s);
  while (std::getline(input_file, s)) {
    std::stringstream ss{s};
    ss >> f;
    push_back(f);
  }
  input_file.close();
  return false;
}





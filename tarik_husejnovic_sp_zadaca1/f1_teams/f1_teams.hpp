#pragma once
#include "f1.hpp"
#include <vector>

class F1_teams : public std::vector<F1> {
public:
  bool ucitaj_timove(const std::string& file);
  template <typename P>
  void for_each(P pred) {
    for (auto it = begin(); it != end(); ++it)
      pred(*it);
  }

};

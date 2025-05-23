#pragma once

#include "radnik.hpp"

#include <vector>

class Firma : public std::vector<Radnik> {
public:
  bool ucitaj_radnike(const std::string& file);

  double ukupna_plata() const;

  template <typename P>
  void for_each(P pred) {
    for (auto it = begin(); it != end(); ++it)
      pred(*it);
  }
};

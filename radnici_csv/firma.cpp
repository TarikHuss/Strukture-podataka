#include "firma.hpp"

#include <fstream>
#include <numeric>
#include <sstream>

bool Firma::ucitaj_radnike(const std::string& file) {
  Radnik r;
  std::string s;
  std::ifstream input_file{file};
  if (!input_file) {
    std::cout << "Nije moguce otvoriti file!" << std::endl;
    return false;
  }

  std::getline(input_file, s);
  while (std::getline(input_file, s)) {
    std::stringstream ss{s};
    ss >> r;
    push_back(r);
  }
  input_file.close();
  return true;
}

double Firma::ukupna_plata() const {
  double plata = 0.;
  for (auto it = begin(); it != end(); ++it)
    plata += it->plata();
  return plata;
}

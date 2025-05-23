#include "radnik.hpp"

std::ostream& operator<<(std::ostream& out, const Radnik& radnik) {
  return out << radnik.ime_ << "," << radnik.prezime_ << "," << radnik.godine_
             << "," << radnik.godine_staza_ << "," << radnik.plata_ << ","
             << radnik.broj_telefona_;
}

std::istream& operator>>(std::istream& in, Radnik& r) {
  std::string temp_string;
  std::getline(in, r.ime_, ',');
  std::getline(in, r.prezime_, ',');
  std::getline(in, temp_string, ',');
  r.godine(std::stoi(temp_string));
  std::getline(in, temp_string, ',');
  r.godineStaza(std::stoi(temp_string));
  std::getline(in, temp_string, ',');
  r.plata(std::stoi(temp_string));
  std::getline(in, r.broj_telefona_);
  return in;
}

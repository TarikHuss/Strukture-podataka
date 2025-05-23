#include "f1.hpp"

std::ostream& operator<<(std::ostream& out, const F1& tim) {
  return out << tim.ime_ << "," << tim.drzava_ << "," << tim.godine_
    << "," << tim.titule_ << "," << tim.budzet_;
}

std::istream& operator>>(std::istream& in, F1& f) {
  std::string temp;
  std::getline(in, f.ime_, ',');
  std::getline(in, f.drzava_, ',');
  std::getline(in, temp, ',');
  f.godine_=std::stoi(temp);
  std::getline(in, temp, ',');
  f.titule_=std::stoi(temp);
  std::getline(in, temp);
  f.budzet_=std::stoi(temp);

  return in;
}

#include "duration.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>

Duration& Duration::set_s(int s) {
 if(s >= 60 || s < 0)
  throw std::out_of_range("Zadana vrijednost je izvan dozvoljenog opsega!");
 s_ = s;
return *this;
}

Duration& Duration::set_m(int m) {
 if(m >= 60 || m < 0)
  throw std::out_of_range("Zadana vrijednost je izvan dozvoljenog opsega!");
 m_ = m;
return *this;
}

Duration& Duration::set_h(int h) {
 if(h < 0)
  throw std::out_of_range("Zadana vrijednost je izvan dozvoljenog opsega!");
 h_ = h;
return *this;
}

bool Duration::operator==(const Duration& drugi) const {
  if(s_==drugi.s_ && m_==drugi.m_ && h_==drugi.h_) {
    return true;
  }
  else {
    return false;
  }
}

bool Duration::operator!=(const Duration& drugi) const {
  if(s_!=drugi.s_ || m_!=drugi.m_ || h_!=drugi.h_) {
    return true;
  }
  else {
    return false;
  }
}

bool Duration::operator<(const Duration& drugi) const {
  if(h_<drugi.h_) {
    return true;
  }
  else if(h_==drugi.h_ && m_<drugi.m_){
    return true;
  }
  else if(h_==drugi.h_ && m_==drugi.m_ && s_<drugi.s_) {
    return true;
  }
  else {
    return false;
  }
}

bool Duration::operator>(const Duration& drugi) const {
  if(h_>drugi.h_) {
    return true;
  }
  else if(h_==drugi.h_ && m_>drugi.m_){
    return true;
  }
  else if(h_==drugi.h_ && m_==drugi.m_ && s_>drugi.s_) {
    return true;
  }
  else {
    return false;
  }
}

bool Duration::operator<=(const Duration& drugi) const {
  if((this->operator<(drugi)) || (this->operator==(drugi))){
    return true;
  }
  else {
    return false;
  }
}

bool Duration::operator>=(const Duration& drugi) const {
  if((this->operator>(drugi)) || (this->operator==(drugi))){
    return true;
  }
  else {
    return false;
  }
}

Duration Duration::operator-(const Duration& drugi) const{
  if(drugi>*this){
    throw std::out_of_range("Nevalidna operacija!");
  }
  else{
    int t=(s_+m_*60+h_*3600)-(drugi.s_+drugi.m_*60+drugi.h_*3600);
    return Duration(t);
  }
}

Duration Duration::operator/(int a) const{
  if(a == 0)
    throw std::invalid_argument("Dijeljenje sa nulom nije dozvoljeno!");
  int t = s_+m_*60+h_*3600;
  return Duration(t/a);
  };

std::ostream& operator<<(std::ostream& o, const Duration& dur) {
  o << std::setfill('0') << std::setw(2) << dur.get_h() << ":"
       << std::setw(2) << dur.get_m() << ":"
       << std::setw(2) << dur.get_s();
  return o;
}

std::istream& operator>>(std::istream& i, Duration& dur) {
  int h, m, s;
  char colon1, colon2;
  if (!(i >> h >> colon1 >> m >> colon2 >> s) || colon1 != ':' || colon2 != ':') {
    throw std::invalid_argument("Invalid time format!");
  }
  dur = Duration(h, m, s);
  return i;
}




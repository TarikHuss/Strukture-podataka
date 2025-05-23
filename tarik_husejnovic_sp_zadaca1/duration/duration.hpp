#pragma once 
#include <stdexcept>
#include <string>
#include <sstream>

class Duration {
  public:
  Duration() : s_{0}, m_{0}, h_{0} {};
  Duration(const Duration& drugi) : s_{drugi.s_}, m_{drugi.m_}, h_{drugi.h_} {};
  Duration(Duration&& drugi) : s_{drugi.s_}, m_{drugi.m_}, h_{drugi.h_} {
    drugi.s_ = 0;
    drugi.m_ = 0;
    drugi.h_ = 0;
  };
  Duration& operator=(const Duration& drugi) {
    if(this != &drugi) {
     s_=drugi.s_;
     m_=drugi.m_;
     h_=drugi.h_;
    }
    return *this;
  };
  Duration& operator=(Duration&& drugi) {
    s_=drugi.s_;
    m_=drugi.m_;
    h_=drugi.h_;
    drugi.s_=0;
    drugi.m_=0;
    drugi.h_=0;
    return *this;
  };
  ~Duration() {};
  Duration(int s) : s_{s}, m_{0}, h_{0} {
  if(s >= 60) {
    m_ = s_ / 60;
    s_ = s_ % 60;
    if(m_ >= 60) {
      h_ = m_ / 60;
      m_ = m_ % 60;
    }
  }
  };
  Duration(int h, int m, int s) : s_{s}, m_{m}, h_{h} {
  if(h_ < 0 || m_ >= 60 || m_ < 0 || s_ >= 60 || s_ < 0)
    throw std::out_of_range("Zadana vrijednost je izvan dozvoljenog opsega!"); 
  };
  Duration(const std::string& ss) {
    std::istringstream iss(ss);
    char colon1, colon2;
    int h, m, s;
  if (!(iss >> h >> colon1 >> m >> colon2 >> s) || colon1 != ':' || colon2 != ':') {
    throw std::invalid_argument("Invalid time format!");
  }
  if (h < 0 || m < 0 || s < 0 || m >= 60 || s >= 60) {
    throw std::out_of_range("Invalid hour, minute, or second value!");
  }
    s_ = s;
    m_ = m;
    h_ = h;
  };
  int get_s () const {return s_;}
  int get_m () const {return m_;}
  int get_h () const {return h_;}
  Duration& set_s (int);
  Duration& set_m (int);
  Duration& set_h (int);
  bool operator==(const Duration&) const;
  bool operator!=(const Duration&) const;
  bool operator<(const Duration&) const;
  bool operator>(const Duration&) const;
  bool operator<=(const Duration&) const;
  bool operator>=(const Duration&) const;
  explicit operator bool() const {
    return (s_!=0 || m_!=0 || h_!=0 ? true : false);
  };
  bool operator!() const {
    return (s_!=0 || m_!=0 || h_!=0 ? false : true);
  };
  Duration operator+(const Duration& drugi) const{
    int t = s_ + drugi.s_ + (m_ + drugi.m_)*60 + (h_ + drugi.h_)*3600;
    return Duration(t);
  };
  Duration& operator+=(const Duration& drugi) {
    *this=*this+drugi;
    return *this;
  };
  Duration operator-(const Duration&) const;
  Duration& operator-=(const Duration& drugi) {
    *this=*this-drugi;
    return *this;
  };
  Duration operator*(int a) const{
    int t = (s_*a)+(m_*a)*60+(h_*a)*3600;
    return Duration(t);
  };
  Duration& operator*=(int a) {
    *this=*this*a;
    return *this;
  };
  Duration operator/(int a) const;
  Duration& operator/=(int a) {
    *this=*this/a;
    return *this;
  };
  
  private:
    int s_, m_, h_;
};

std::ostream& operator<<(std::ostream&, const Duration&);
std::istream& operator>>(std::istream&, Duration&);

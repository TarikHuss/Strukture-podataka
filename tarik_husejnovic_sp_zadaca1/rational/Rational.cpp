#include "Rational.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cmath>
#include <sstream>
#include <fstream>

int gcd(int numerator, int denominator) {
  if(numerator<0)
    numerator=-numerator;
  if(denominator<0)
    denominator=-denominator;
  const int num = numerator;
  const int denom = denominator;
  int shift;
  for (shift = 0; ((numerator | denominator) & 1) == 0; ++shift) {
    numerator >>= 1;
    denominator >>= 1;
  }
  while ((numerator & 1) == 0) {
    numerator >>= 1;
  }
  while (denominator != 0) {
    while ((denominator & 1) == 0) {
      denominator >>= 1;
    }
    if (numerator > denominator) {
      std::swap(numerator, denominator);
    }
    denominator -= numerator;
  }
return numerator << shift;
}
void Rational::skrati() {
  int common = gcd(numerator_, denominator_);
  numerator_/= common;
  denominator_/= common;
}

Rational::Rational() : numerator_{0}, denominator_{1} {};
Rational::Rational(int numerator) : numerator_{numerator}, denominator_{1} {
  skrati();
};
Rational::Rational(int numerator, int denominator) {
  if(denominator==0) {
    throw std::invalid_argument("Nazivnik ne smije biti 0!");
  }
  else {
    numerator_ = numerator;
    denominator_ = denominator;
    skrati();
  }
};
Rational::Rational(const char* rational) {
std::istringstream ss(rational);
char slash;
int a,b;
if ((ss >> a)) {
  numerator_ = a;
  if (ss >> slash >> b && slash == '/' && ss.eof()) {
    denominator_ = b;
  } else if (ss.eof()) {
      denominator_ = 1;
    } else {
    throw std::invalid_argument("Nevalidan format!");
    }
    } else {
    throw std::invalid_argument("Nevalidan format!");
  }
skrati();
};
Rational::Rational(const std::string& s) {
std::istringstream ss(s);
char slash;
int a,b;
if ((ss >> a)) {
  numerator_ = a;
  if (ss >> slash >> b && slash == '/' && ss.eof()) {
    denominator_ = b;
  } else if (ss.eof()) {
      denominator_ = 1;
    } else {
    throw std::invalid_argument("Nevalidan format!");
    }
    } else {
    throw std::invalid_argument("Nevalidan format!");
  }
skrati();
};
Rational::Rational(const Rational& rational) 
: numerator_{rational.numerator_}, denominator_{rational.denominator_} {};
Rational::Rational(Rational&& rational) 
: numerator_{rational.numerator_}, denominator_{rational.denominator_} {
  rational.numerator_ = 0;
  rational.denominator_ = 1;
};
Rational& Rational::operator=(const Rational& rational) {
if(this!=&rational) {
  numerator_=rational.numerator_;
  denominator_=rational.denominator_;
}
return *this;
};
Rational& Rational::operator=(Rational&& rational) {
  numerator_=rational.numerator_;
  denominator_=rational.denominator_;
  rational.numerator_ = 0;
  rational.denominator_ = 1;
  return *this;
};
Rational Rational::operator+(const Rational& rational) const{
  int newNumerator = numerator_* rational.denominator_+ rational.numerator_* denominator_;
  int newDenominator = denominator_* rational.denominator_;
return Rational(newNumerator, newDenominator);
};
Rational Rational::operator+(int numerator) const{
  int newNumerator = numerator_ + numerator*denominator_;
  return Rational(newNumerator, denominator_);
};
Rational Rational::operator-(const Rational& rational) const{
  int newNumerator;
  int newDenominator;
  newNumerator = numerator_ * rational.denominator_ - rational.numerator_ * denominator_;
  newDenominator = denominator_ * rational.denominator_; 
  return Rational(newNumerator, newDenominator);
};
Rational Rational::operator-(int numerator) const{
  int newNumerator = numerator_ - numerator*denominator_;
  return Rational(newNumerator, denominator_);
};
Rational Rational::operator*(const Rational& rational) const{
  int newNumerator=numerator_*rational.numerator_;
  int newDenominator=denominator_*rational.denominator_;
  return Rational(newNumerator, newDenominator);
};
Rational Rational::operator*(int numerator) const{
  int newNumerator=numerator_*numerator;
  return Rational(newNumerator, denominator_);
};
Rational Rational::operator/(const Rational& rational) const{
  int newNumerator=numerator_*rational.denominator_;
  int newDenominator=denominator_*rational.numerator_;
  return Rational(newNumerator, newDenominator);
};
Rational Rational::operator/(int numerator) const{
  int newDenominator=denominator_*numerator;
  return Rational(numerator_, newDenominator);
};
Rational Rational::operator^(int power) const{
  if (power == 0) {
    return Rational(1, 1); 
  }
  else if(power > 0) {
    int a = 1;
    int b = 1;
    for(int i = 0;i<power;++i){
     a*=numerator_;
     b*=denominator_;
   }
    return Rational{a,b};
  }
  else{
    int a = 1;
    int b = 1;
    for(int i = 0; i<-power;++i){
      a*=denominator_;
      b*=numerator_;
    }
    return Rational{a,b};
  }
  /*else if (power < 0) {
    return Rational(std::pow(denominator_, -power), std::pow(numerator_, -power));
  }
  else {
    return Rational(std::pow(numerator_, power), std::pow(denominator_, power));
  }*/
};
Rational& Rational::operator++() {
  *this=*this+1;
  return *this;
};
Rational Rational::operator++(int) {
  Rational a=*this;
  *this=*this+1;
  return a;
};
Rational& Rational::operator--() {
  *this=*this-1;
  return *this;
};
Rational Rational::operator--(int) {
  Rational a=*this;
  *this=*this-1;
  return a;
};
bool Rational::operator==(const Rational& rational) const{
  return (numerator_ == rational.numerator_ && denominator_==rational.denominator_)
  ?true:false;
};
bool Rational::operator==(const char* rational) const{
  Rational a{rational};
 return (numerator_ == a.numerator_ && denominator_==a.denominator_)
  ?true:false;
};
bool Rational::operator!=(const Rational& rational) const{
  return (numerator_ != rational.numerator_ || denominator_!=rational.denominator_)
  ?true:false;
};
bool Rational::operator!=(const char* rational) const{
  Rational a{rational};
 return (numerator_ != a.numerator_ || denominator_!=a.denominator_)
  ?true:false;
};
const int Rational::numerator() const{
  return numerator_;
}
const int Rational::denominator() const{
  return denominator_;
}
Rational::~Rational() {};

std::ostream& operator<<(std::ostream& os, const Rational& rational) {
  if(rational.denominator() == 1) {
    os<<rational.numerator();
  }
  else{
    os<<rational.numerator()<<"/"<<rational.denominator();
  }
  return os;
};

std::istream& operator>>(std::istream& ss, Rational& rational) {
char slash;
int a,b;
if ((ss >> a)) {
  rational.numerator_ = a;
  if (ss >> slash >> b && slash == '/' ) {
    rational.denominator_ = b;
  } else if(ss.eof()) {
      rational.denominator_ = 1;
      //ss.unget();
    } else {
    throw std::invalid_argument("Nevalidan format!");
    }
    } else {
    throw std::invalid_argument("Nevalidan format!");
  }
rational.skrati();
return ss;
}; 



















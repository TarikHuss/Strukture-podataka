#pragma once
#include "../zadatak1/DoubleLinkedList.hpp"
#include <iostream>

class Number {
public:
  Number();
  Number(const Number &);
  Number(Number &&);
  Number &operator=(const Number &);
  Number &operator=(Number &&);
  Number(int);

  Number operator+(const Number &) const;
  Number operator-(const Number &) const;
  Number &operator+=(const Number &);
  Number &operator-=(const Number &);
  Number &operator=(const int &);
  Number &operator=(int &&);
  Number operator+(const int &) const;
  Number operator-(const int &) const;
  Number &operator+=(const int &);
  Number &operator-=(const int &);
  bool operator==(const Number &o) const;
  bool operator!=(const Number &) const;
  bool operator>(const Number &) const;
  bool operator<(const Number &) const;
  bool operator>=(const Number &) const;
  bool operator<=(const Number &) const;
  bool operator==(const int &) const;
  bool operator!=(const int &) const;
  bool operator>(const int &) const;
  bool operator<(const int &) const;
  bool operator>=(const int &) const;
  bool operator<=(const int &) const;
  //   Stepenovanje
  Number operator^(short) const;
  //   Primjer pozivanja operator bool():
  //     Number num;
  //       if(num)  Poziva se operator bool()
  //        cout << "Valid" << std::endl;;
  operator bool() const;
  Number &operator++();
  Number operator++(int);
  Number &operator--();
  Number operator--(int);

  friend std::ostream &operator<<(std::ostream &o, const Number &num);

private:
  DoubleLinkedList<int> digits_{};
  bool negative_ = false;
};


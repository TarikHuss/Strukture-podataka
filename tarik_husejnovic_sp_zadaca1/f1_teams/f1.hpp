#pragma once

#include <iostream>
#include <string>

class F1 {
  public:
 
  friend std::istream& operator>>(std::istream&, F1&);
  friend std::ostream& operator<<(std::ostream&, const F1&);

  const std::string& ime() const {
    return ime_;
  }
  void ime(const std::string& ime) {
    ime_ = ime;
  }

  const std::string& drzava() const {
    return drzava_;
  }
  void drzava(const std::string& drzava) {
    drzava_ = drzava;
  }

  int godine() const {
    return godine_;
  }
  void godine(int godina) {
    godine_ = godina;
  }

  int titule() const {
    return titule_;
  }
  void titule(int titule) {
    titule_ = titule;
  }

  int budzet() const {
    return budzet_;
  }
  void budzet(double budzet) {
    budzet_ = budzet;
  }

private:
  std::string ime_;
  std::string drzava_;
  int godine_;
  int titule_;
  int budzet_;
};

#include "annotated.hpp"

#include <iostream>
#include <string>

class Customer {
  AnnotatedString firstname;
  AnnotatedString lastname;

public:
  // Customer(const AnnotatedString& ime, const AnnotatedString& prezime)
  //   : firstname{ime}, lastname{prezime} {
  // }

  // Customer(AnnotatedString&& ime, AnnotatedString&& prezime)
  //   : firstname{std::move(ime)}, lastname{std::move(prezime)} {
  // }

  template <typename F, typename G>
  Customer(F&& ime, G&& prezime)
    : firstname{std::forward<F>(ime)}, lastname{std::forward<G>(prezime)} {
  }

  template <typename T>
  void setIme(T&& ime) {
    firstname = std::forward<T>(ime);
  }

  template <typename T>
  void setPrezime(T&& prezime) {
    lastname = std::forward<T>(prezime);
  }
};

int main() {
  AnnotatedString ime{"Harun"};
  AnnotatedString prezime{"Delic"};

  // Customer customer(ime, prezime);
  // Customer customer(std::move(ime), std::move(prezime));
  // Customer customer(ime, std::move(prezime));
  Customer customer(std::move(ime), prezime);

  return 0;
}

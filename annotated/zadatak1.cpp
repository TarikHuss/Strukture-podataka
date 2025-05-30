#include "annotated.hpp"

#include <iostream>
#include <string>

class Customer {
  AnnotatedString firstname;
  AnnotatedString lastname;

public:
  //   Customer(const AnnotatedString& ime, const AnnotatedString& prezime) {
  //     firstname = ime;
  //     lastname = prezime;
  //   }

  Customer(const AnnotatedString& ime, const AnnotatedString& prezime)
    : firstname{ime}, lastname{prezime} {
  }

  Customer(const char* ime, const char* prezime) {
    firstname = AnnotatedString{ime};
    lastname = AnnotatedString{prezime};
  }

  // // Prva verzija
  // void setIme(const AnnotatedString& ime) {
  //   firstname = ime;
  // }
  //
  // void setIme(AnnotatedString&& ime) {
  //   firstname = std::move(ime);
  // }

  // Druga verzija
  template <typename F>
  void setIme(F&& ime) {
    firstname = std::forward<F>(ime);
  }

  template <typename F>
  void setPrezime(F&& prezime) {
    lastname = std::forward<F>(prezime);
  }
};

int main() {
  std::cout << "primjer ctor" << std::endl;
  AnnotatedString ime{"Harun"};
  AnnotatedString prezime{"Jaranović"};
  std::cout << "kraj ctor" << std::endl;

  std::cout << "primjer I" << std::endl;
  Customer customer(ime, prezime);

  std::cout << "primjer II" << std::endl;
  Customer customer1("Harun", "Jaranović");

  std::cout << "poziv settera I" << std::endl;
  customer.setIme(ime);
  std::cout << "kraj poziv settera I" << std::endl;

  std::cout << "poziv settera II" << std::endl;
  customer.setPrezime(std::move(prezime));
  std::cout << "kraj settera" << std::endl;

  return 0;
}

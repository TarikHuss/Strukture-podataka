#include "annotated.hpp"

#include <iostream>
#include <string>

// rvo
AnnotatedString stringFactory() {
  AnnotatedString ime;
  ime.value = "Mak";
  return ime;
}

int main() {
  auto ime = stringFactory();
  return 0;
}

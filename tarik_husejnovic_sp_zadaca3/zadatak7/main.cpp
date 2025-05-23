#include <iostream>
#include <string>
#include "../zadatak5/Stack.hpp"

bool otvorenaZagrada(char c) { return c == '<' || c == '(' || c == '[' || c == '{'; }

bool zatvorenaZagrada(char c) { return c == '>' || c == ')' || c == ']' || c == '}'; }

bool pravilnaZagrada(char l, char r) {
  return (l == '<' && r == '>') || (l == '(' && r == ')') || (l == '[' && r == ']') || (l == '{' && r == '}');
}

int hijerarhija(char c) {
  switch(c) {
    case '<': return 3;
    case '(': return 2;
    case '[': return 1;
    case '{': return 0;
    default: return -1; 
    }
  }

std::string provjeriZagrade(const std::string& linija) {
  Stack<char> zagrade;
  for (char c : linija) {
    if (otvorenaZagrada(c)) {
      if (!zagrade.empty() && hijerarhija(c) < hijerarhija(zagrade.top())) {
        return "pogrešan";
      }
      zagrade.push(c);
      } 
      else if (zatvorenaZagrada(c)) {
        if (!zagrade.empty() && pravilnaZagrada(zagrade.top(), c)) {
          zagrade.pop();
        } 
        else {
          return "pogrešan";
        }
      }
    }
  return zagrade.empty() ? "dobar" : "pogrešan";
  }

int main() {
  std::string linija;
  while (std::getline(std::cin, linija)) {
    if (linija.empty()) {
      break; 
    }
    std::string result = provjeriZagrade(linija);
    std::cout << result << std::endl;
  }
  return 0;
}

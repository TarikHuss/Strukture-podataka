#include "Rational.hpp"
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
 try {
  std::ifstream inputFile("input.txt");
  std::vector<Rational> rational; 
  Rational r; 
  while (inputFile>>r) {
    rational.push_back(r); 
  }
  inputFile.close();

  for(auto it=begin(rational);it!=end(rational);++it)
    std::cout<<*it<<" ";
 }

 catch(const std::invalid_argument& c) {
   std::cout<<c.what()<<std::endl;
 }
  return 0;
}

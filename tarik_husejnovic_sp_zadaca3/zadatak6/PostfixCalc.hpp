#pragma once
#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

class PostfixCalc { 
  private:
    std::stack<int> calc;
  public:
    int calculate(std::string);
    bool isOperator(const std::string&);
};

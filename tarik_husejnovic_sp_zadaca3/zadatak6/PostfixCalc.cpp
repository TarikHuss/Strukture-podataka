#include "PostfixCalc.hpp"

int PostfixCalc::calculate(std::string line) {
  while(!calc.empty())
    calc.pop();
  std::stringstream ss(line);
  std::string token;
  while (ss >> token) {
    if (isOperator(token)) {
      if (calc.size() < 2) {
        throw std::out_of_range("Insufficient operands for operator");
      }
      int num2 = calc.top();
      calc.pop();
      int num1 = calc.top();
      calc.pop();
      switch (token[0]) {
        case '+':
        calc.push(num1 + num2);
        break;
        case '-':
        calc.push(num1 - num2);
        break;
        case '*':
        calc.push(num1 * num2);
        break;
        case '/':
        if (num2 == 0) 
          throw std::out_of_range("Division by zero");
        calc.push(num1 / num2);
        break;
        default:
        throw std::out_of_range("Invalid operator");
      }
    } 
    else {
      try {
        int operand = std::stoi(token);
        calc.push(operand);
      } 
      catch (const std::invalid_argument&) { 
        throw std::out_of_range("Invalid operand");
      } 
    }
  }
  if (calc.size() != 1) 
    throw std::out_of_range("Invalid expression");
  int result = calc.top();
  calc.pop();
  return result;
}

bool PostfixCalc::isOperator(const std::string& token) {
  return token == "+" || token == "-" || token == "*" || token == "/";
}

int main() {
  PostfixCalc calc;
  std::string expression;

  while (true) {
    std::cout << "Enter a postfix expression (or 'exit' to quit): ";
    std::getline(std::cin, expression);
    if (expression == "exit") {
      break;
    }
    try {
      int result = calc.calculate(expression);
      std::cout << "Result: " << result << std::endl;
    } 
    catch (const std::out_of_range& e) {
      std::cout << "Error: " << e.what() << std::endl;
    }
  }

  return 0;
}


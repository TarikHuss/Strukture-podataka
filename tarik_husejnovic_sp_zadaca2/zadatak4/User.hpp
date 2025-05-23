#pragma once
#include <string>

class User {
  public:
  User();
  User(std::string, std::string, int);
  User(const User&);
  const int& get_userID() const;
  int get_owns() const;
  User& operator++();
  User& operator--();

  private:
  std::string firstName_;
  std::string lastName_;
  int userID_;
  int owns_=0;
};

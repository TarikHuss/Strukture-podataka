#include "User.hpp"

User::User() = default;

User::User(std::string firstName, std::string lastName, int userID) : firstName_{firstName}, lastName_{lastName}, userID_{userID} {}

User::User(const User& other) : firstName_{other.firstName_}, lastName_{other.lastName_}, userID_{other.userID_}, owns_{other.owns_} {}

const int& User::get_userID() const { return userID_; }

int User::get_owns() const { return owns_; }

User& User::operator++() {
  ++owns_;
  return *this;
}

User& User::operator--() {
  --owns_;
  return *this;
}

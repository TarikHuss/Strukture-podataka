#pragma once
#include "../zadatak1/MojVektor.hpp"
#include "Book.hpp"
#include "User.hpp"

class Library {
  public:
  void create_user();
  void book_add();
  void book_borrow();
  void book_return();
  void book_search_by_title() const;
  void book_search_by_author() const;
  void book_search_by_publisher() const;
  void book_search_by_publication_year() const;
  void help() const;

  private:
  MojVektor<Book> books_;
  MojVektor<User> users_;
};

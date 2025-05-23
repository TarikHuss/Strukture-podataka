#pragma once
#include <string>

class Book {
  public:
  Book();
  Book(std::string, std::string, std::string, int, int);
  Book(const Book&);
  Book& operator=(const Book&);
  Book& operator++();
  Book& operator--();
  const std::string& get_title() const;
  const std::string& get_author() const;
  const std::string& get_publisher() const;
  const int& get_publicationYear() const;
  const int& get_numberOfCopies() const;
  void print() const;

  private:
  std::string title_;
  std::string author_;
  std::string publisher_;
  int publicationYear_;
  int numberOfCopies_;
};

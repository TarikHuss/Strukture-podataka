#include "Book.hpp"
#include <iostream>

Book::Book()=default;

Book::Book(std::string title, std::string author, std::string publisher, int publicationYear, int numberOfCopies)
    : title_{title}, author_{author}, publisher_{publisher}, publicationYear_{publicationYear}, numberOfCopies_{numberOfCopies} {}

Book::Book(const Book& other): title_{other.title_}, author_{other.author_}, publisher_{other.publisher_}, publicationYear_{other.publicationYear_}, numberOfCopies_{other.numberOfCopies_} {}

Book& Book::operator=(const Book& other) {
  title_ = other.title_;
  author_ = other.author_;
  publisher_ = other.publisher_;
  publicationYear_ = other.publicationYear_;
  numberOfCopies_ = other.numberOfCopies_;
  return *this;
}

Book& Book::operator++() {
  ++numberOfCopies_;
  return *this;
}
Book& Book::operator--() {
  --numberOfCopies_;
  return *this;
}

const std::string& Book::get_title() const { return title_; }
const std::string& Book::get_author() const { return author_; }
const std::string& Book::get_publisher() const { return publisher_; }
const int& Book::get_publicationYear() const { return publicationYear_; }
const int& Book::get_numberOfCopies() const { return numberOfCopies_; }

void Book::print() const{
  std::cout<< "--------------------------------------------------"<<std::endl;
  std::cout<< "Title: "<<title_<<std::endl;
  std::cout<< "Author: "<< author_ <<std::endl;
  std::cout<< "Publisher: "<<publisher_<<std::endl;
  std::cout<< "Publication year: " <<publicationYear_<<std::endl;
  std::cout<< "Number of copies: " <<numberOfCopies_<<std::endl;
  std::cout<< "--------------------------------------------------"<<std::endl;
}

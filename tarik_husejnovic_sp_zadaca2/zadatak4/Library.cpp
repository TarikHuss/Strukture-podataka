#include "Library.hpp"
#include <iostream>

void Library::create_user() {
  std::string firstName, lastName;
  int userID;
  std::cout<< "First name: ";
  std::cin.ignore();
  std::getline(std::cin, firstName);
  std::cout<< "Last name: ";
  std::getline(std::cin, lastName);
  std::cout<< "User ID: ";
  std::cin>> userID;
  int n = 0;
  for (size_t i = 0; i < users_.size(); ++i) {
    if (users_[i].get_userID() == userID) {
      ++n;
      break;
    }
  }
  if (n) {
    std::cout<< "User with id {" << userID << "} already exist!" <<std::endl;
    std::cout<< ".................................................."<<std::endl;
  } else {
    User user{firstName, lastName, userID};
    users_.push_back(user);
    std::cout<< "User created successfully." <<std::endl;
    std::cout<< ".................................................."<<std::endl;
  }
}

void Library::book_add() {
  std::string title, author, publisher;
  int publicationYear, numberOfCopies;
  std::cout<< "Title: ";
  std::cin.ignore();
  std::getline(std::cin, title);
  std::cout<< "Author: ";
  std::getline(std::cin, author);
  std::cout<< "Publisher: ";
  std::getline(std::cin, publisher);
  std::cout<< "Publication year: ";
  std::cin>>publicationYear;
  std::cout<< "Number of copies: ";
  std::cin>>numberOfCopies;
  Book book{title, author, publisher, publicationYear, numberOfCopies};
  books_.push_back(book);
  std::cout<< "Book added successfully."<<std::endl;
  std::cout<< ".................................................."<<std::endl;
}

void Library::book_borrow(){
  int userID;
  std::string title;
  std::cout<< "User ID: ";
  std::cin>>userID;
  std::cout<< "Book title: ";
  std::cin.ignore();
  std::getline(std::cin, title);
  int n = 0;
  for (size_t i = 0; i < users_.size(); ++i) {
    if (users_[i].get_userID() == userID) {
      if (users_[i].get_owns() == 0) {
        for (size_t j = 0; j < books_.size(); ++j) {
          if (books_[j].get_title() == title) {
            ++n;
            if (books_[j].get_numberOfCopies() > 0) {
              ++n;
              --books_[j];
              ++users_[i];
            }
            break;
          }
        }
      } else {
        n = 3;
        break;
      }
    }
  }
  if (n == 0)
    std::cout<<"Book not found."<<std::endl;
  else if (n == 1)
    std::cout<<"Book not available."<<std::endl;
  else if (n == 3)
    std::cout<<"The user with this ID already owns a book"<<std::endl;
  else
    std::cout<<"Book successfully borrowed"<<std::endl;
  std::cout<<".................................................."<<std::endl;
}

void Library::book_return() {
  int userID;
  std::string title;
  std::cout<< "User ID: ";
  std::cin>>userID;
  std::cout<< "Book title: ";
  std::cin.ignore();
  std::getline(std::cin, title);
  for(size_t i = 0; i<users_.size(); ++i) {
    if (users_[i].get_userID() == userID) {
      for (size_t j = 0; j < books_.size(); ++j) {
        if (books_[j].get_title() == title) {
          ++books_[j];
          --users_[i];
          break;
        }
      }
    }
  }
  std::cout<< "Book successfully returned" <<std::endl;
  std::cout<< ".................................................." <<std::endl;
}

void Library::book_search_by_title() const {
  std::string title;
  std::cout<< "Title: ";
  std::cin.ignore();
  std::getline(std::cin, title);
  std::cout<< "Found books: " <<std::endl;
  for (size_t i = 0; i < books_.size(); ++i) {
    if (books_[i].get_title() == title) books_[i].print();
    std::cout<< std::endl;
    std::cout<< std::endl;
  }
  std::cout<< ".................................................." <<std::endl;
}

void Library::book_search_by_author() const {
  std::string author;
  std::cout<< "Author: ";
  std::cin.ignore();
  std::getline(std::cin, author);
  std::cout<< "Found books: " <<std::endl;
  for (size_t i = 0; i < books_.size(); ++i) {
    if (books_[i].get_author() == author) books_[i].print();
    std::cout<<std::endl;
    std::cout<<std::endl;
  }
  std::cout<< ".................................................." <<std::endl;
}

void Library::book_search_by_publisher() const {
  std::string publisher;
  std::cout<< "Publisher: ";
  std::cin.ignore();
  std::getline(std::cin, publisher);
  std::cout<< "Found books: " <<std::endl;
  for (size_t i = 0; i < books_.size(); ++i) {
    if (books_[i].get_publisher() == publisher) books_[i].print();
    std::cout<<std::endl;
    std::cout<<std::endl;
  }
  std::cout<< ".................................................." <<std::endl;
}

void Library::book_search_by_publication_year() const {
  int publicationYear;
  std::cout<< "Publication year: ";
  std::cin>>publicationYear;
  std::cout<< "Found books: " <<std::endl;
  for (size_t i = 0; i < books_.size(); ++i) {
    if (books_[i].get_publicationYear() == publicationYear) books_[i].print();
    std::cout<<std::endl;
    std::cout<<std::endl;
  }
  std::cout<< ".................................................." <<std::endl;
}

void Library::help() const {
  std::cout<< "--------------------------------------------------" <<std::endl;
  std::cout<< "List of commands:" <<std::endl;
  std::cout<< "==================================================" <<std::endl;
  std::cout<< "CreateUser" <<std::endl;
  std::cout<< "BookAdd" <<std::endl;
  std::cout<< "BookBorrow" <<std::endl;
  std::cout<< "BookReturn" <<std::endl;
  std::cout<< "BookSearchByTitle" <<std::endl;
  std::cout<< "BookSearchByAuthor" <<std::endl;
  std::cout<< "BookSearchByPublisher" <<std::endl;
  std::cout<< "BookSearchByPublicationYear" <<std::endl;
  std::cout<< "Help" <<std::endl;
  std::cout<< "Exit" <<std::endl;
  std::cout<< "--------------------------------------------------" <<std::endl;
  std::cout<< ".................................................." <<std::endl;
}

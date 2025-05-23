#include <iostream>
#include <string>
#include "Book.hpp"
#include "Library.hpp"
#include "User.hpp"

int main(void) {
  Library library;

  std::cout<< "=================================================="<<std::endl;
  std::cout<< "University of Tuzla"<<std::endl;
  std::cout<< "Faculty od Electrical Engineering"<<std::endl;
  std::cout<<std::endl;
  std::cout<< "Library application" <<std::endl;
  std::cout<< "Version: April 2024." <<std::endl;
  std::cout<<std::endl;
  std::cout<< "=================================================="<<std::endl;
  library.help();

  std::string command;
  std::cout<< "Enter command: ";
  while (std::cin >> command) {
    std::cout << ".................................................." << std::endl;
    if (command == "CreateUser")
      library.create_user();
    else if (command == "BookAdd")
      library.book_add();
    else if (command == "BookBorrow")
      library.book_borrow();
    else if (command == "BookReturn")
      library.book_return();
    else if (command == "BookSearchByTitle")
      library.book_search_by_title();
    else if (command == "BookSearchByAuthor")
      library.book_search_by_author();
    else if (command == "BookSearchByPublisher")
      library.book_search_by_publisher();
    else if (command == "BookSearchByPublicationYear")
      library.book_search_by_publication_year();
    else if (command == "Help")
      library.help();
    else if (command == "Exit") {
      std::cout << "Goodbye!" << std::endl;
      break;
    } else {
      std::cout << "Invalid command. Please try again." << std::endl;
      std::cout << ".................................................." << std::endl;
    }
    std::cout<<"Enter command: ";
  }

  return 0;
}

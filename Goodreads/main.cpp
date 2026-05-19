#include <iostream>
#include "GoodReads.h"
#include "Reader.h"
#include "Book.h"
#include "Repository.cpp"
int main()
{
    std::shared_ptr<Reader> eli = std::make_shared<Reader>("eli", "password");
	GoodReads::instance->getUsers().addElement(eli);
    GoodReads::instance->setActiveUser(eli);
	std::shared_ptr<Book> book = std::make_shared<Book>("book");
	GoodReads::instance->getBooks().addElement(book);
    while (true) {
        std::string command;
        std::cout << "Enter command: ";
        std::getline(std::cin, command);
        GoodReads::instance->ExecuteCommand(command);
	}
}
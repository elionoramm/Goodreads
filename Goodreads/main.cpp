#include <iostream>
#include "GoodReads.h"
#include "Reader.h"
int main()
{
    std::shared_ptr<Reader> eli = std::make_shared<Reader>("eli", "password");
	GoodReads::instance->getUsers().addElement(eli);
    GoodReads::instance->setActiveUser(eli);
    while (true) {
        std::string command;
        std::cout << "Enter command: ";
        std::getline(std::cin, command);
        GoodReads::instance->ExecuteCommand(command);
	}
}
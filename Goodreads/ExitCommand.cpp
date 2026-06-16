#include "ExitCommand.h"

Exit::Exit(GoodReads& goodReads) : goodReads(goodReads) {}

void Exit::execute(std::vector<std::string> params) {
	if (params.size() != 0) {
		throw WrongCommandUsage("Usage: exit\n");
	}
	BookSystem& bookSystem = goodReads.getBookSystem();
	UserSystem& userSystem = goodReads.getUserSystem();
	std::fstream file;
	file.open("GoodReads.txt", std::fstream::out);
	if (file.is_open()) {
		bookSystem.saveBookSystem(file);
		userSystem.saveUserSystem(file);
		file.close();
	}
	std::cout << "Exiting the application. Goodbye.\n" << std::endl;
	std::exit(0);
}
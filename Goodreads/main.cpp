#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "GoodReads.h"
#include "Command.h"
#include "CommandFactory.h"
#include "CustomUserExceptions.h"

int main() {
	GoodReads goodReads = GoodReads();
	CommandFactory commandFactory = CommandFactory(goodReads);
	while (true) {
		std::string line;
		std::cout << "Enter command: ";
		std::getline(std::cin, line);
		std::unique_ptr<Command> command;
		std::string word;
		std::vector<std::string> params;
		for (int i = 0; i <= line.size(); i++) {
			if (line[i] != ' ' && line[i] != '\0') {
				word = word + line[i];
			}
			else if (word != "") {
				params.push_back(word);
				word = "";
			}
		}
		if (params.size() != 0) {
			command = commandFactory.create(params[0]);
			params.erase(params.begin());
		}
		try {
			command->execute(params);
		}
		catch (const WrongUserCommand& ex) {
			std::cout << ex.what() << '\n';
		}
		catch (const WrongCommandUsage& ex){
			std::cout << ex.what() << '\n';
		}
		catch (const NotLoggedIn& ex) {
			std::cout << ex.what() << '\n';
		}
		catch (const std::logic_error& ex) {
			std::cout << ex.what() << '\n';
		}
	}
}
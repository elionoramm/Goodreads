#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "User.h"
#include "Reader.h"
#include "Author.h"
#include "Publisher.h"
#include "Repository.h"
#include "Command.h"
#include "GoodReads.h"

// User commands
class Help : public Command {
public:
	void execute(std::vector<std::string> substrings) override;
};

class Register : public Command {
public:
	void execute(std::vector<std::string> substrings) override;
};

class Login : public Command {
public:
	void execute(std::vector<std::string> substrings) override;
};

class Logout : public Command {
public:
	void execute(std::vector<std::string> substrings) override;
};

class Exit : public Command {
public:
	void execute(std::vector<std::string> substrings) override;
};

// Reader commands
class Search : public Command {
public:
	bool caseInsensitiveMatch(const std::string& str1, const std::string& str2);
	void execute(std::vector<std::string> substrings) override;
};

class Follow : public Command {
public:
	void execute(std::vector<std::string> substrings) override;
};

class AddBook : public Command {
public:
	void execute(std::vector<std::string> substrings) override;
};

class CreateShelf : public Command {
public:
	void execute(std::vector<std::string> substrings) override;
};

class DeleteShelf : public Command {
public:
	void execute(std::vector<std::string> substrings) override;
};

class AddToShelf : public Command {
public:
	void execute(std::vector<std::string> substrings) override;
};

class RemoveFromShelf : public Command {
public:
	void execute(std::vector<std::string> substrings) override;
};

class DeleteBook : public Command {
public:
	void execute(std::vector<std::string> substrings) override;
};

class ShowShelf : public Command {
public:
	void execute(std::vector<std::string> substrings) override;
};

class ShowInbox : public Command {
public:
	void execute(std::vector<std::string> substrings) override;
};

class ReadMSG : public Command {
public:
	void execute(std::vector<std::string> substrings) override;
};

class DeleteMSG : public Command {
public:
	void execute(std::vector<std::string> substrings) override;
};

class Friends : public Command {
public:
	void execute(std::vector<std::string> substrings) override;
};

class AddBirthday : public Command {
public:
	void execute(std::vector<std::string> substrings) override;
};

class Profile : public Command {
public:
	void execute(std::vector<std::string> substrings) override;
};

// Author commands
//class AcceptOffer : public Command {
//public:
//	void execute(std::vector<std::string> substrings) override;
//};
//
//class Leave : public Command {
//public:
//	void execute(std::vector<std::string> substrings) override;
//};
//
//class Followers : public Command {
//public:
//	void execute(std::vector<std::string> substrings) override;
//};
//// Publisher commands
//class Publish : public Command {
//public:
//	void execute(std::vector<std::string> substrings) override;
//};
//
//class AddSynopsis : public Command {
//public:
//	void execute(std::vector<std::string> substrings) override;
//};
//
//class Offer : public Command {
//public:
//	void execute(std::vector<std::string> substrings) override;
//};
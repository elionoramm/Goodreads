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

//class AddBook : public Command {
//
//};
//
//class CreateShelf : public Command {
//
//};
//
//class DeleteShelf : public Command {
//
//};
//
//class AddToShelf : public Command {
//
//};
//
//class RemoveFromShelf : public Command {
//
//};
//
//class DeleteBook : public Command {
//
//};
//
//class ShowShelf : public Command {
//
//};
//
//class ShowInbox : public Command { // both reader and author
//
//};
//
//class ReadMSG : public Command {
//
//};
//
//class DeleteMSG : public Command {
//
//};
//
//class Friends : public Command {
//
//};
//
//class AddBirthday : public Command {
//
//};
//
//class Profile : public Command {
//
//};
//// Author commands
//class AcceptOffer : public Command {
//
//};
//
//class Leave : public Command {
//
//};
//
//class Followers : public Command {
//
//};
//// Publisher commands
//class Publish : public Command {
//
//};
//
//class AddSynopsis : public Command {
//
//};
//
//class Offer : public Command {
//
//};
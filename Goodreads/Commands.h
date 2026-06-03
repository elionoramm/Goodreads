#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
//#include "User.h"
//#include "Reader.h"
//#include "Author.h"
//#include "Publisher.h"
#include "Command.h"
#include "GoodReads.h"

// User commands
class Help : public Command {
private:
	GoodReads& goodReads;
public:
	Help(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class Register : public Command {
private:
	GoodReads& goodReads;
public:
	Register(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class Login : public Command {
private:
	GoodReads& goodReads;
public:
	Login(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class Logout : public Command {
private:
	GoodReads& goodReads;
public:
	Logout(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class Exit : public Command {
private:
	GoodReads& goodReads;
public:
	Exit(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

// Reader commands
class Search : public Command {
private:
	GoodReads& goodReads;
public:
	Search(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class Follow : public Command {
private:
	GoodReads& goodReads;
public:
	Follow(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class AddBook : public Command {
private:
	GoodReads& goodReads;
public:
	AddBook(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class CreateShelf : public Command {
private:
	GoodReads& goodReads;
public:
	CreateShelf(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class DeleteShelf : public Command {
private:
	GoodReads& goodReads;
public:
	DeleteShelf(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class AddToShelf : public Command {
private:
	GoodReads& goodReads;
public:
	AddToShelf(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class RemoveFromShelf : public Command {
private:
	GoodReads& goodReads;
public:
	RemoveFromShelf(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class DeleteBook : public Command {
private:
	GoodReads& goodReads;
public:
	DeleteBook(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class ShowShelf : public Command {
private:
	GoodReads& goodReads;
public:
	ShowShelf(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class ShowInbox : public Command {
private:
	GoodReads& goodReads;
public:
	ShowInbox(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class ReadMSG : public Command {
private:
	GoodReads& goodReads;
public:
	ReadMSG(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class DeleteMSG : public Command {
private:
	GoodReads& goodReads;
public:
	DeleteMSG(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class Friends : public Command {
private:
	GoodReads& goodReads;
public:
	Friends(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class AddBirthday : public Command {
private:
	GoodReads& goodReads;
public:
	AddBirthday(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class Profile : public Command {
private:
	GoodReads& goodReads;
public:
	Profile(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

// Author commands
class AcceptOffer : public Command {
private:
	GoodReads& goodReads;
public:
	AcceptOffer(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class Leave : public Command {
private:
	GoodReads& goodReads;
public:
	Leave(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class Followers : public Command {
private:
	GoodReads& goodReads;
public:
	Followers(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

// Publisher commands
class Publish : public Command {
private:
	GoodReads& goodReads;
public:
	Publish(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class AddSynopsis : public Command {
private:
	GoodReads& goodReads;
public:
	AddSynopsis(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};

class Offer : public Command {
private:
	GoodReads& goodReads;
public:
	Offer(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};
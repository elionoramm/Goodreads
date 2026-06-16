#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <time.h>
#include "Date.h"
#include "Book.h"
#include "Message.h"
#include "BookSystem.h"
#include "CustomUserExceptions.h"

class User {
protected:
	std::string username;
	std::string password;
	Date registrationDate;
	std::vector<std::string> followers;
public:
	User(const std::string& username, const std::string& password);
	virtual ~User() = default;
	virtual void loadUser(std::fstream& file, const BookSystem& bookSystem);
	virtual void saveUser(std::fstream& file) const;
	virtual std::string getUserType() const = 0;
	std::string getUsername() const;
	std::string getPassword() const;
	Date getRegistrationDate() const;
	std::vector<std::string>& getFollowers();
	std::string findFollower(const std::string& username) const;
	void printFollowers() const;
	virtual void help() const = 0;
	bool isFollowedBy(const std::string& username) const;
	friend class PasswordValidator;
	friend class UsernameValidator;
};
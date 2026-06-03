#include "User.h"

User::User(const std::string& username, const std::string& password) {
	this->username = username;
	this->password = password;
	std::time_t t = std::time(0);
	std::tm datetime;
	localtime_s(&datetime, &t);
	std::string dateString = std::to_string(datetime.tm_mday) + "/" + std::to_string(datetime.tm_mon + 1) + "/" + std::to_string(datetime.tm_year + 1900);
	registrationDate = Date(dateString);
}

void User::loadUser(std::fstream& file) {
	std::string registrationDateString;
	file >> registrationDateString;
	this->registrationDate = Date(registrationDateString);
	std::string followersCount;
	file >> followersCount;
	for (size_t i = 0; i < static_cast<size_t>(std::stoull(followersCount)); i++) {
		std::string follower;
		file >> follower;
		followers.push_back(follower);
	}
}

void User::saveUser(std::fstream& file) const {
	file << getUserType() << '\n' << username << '\n' << password << '\n' << registrationDate.dateToString() << '\n';
	file << std::to_string(followers.size()) << '\n';
	for (size_t i = 0; i < followers.size(); i++) {
		file << followers[i] << '\n';
	}
}

std::string User::getUsername() const {
	return username;
}

std::string User::getPassword() const {
	return password;
}

Date User::getRegistrationDate() const {
	return registrationDate;
}

std::vector<std::string> User::getFollowers() const {
	return followers;
}

void User::addFollower(const std::string follower) {
	if (follower == username) {
		std::cout << "You cannot follow yourself.\n" << std::endl;
		return;
	}
	for (size_t i = 0; i < followers.size(); i++) {
		if (followers[i] == follower) {
			std::cout << "You are already following this user.\n" << std::endl;
			return;
		}
	}
	followers.push_back(follower);
	std::cout << "You are now following " << username << ".\n" << std::endl;
	if (this->getUserType() != "publisher") {
		std::string activeUserUsername = follower;
		std::string messageContent = activeUserUsername + " has sent you a friend request.";
		Message message = Message(activeUserUsername, 0, messageContent);
		this->receiveMessage(message);
	}
	else {
		std::cout << "Publishers cannot follow other users.\n" << std::endl;
	}
}

void User::printFollowers() const {
	std::cout << "Followers:\n";
	for (size_t i = 0; i < followers.size(); i++) {
		std::cout << "- " << followers[i] << std::endl;
	}
	if (followers.size() == 0) {
		std::cout << "You have no followers yet.\n" << std::endl;
	}
}

bool User::isFollowedBy(const std::string& username) const {
	for (size_t i = 0; i < followers.size(); i++) {
		if (followers[i] == username) {
			return true;
		}
	}
	return false;
}
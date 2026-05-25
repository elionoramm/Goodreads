#include <iostream>
#include "User.h"
#include "Repository.cpp"

std::string User::getUsername() const {
	return username;
}

std::string User::getPassword() const {
	return password;
}

Date User::getRegistrationDate() const {
	return registrationDate;
}

void User::addFollower(const std::shared_ptr<User> follower) {
	if (follower->getUsername() == username) {
		std::cout << "You cannot follow yourself.\n" << std::endl;
		return;
	}
	for (size_t i = 0; i < followers.size(); i++) {
		if (followers[i] == follower) {
			std::cout << "You are already following this user.\n" << std::endl;
			return;
		}
	}
	followers.addElement(follower);
	std::cout << "You are now following " << username << ".\n" << std::endl;
	if (this->getUserType() != "Publisher") {
		std::string activeUserUsername = follower->getUsername();
		std::string messageContent = activeUserUsername + " has sent you a friend request.";
		std::shared_ptr<Message> message = std::make_shared<Message>(activeUserUsername, 0, messageContent);
		this->receiveMessage(message);
	}
	else {
		std::cout << "Publishers cannot follow other users.\n" << std::endl;
	}
}

void User::printFollowers() const {
	std::cout << "Followers:\n";
	for (size_t i = 0; i < followers.size(); i++) {
		std::cout << "- " + followers[i]->getUsername() << std::endl;
	}
	if (followers.size() == 0) {
		std::cout << "You have no followers yet.\n" << std::endl;
	}
}

bool User::isFollowedBy(const std::string& username) const {
	for (size_t i = 0; i < followers.size(); i++) {
		if (followers[i]->getUsername() == username) {
			return true;
		}
	}
	return false;
}
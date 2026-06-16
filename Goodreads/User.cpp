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

void User::loadUser(std::fstream& file, const BookSystem& bookSystem) {
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

std::vector<std::string>& User::getFollowers() {
	return followers;
}

std::string User::findFollower(const std::string& username) const {
	for (auto follower : followers) {
		if (follower == username) {
			return follower;
		}
	}
	return "";
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
#include "Reader.h"
std::string Reader::getUserType() const {
	return "Reader";
}
Reader::Reader(const std::string& username, const std::string& password) {
	this->username = username;
	this->password = password;
}
#include "Publisher.h"
std::string Publisher::getUserType() const {
	return "Publisher";
}
Publisher::Publisher(const std::string& username, const std::string& password) {
	this->username = username;
	this->password = password;
}
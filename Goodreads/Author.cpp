#include "Author.h"
std::string Author::getUserType() const {
	return "Author";
}
Author::Author(const std::string& username, const std::string& password) : Reader(username, password) {}

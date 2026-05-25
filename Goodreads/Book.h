#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Date.h"

class Book {
private:
	std::string title;
	std::string author;
	std::string publisher;
	std::string synopsis;
	std::vector<std::string> genres;
	double averageRating;
	unsigned int reviewsCount;
	Date publishingDate;
	unsigned int pagesCount;
public:
	Book(const std::string& title);
	Book(const std::string title, const std::string author, const std::string publisher, const Date releaseDate, const int pageCount, const std::vector<std::string> genres);
	std::string getTitle() const;
	std::string getSynopsis() const;
	double getAverageRating() const;
	void addReview(const double rating);
	void addSynopsis(const std::string synopsis);
};
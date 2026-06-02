#pragma once
#include <string>
#include <vector>
#include <memory>
#include <fstream>
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
	Date releaseDate;
	unsigned int pagesCount;
public:
	Book(const std::string& title);
	Book(const std::string title, const std::string author, const std::string publisher, const Date releaseDate, const int pageCount, const std::vector<std::string> genres);
	std::string getTitle() const;
	std::string getAuthor() const;
	std::string getPublisher() const;
	std::vector<std::string> getGenres() const;
	unsigned int getPageCount() const;
	Date getReleaseDate() const;
	std::string getSynopsis() const;
	double getAverageRating() const;
	void addReview(const double rating);
	void addSynopsis(const std::string synopsis);
	void saveBook(std::fstream& file) const;
	void loadBook(std::fstream& file);
};
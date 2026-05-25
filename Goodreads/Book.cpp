#include "Book.h"

Book::Book(const std::string& title) : title(title), averageRating(0), reviewsCount(0) {}

Book::Book(const std::string title, const std::string author, const std::string publisher, const Date releaseDate, const int pageCount, const std::vector<std::string> genres) {
	this->title = title;
	this->author = author;
	this->publisher = publisher;
	this->synopsis = "";
	this->genres = genres;
	this->averageRating = 0;
	this->reviewsCount = 0;
	this->publishingDate = releaseDate;
	this->pagesCount = pageCount;
}

std::string Book::getTitle() const {
	return title;
}

std::string Book::getSynopsis() const {
	return synopsis;
}

double Book::getAverageRating() const {
	return averageRating;
}

void Book::addReview(const double rating) {
	averageRating = (averageRating * reviewsCount + rating) / (reviewsCount + 1);
	reviewsCount++;
}

void Book::addSynopsis(const std::string synopsis) {
	this->synopsis = synopsis;
}
#include <iostream>
#include "Book.h"

Book::Book(const std::string& title) : title(title), averageRating(0), reviewsCount(0), pagesCount(0) {}

Book::Book(const std::string title, const std::string author, const std::string publisher, const Date releaseDate, const int pageCount, const std::vector<std::string> genres) {
	this->title = title;
	this->author = author;
	this->publisher = publisher;
	this->synopsis = "#";
	this->genres = genres;
	this->averageRating = 0;
	this->reviewsCount = 0;
	this->releaseDate = releaseDate;
	this->pagesCount = pageCount;
}

std::string Book::getTitle() const {
	return title;
}

std::string Book::getAuthor() const {
	return author;
}

std::string Book::getPublisher() const {
	return publisher;
}

std::vector<std::string> Book::getGenres() const {
	return genres;
}

unsigned int Book::getPageCount() const {
	return pagesCount;
}

Date Book::getReleaseDate() const {
	return releaseDate;
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

void Book::saveBook(std::fstream& file) const {
	file << title << '\n' << author << '\n' << publisher << '\n';
	file << releaseDate.dateToString() << '\n';
	file << std::to_string(pagesCount) << '\n';
	file << std::to_string(genres.size()) << '\n';
	for (size_t i = 0; i < genres.size(); i++) {
		file << genres[i] << '\n';
	}
	file << synopsis << '\n';
	file << std::to_string(reviewsCount) << '\n';
	file << std::to_string(averageRating) << '\n';
}

void Book::loadBook(std::fstream& file) {
	file >> author;
	file >> publisher;
	std::string releaseDateString;
	file >> releaseDateString;
	releaseDate = Date(releaseDateString);
	std::string pagesCount;
	file >> pagesCount;
	this->pagesCount = std::stoi(pagesCount);
	std::string genresCount;
	file >> genresCount;
	for (size_t i = 0; i < static_cast<size_t>(std::stoull(genresCount)); i++) {
		std::string genre;
		file >> genre;
		genres.push_back(genre);
	}
	file >> synopsis;
	std::string reviewsCount;
	file >> reviewsCount;
	this->reviewsCount = std::stoi(reviewsCount);
	std::string averageRating;
	file >> averageRating;
	this->averageRating = std::stod(averageRating);
}
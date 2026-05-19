#include "Book.h"

Book::Book(const std::string& title) : title(title), averageRating(0), reviewsCount(0) {}

std::string Book::getTitle() const {
	return title;
}

double Book::getAverageRating() const {
	return averageRating;
}

void Book::addReview(double rating) {
	averageRating = (averageRating * reviewsCount + rating) / (reviewsCount + 1);
	reviewsCount++;
}
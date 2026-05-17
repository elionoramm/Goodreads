#pragma once
#include <string>
#include <vector>
//#include <memory>
//#include "Author.h"
//#include "Publisher.h"
#include "Date.h"
enum genre {
	Action,
	Adventure,
	Biography,
	Fantasy,
	GraphicNovel,
	HistoricalFiction,
	History,
	Horror,
	LiteraryFiction,
	Memoir,
	Mystery,
	Romance,
	ScienceFiction,
	SelfHelp,
	Thriller,
	TravelLiterature,
	YoungAdult
};
class Book {
private:
	std::string title;
	//std::weak_ptr<Author> author;
	//std::weak_ptr<Publisher> publisher;
	std::string summary;
	std::vector<genre> genres;
	double averageRating;
	unsigned int reviewsCount;
	Date publishingDate;
	unsigned int pagesCount;
public:
	std::string getTitle() const;
	double getAverageRating() const;
};
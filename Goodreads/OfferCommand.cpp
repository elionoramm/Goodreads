#include "OfferCommand.h"

Offer::Offer(GoodReads& goodReads) : goodReads(goodReads) {}

void Offer::execute(std::vector<std::string> params) {
	std::shared_ptr<Publisher> activeUser = goodReads.getActivePublisher();
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 1) {
		throw WrongCommandUsage("Usage: offer <author>\n");
	}
	std::string authorName = params[0];
	if (activeUser->getUsername() == authorName) {
		throw std::invalid_argument("You cannot send yourself a job offer.\n");
	}
	std::shared_ptr<Author> author = goodReads.toAuthor(goodReads.findUser(authorName));
	if (author->getUserType() != "author") {
		throw std::invalid_argument("This user is not an author, you cannot send them a job offer.\n");
	}
	if (author->hasAJobOfferFrom(activeUser->getUsername())) {
		throw std::invalid_argument("This author already has a job offer from you.\n");
	}
	if (author->isWorkingWithPublisher(activeUser->getUsername())) {
		throw std::invalid_argument("You are already working with this author.\n");
	}
	if (author->getUsername() == authorName && author->getUserType() == "author") {
		std::string activeUserUsername = activeUser->getUsername();
		std::string messageContent = activeUserUsername + " has sent you a job offer.";
		Message message = Message(activeUserUsername, 0, messageContent);
		goodReads.toAuthor(author)->receiveMessage(message);
		std::cout << "You have sent " << authorName << " a job offer.\n" << std::endl;
	}
}
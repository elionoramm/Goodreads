#include "AcceptOfferCommand.h"

AcceptOffer::AcceptOffer(GoodReads& goodReads) : goodReads(goodReads) {}

void AcceptOffer::execute(std::vector<std::string> params) {
	std::shared_ptr<Author> activeUser = goodReads.getActiveAuthor();
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 1) {
		throw WrongCommandUsage("Usage: accept-offer <index>\n");
	}
	int index;
	try {
		index = std::stoi(params[0]);
	}
	catch (const std::invalid_argument& e) {
		std::cout << "Invalid index.\n" << std::endl;
		return;
	}
	std::string publisherName = activeUser->getPublisher(index);
	if (publisherName == "") {
		throw std::invalid_argument("Offer not found.\n");
	}
	std::shared_ptr<Publisher> publisher = goodReads.toPublisher(goodReads.findUser(publisherName));
	if (publisher == nullptr) {
		throw std::invalid_argument("Publisher not found.\n");
	}
	activeUser->acceptOffer(index, publisherName);
	publisher->addAuthor(activeUser->getUsername());
}
#pragma once
#include <memory>
#include <string>
#include "GoodReads.h"
#include "Command.h"
#include "HelpCommand.h"
#include "RegisterCommand.h"
#include "LoginCommand.h"
#include "LogoutCommand.h"
#include "ExitCommand.h"
#include "SearchCommand.h"
#include "FollowCommand.h"
#include "AddBookCommand.h"
#include "CreateShelfCommand.h"
#include "DeleteShelfCommand.h"
#include "AddToShelfCommand.h"
#include "RemoveFromShelfCommand.h"
#include "DeleteBookCommand.h"
#include "ShowShelfCommand.h"
#include "ShowInboxCommand.h"
#include "ReadMSGCommand.h"
#include "DeleteMSGCommand.h"
#include "FriendsCommand.h"
#include "addBirthdayCommand.h"
#include "ProfileCommand.h"
#include "AcceptOfferCommand.h"
#include "LeaveCommand.h"
#include "FollowersCommand.h"
#include "PublishCommand.h"
#include "addSynopsisCommand.h"
#include "OfferCommand.h"
class CommandFactory {
private:
	GoodReads& goodReads;
public:
	CommandFactory(GoodReads& goodReads);
	std::unique_ptr<Command> create(const std::string& input) const;
};
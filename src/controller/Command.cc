#include "Command.h"

static const std::string default_message = "no message";

Command::Command(CommandType type)
	: type{ type }, message{ default_message }
{

}

Command::Command()
	: type{ CommandType::UNDEFINED_COMMAND }, message{ default_message }
{

}

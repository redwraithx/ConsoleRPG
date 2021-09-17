#ifndef DEBUGMODE_H
#define DEBUGMODE_H



static struct DebugMessages
{
	DebugMessages() : enableDebugMessages(false) // set to true for debug messages
	{}

	bool enableDebugMessages;
}debugLog;


#endif //DEBUGMODE_H
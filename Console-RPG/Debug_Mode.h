#ifndef DEBUGMODE_H
#define DEBUGMODE_H



static struct debug_messages
{
	debug_messages() : enable_debug_messages(false) // set to true for debug messages
	{}

	bool enable_debug_messages;
}debug_log;


#endif //DEBUGMODE_H
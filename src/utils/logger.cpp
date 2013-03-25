#include "utils/logger.h"
#include <iostream>

using namespace jormungandr;

class DefaultLogger : public Logger
{
public:
	inline void log(const char* p_Message) const
	{
		std::cout<<"Log : "<<p_Message<<std::endl;
	}

	inline void error(const char* p_Message) const
	{
		std::cout<<"Error : "<<p_Message<<std::endl;
	}
};

const Logger* g_DefaultLogger = new DefaultLogger();

//-------------------------------------------------

const Logger* logger::defaultLogger()
{
	return g_DefaultLogger;
}

//-------------------------------------------------

Logger* logger::createDefaultLogger()
{
	return new DefaultLogger();
}

//-------------------------------------------------

void logger::log(const char* p_Message, const Logger* p_Logger)
{
	if(nullptr == p_Logger)
	{
		defaultLogger()->log(p_Message);
	}
	else
	{
		p_Logger->log(p_Message);
	}
}

//-------------------------------------------------

void logger::error(const char* p_Message, const Logger* p_Logger)
{
	if(nullptr == p_Logger)
	{
		defaultLogger()->error(p_Message);
	}
	else
	{
		p_Logger->error(p_Message);
	}
}
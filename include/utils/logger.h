#pragma once

#include "utils\logger_type.h"

namespace jormungandr
{
	class Logger
	{
	public:
		inline virtual void log(const char* p_Message) const = 0;
		inline virtual void error(const char* p_Message) const = 0;
	};

	namespace logger
	{
		const Logger* defaultLogger();
		Logger* createDefaultLogger();

		/**
		* \brief if m_Logger is null, then the default logger is used
		*/
		void log(const char* p_Message, const Logger* m_Logger = nullptr);

		/**
		* \brief if m_Logger is null, then the default logger is used
		*/
		void error(const char* p_Message, const Logger* m_Logger = nullptr);
	}
}
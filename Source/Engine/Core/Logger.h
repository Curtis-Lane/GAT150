#pragma once

#include <string>
#include <fstream>
#include <cassert>

#define INFO_LOG    {ane::globalLogger.Log(ane::LogLevel::INFO, __FILE__, __LINE__);}
#define WARNING_LOG {ane::globalLogger.Log(ane::LogLevel::WARNING, __FILE__, __LINE__);}
#define ERROR_LOG   {ane::globalLogger.Log(ane::LogLevel::ERROR, __FILE__, __LINE__);}
#define ASSERT_LOG  {ane::globalLogger.Log(ane::LogLevel::ASSERT, __FILE__, __LINE__);}

namespace ane {
	enum class LogLevel {
		INFO,
		WARNING,
		ERROR,
		ASSERT
	};

	class Logger {
		public:
			Logger(LogLevel logLevel, std::ostream* ostream) {
				this->logLevel = logLevel;
				this->ostream = ostream;
			}

			bool Log(LogLevel logLevel, const std::string& fileName, int line);

		private:
			LogLevel logLevel;
			std::ostream* ostream = nullptr;
			std::ofstream fstream;
	};

	extern Logger globalLogger;
}
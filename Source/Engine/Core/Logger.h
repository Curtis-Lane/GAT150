#pragma once

#include "Framework/Singleton.h"

#include <string>
#include <fstream>
#include <iostream>
#include <cassert>

#ifdef _DEBUG
	#define INFO_LOG(message)    {if(ane::Logger::Instance().Log(ane::LogLevel::INFO, __FILE__, __LINE__)) {ane::Logger::Instance() << message << "\n";}}
	#define WARNING_LOG(message) {if(ane::Logger::Instance().Log(ane::LogLevel::WARNING, __FILE__, __LINE__)) {ane::Logger::Instance() << message << "\n";}}
	#define ERROR_LOG(message)   {if(ane::Logger::Instance().Log(ane::LogLevel::ERROR, __FILE__, __LINE__)) {ane::Logger::Instance() << message << "\n";}}
	#define ASSERT_LOG(condition, message)  {if(!condition && ane::Logger::Instance().Log(ane::LogLevel::ASSERT, __FILE__, __LINE__)) {ane::Logger::Instance() << message << "\n";} assert(condition);}
#else
	#define INFO_LOG(message)    {;}
	#define WARNING_LOG(message) {;}
	#define ERROR_LOG(message)   {;}
	#define ASSERT_LOG(condition, message)  {;}
#endif // _DEBUG

namespace ane {
	enum class LogLevel {
		INFO,
		WARNING,
		ERROR,
		ASSERT
	};

	class Logger : public Singleton<Logger> {
		public:
			Logger(LogLevel logLevel = LogLevel::INFO, std::ostream* ostream = &std::cout, const std::string& fileName = "log.txt") {
				this->logLevel = logLevel;
				this->ostream = ostream;
				if(!fileName.empty()) {
					this->fstream.open(fileName);
				}
			}

			bool Log(LogLevel logLevel, const std::string& fileName, int line);

			template<typename T>
			Logger& operator << (T value);

		private:
			LogLevel logLevel;
			std::ostream* ostream = nullptr;
			std::ofstream fstream;
	};

	template<typename T>
	inline Logger& Logger::operator << (T value) {
		if(this->ostream != nullptr) {
			*(this->ostream) << value;
		}
		if(this->fstream.is_open()) {
			this->fstream << value;
			this->fstream.flush();
		}

		return *this;
	}
}
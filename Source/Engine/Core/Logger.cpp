#include "Logger.h"

#include <iostream>

#include "FileIO.h"

namespace ane {
	Logger globalLogger(LogLevel::INFO, &std::cout, "log.txt");

	bool Logger::Log(LogLevel logLevel, const std::string& fileName, int line) {
		if(logLevel < this->logLevel) {
			return false;
		}

		switch(logLevel) {
			case LogLevel::INFO:
				*this << "INFO: ";
				break;
			case LogLevel::WARNING:
				*this << "WARNING: ";
				break;
			case LogLevel::ERROR:
				*this << "ERROR: ";
				break;
			case LogLevel::ASSERT:
				*this << "ASSERT: ";
				break;
			default:
				break;
		}

		*this << getFileName(fileName) << "(" << line << ") ";

		return true;
	}
}